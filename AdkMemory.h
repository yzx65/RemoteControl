/********************************************************************
 * Module:									(BuildNum:0012-2011111)
 *       AdkMemory.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		�ṩ�������ڴ���ʺ���
 *
 *			AdkMalloc				-- (�������Զ����ڴ�������0)
 *			AdkFree
 *
 *			AdkZeroMemory
 *			AdkFillMemory
 *			AdkCopyMemory
 *			AdkMoveMemory
 * 			AdkXorMemory			-- �ڴ��ĳ��ֵ�������
 *			AdkXorMemoryEx			-- �����ڴ�֮��������
 *			AdkCompareMemory		-- �Ƚ��ڴ�
 *			AdkMemoryFind			-- �ڴ����
 *
 */

#ifndef __ADK_TUOJIE_MEMORY_H__
#define __ADK_TUOJIE_MEMORY_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

//
// �ļ������ǰ׺�ͺ�׺
//

#define ADK_MEM_PREFIX                 0x12345678
#define ADK_MEM_POSTFIX                0x87654321

//----------------------------------------------------------------
// �ڴ�����ͷź��� Memory Allocate And Free Function
//
//

#ifdef _DEBUG

#ifdef __KERNEL__

/**************************************************************
 * AdkMalloc
 * 
 */
__inline 
PVOID NTAPI AdkMalloc(IN POOL_TYPE	PoolType,
					  IN ULONG		Size)
{
	PBYTE Ptr = NULL;

	if (Size == 0)
	{
		return NULL;
	}

	xASSERT(((1024*1024*256) > Size && Size));

	Ptr  = (PBYTE)ExAllocatePool(PoolType,(SIZE_T)(Size + 12));
	if (Ptr)
	{
		RtlZeroMemory(Ptr, (SIZE_T)(Size + 12));

		*(ULONG*)&Ptr[0]        = Size;
		*(ULONG*)&Ptr[4]        = ADK_MEM_PREFIX;
		*(ULONG*)&Ptr[Size + 8]	= ADK_MEM_POSTFIX;

		Ptr += 8;
	}

	return Ptr;
}

/**************************************************************
 * AdkFree
 * 
 */
__inline 
VOID NTAPI AdkFree(PVOID Ptr)
{
	PBYTE aPtr = (PBYTE)Ptr;

	AdkASSERT(Ptr);

	AdkASSERT(ADK_MEM_PREFIX  == *(ULONG*)&aPtr[-4]);
	AdkASSERT(ADK_MEM_POSTFIX == *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]]);

	aPtr -= 8;
	Ptr   = aPtr;

	ExFreePool(Ptr);

	return ;
}

#else	// USER

/**************************************************************
 * AdkMalloc:
 * 
 */
__inline 
PVOID WINAPI AdkMalloc(IN ULONG	 Size)
{
	PBYTE Ptr = NULL;

	if (Size == 0)
	{
		return NULL;
	}

	AdkASSERT(((1024*1024*256) > Size && Size));

	Ptr = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY , (SIZE_T)(Size + 12));
	if (Ptr)
	{
		*(ULONG*)&Ptr[4]           = ADK_MEM_PREFIX;
		*(ULONG*)&Ptr[0]           = Size;
		*(ULONG*)&Ptr[Size + 8] = ADK_MEM_POSTFIX;

		Ptr += 8;
	}

	return Ptr;
}

/**************************************************************
 * AdkFree:
 * 
 */
__inline
VOID WINAPI AdkFree(PVOID Ptr)
{
	PBYTE aPtr = (PBYTE)Ptr;

	AdkASSERT(NULL != Ptr);

	AdkASSERT(ADK_MEM_PREFIX  == *(ULONG*)&aPtr[-4]);

	if (ADK_MEM_POSTFIX != *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]])
	{
		aPtr = (PBYTE)Ptr;
	}

	AdkASSERT(ADK_MEM_POSTFIX == *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]]);

	aPtr -= 8;
	Ptr   = aPtr;	

	HeapFree(GetProcessHeap(), 0, Ptr);

	return ;
}

#endif // !__KERNEL__

#else	// RELEASE

#ifdef __KERNEL__

/**************************************************************
 * AdkMalloc - Ϊ�˺�DEBUG�汾��AdkMalloc��Ϊ��һ�£�������Ҫ������0
 * 
 */
__inline 
PVOID NTAPI AdkMalloc(IN POOL_TYPE	PoolType,  IN ULONG		Size)
{
	PBYTE Ptr = (PBYTE)ExAllocatePool(PoolType,(SIZE_T)(Size ));

	if (Ptr)
	{
		RtlZeroMemory(Ptr, (SIZE_T)(Size));
	}

	return Ptr;
}

#define AdkFree(__PTR__)						ExFreePool((__PTR__))

#else // _WIN32_

#define AdkMalloc(__HOWMUCH__)					(PVOID)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,(SIZE_T)(__HOWMUCH__));
#define AdkFree(__PTR__)						HeapFree(GetProcessHeap(), 0, __PTR__)

#endif // !__KERNEL__

#endif // !_DEBUG

//----------------------------------------------------------------
// �ڴ�������� Memory Operation Function
//

/**************************************************************
 * AdkFillMemory
 *
 */
INLINE
VOID AdkFillMemory(PVOID	lpBuffer,
				   int		nCount,
				   BYTE		Fill)
{
	PBYTE lpPos = (PBYTE)lpBuffer;

	xASSERT((lpBuffer));

	while (nCount--) 
	{
		*lpPos++ = Fill;	
	}

	return;
}

/**************************************************************
 * AdkZeroMemory
 *
 */
INLINE
VOID AdkZeroMemory(PVOID lpBuffer, int nCount)
{
	xASSERT((lpBuffer));

	AdkFillMemory(lpBuffer, nCount, 0);
}

/**************************************************************
 * AdkCopyMemory
 *
 */
INLINE
VOID AdkCopyMemory(PVOID		lpDest,
				   const PVOID	lpSrc,
				   int			nCount)
{
	PBYTE lpbyDest = (PBYTE)lpDest;
	PBYTE lpbySrc = (PBYTE)lpSrc;

	xASSERT((lpDest));
	xASSERT((lpSrc));

    // copy from lower addresses to higher addresses
    //
    while (nCount--) 
	{
		*lpbyDest++ = *lpbySrc++;
	}

	return;
}

/**************************************************************
 * AdkMoveMemory
 *
 */
INLINE
VOID AdkMoveMemory(PVOID		lpDest,
				   const PVOID	lpSrc,
				   int			nCount)
{
	PBYTE lpbyDest = (PBYTE)lpDest;
	PBYTE lpbySrc = (PBYTE)lpSrc;

	xASSERT((lpDest));
	xASSERT((lpSrc));

	if (lpbyDest <= lpbySrc || lpbyDest >= (lpbySrc + nCount)) 
	{
		//
		// Non-Overlapping Buffers
		// copy from lower addresses to higher addresses
		//
		while (nCount--) 
		{
			*lpbyDest++ = *lpbySrc++;
		}
	}
	else 
	{
		//
		// Overlapping Buffers
		// copy from higher addresses to lower addresses
		//
		lpbyDest = lpbyDest + nCount - 1;
		lpbySrc = lpbySrc + nCount - 1;

		while (nCount--) 
		{
			*lpbyDest-- = *lpbySrc--;
		}
	}
}

/**************************************************************
 * AdkXorMemory
 *
 */
INLINE
VOID AdkXorMemory(PVOID lpBuf, const BYTE byMask, int nCount)
{
	PBYTE lpbyBuf = (PBYTE)lpBuf;
	int i;
	for (i = 0; i < nCount; i++) 
	{
		lpbyBuf[i] ^= byMask;
	}
}

/**************************************************************
 * AdkXorMemoryEx
 *
 */
INLINE
VOID AdkXorMemoryEx(PVOID lpBuf, const PBYTE lpMask, int nCount)
{
	PBYTE lpbyBuf = (PBYTE)lpBuf;
	int i;

	for (i = 0; i < nCount; i++) 
	{
		lpbyBuf[i] ^= lpMask[i];
	}
}

/*********************************************************************
 * AdkCompareMemory
 *
 */
INLINE
int AdkCompareMemory(const PVOID lpBuf1,
					 const PVOID lpBuf2,
					 int		 nCount)
{
	PBYTE lpbyBuf1 = (PBYTE)lpBuf1;
	PBYTE lpbyBuf2 = (PBYTE)lpBuf2;

	if (nCount == 0)
	{
		return(0);
	}

	while ( --nCount && *lpbyBuf1 == *lpbyBuf2 ) 
	{
		lpbyBuf1++;
		lpbyBuf2++;
	}

	return ( *((unsigned char *)lpbyBuf1) - *((unsigned char *)lpbyBuf2) );
}

/*********************************************************************
 * AdkMemoryFind
 *
 *	����ֵ�ǵ�һ���ҵ��ڴ���ƫ��ֵ��-1˵��û���ҵ�
 *	
 *
 */
INLINE
int AdkMemoryFind(const char *mem,	 
				  const char *str, 
				  int		 sizem,		// �ڴ�ռ�ĳ���
				  int		 sizes)		// ���ҵ�ƥ���ڴ�鳤��,Ϊ0,����ʧ��
{   
	int  i,j; 

	if (sizes == 0) 
	{
		return -1;
	}

	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < sizes; j ++)
		{
			if (mem[i+j] != str[j])	
			{
				break;
			}

			if (j + 1 == sizes) 
			{
				return i;
			}
		}
	} 

	return -1;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ! __ADK_TUOJIE_MEMORY_H__

/*
 * Revision:
 *
 *		11. ����RtlZeroMemory��Rtl���صĺ�������������C�⣬������ʵ����AdkZeroMemory�Ⱥ���			(BuildNum:0012-2011111)
 *				AdkZeroMemory / AdkFillMemory / AdkCopyMemory / AdkMoveMemory
 *			ȥ����AdkSecureZeroMemory
 *
 *		10. ������AdkMemoryFind��һ��BUG��if (j == sizes) ��Ϊif (j + 1 == sizes)					(BuildNum:0011-20110919)
 *
 *		9. ������AdkMemoryFind,�Ա����ڸ������ڴ�ռ��в���һ���������ڴ�飬���ڱ���/Э�����(���ܰ���0)��Ч���ر��		(BuildNum:0010-20110825)
 *
 *		8. AdkMalloc������û�жԷ��䳤���Ƿ�Ϊ0���м��				(BuildNum:0009-20110630)
 *
 *		7. ������AdkCompareMemory����								(BuildNum:0008-20100917)
 *
 *		6. �ع���AdkXorMemory, ������AdkXorMemoryEx					(BuildNum:0007-20100524)
 *
 *		5. ���ع���������AdkFillMemory							(BuildNum:0006-20081003)
 *
 *		4. ���ӳ����ڴ濽���Ⱥ�����ͳһADK��ʽ
 *		   ����AdkXorMemory���������һ���ڴ�ռ�					(BuildNum:0005-20080707)
 *
 *		3. ����һ��Ǳ�ڵĴ���,��KERNEL�����Debug���Release����һ�����Ե�����, Debug��Ὣ�ڴ�����0, ��Release���򲻻�
 *			������ϲ��û����Ϊ��֪����,�ֽ���ͳһΪ��0			(BuildNum:0004-20080105)
 *
 *		2. Remove AdkGetModuleBase and AdkGetKernelProcAddress, 
 *		   Keep adkmemory to simplest 
 *																	(BuildNum:0003-20070729)
 *
 *		1. Found a potential bug, In kernel mode, debug AdkMalloc zero memory, but realse AdkMalloc
 *			don't zero memory. So we see AdkMalloc as ExAllocatePool, and should call RtlZeroMemory after AdkMalloc. 
 *
 *
 ******************************************************************************************************************/
