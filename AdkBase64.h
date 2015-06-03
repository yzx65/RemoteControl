/*************************************************************
 * Module:								 (BuildNum : 0002-20110619)
 *        AdkBase64.h
 *
 * Author:
 *        DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Histroy:
 *        Dec 31,2005,Nanjing (created)
 *
 * Description:
 *
 *       Base64����:Base64����������������ڴ���8Bit�ֽڴ���ı��뷽ʽ֮һ��
 *
 *       Base64Ҫ���ÿ����8Bit���ֽ�ת��Ϊ�ĸ�6Bit���ֽڣ�3*8 = 4*6 = 24����Ȼ���6Bit������λ��λ0������ĸ�8Bit���ֽڡ�
 * ����  �����������Ĺ��� ����
 *			�� ��3���ַ����4���ַ�.. ����
 *			�� ÿ76���ַ���һ�����з�.. ����
 *			�� ���Ľ�����ҲҪ����.. ����
 *
 *		��׼��Base64�����ʺ�ֱ�ӷ���URL�ﴫ�䣬��˲����˺ܶ�ı���:
 *			��׼Base 64					+ / =
 *			URL Base64					* _
 *			������ʽ Base64			! -
 *			..		
 *		ע:��ǰֻʵ���˱�׼��Base64����
 *
 * Usage:
 *
 *		��׼Base64����뺯��
 *
 *		  ��Ҫ���ȷ����ڴ�
 *			int AdkBase64Encode(unsigned char  *lpbyPlainBuf, 
 *								int				nPlainBufLen, 
 *								PCHAR			lpszEncodeBuf, 
 *								int				nEncodeBufSize)
 *
 *			int AdkBase64Decode(PCHAR			lpszBase64Buf,
 *								int				nBase64BufLen,
 *								unsigned char  *lpbyDecodeBuf,
 *								int				nDecodeBufSize);
 *
 *		  ����Ҫ���ȷ����ڴ�
 *			PCHAR AdkBase64EncodeEx(unsigned char  *lpszPlainBuf,
 *									int				nPlainBufLen,
 *									int			   *lpnEncodeLen);
 *
 *			PVOID AdkBase64DecodeEx(PCHAR		lpszBase64Buf,
 *									int			nBase64Len,
 *									int		   *lpnDecodeLen);
 *
 *	TODO:
 *		
 *		1. Ŀǰ��׼���뻹��һ��û�� - ÿ76���ֽ����ӷ��з�
 *		2. ʵ���������ε�Base64����
 *		
 *
 */

#ifndef _ADK_TUOJIE_BASE64_H_
#define _ADK_TUOJIE_BASE64_H_

#define BASE64_INVALID_CHAR        (unsigned long)-2
#define BASE64_IGNORE_CHAR         (unsigned long)-1

/**************************************************************
 * binary_from_ASCII
 *
 */
__inline
unsigned long binary_from_ASCII(char alpha)
{
	switch (alpha)
	{
	case '+':
		return 62;

	case '/': 
		return 63;

	case ' ':
	case '\t':
	case '\n':
	case '\r':

		return (BASE64_IGNORE_CHAR);

	default:

		if (  ('A' <= alpha) && ('Z' >= alpha) )
		{
			return (int)(alpha - 'A');
		}
		else if ( ('a' <= alpha) && ('z' >= alpha) )
		{
			return (int)(26 + (int)(alpha - 'a'));
		}
		else if ( ('0' <= alpha) && ('9' >= alpha) )
		{
			return (52  + (int)(alpha - '0'));
		}
	}

	return BASE64_INVALID_CHAR;
}

/**************************************************************
 * AdkBase64Decode
 *
 * ����˵����
 *		lpszBase64Buf		- ָ��Base64���������
 *		nBase64BufLen		- Base64���볤��
 *		lpbyDecodeBuf		- ָ������Ŀռ�
 *		nDecodeBufSize		- lpbyDecodeBuf��ָ����ڴ泤��
 *
 * ����ֵ��
 *		������ֵ>0, ˵���ǽ����ĳ���
 *		������Ϊ=0, ˵��lpszBase64Bufָ��Ŀռ�����Ƿ��ַ�
 *
 * ע�⣺
 *		��lpbyDecodeBuf�ռ䳤�Ȳ�����ʱ���ǽ�����������
 *
 */
__inline
int AdkBase64Decode(const char*		lpszBase64Buf,
					int				nBase64BufLen,
					unsigned char * lpbyDecodeBuf,
					int				nDecodeBufSize)
{
	int           i     = 0;
	int           shift = 0;
	unsigned long accum = 0;
	unsigned long value;

	xASSERT((lpszBase64Buf));
	xASSERT((lpbyDecodeBuf));

    nDecodeBufSize--;

	for ( ; ; ++lpszBase64Buf)
	{
		value = binary_from_ASCII(*lpszBase64Buf);

		if (value < 64)
		{
			accum <<= 6;
			shift  += 6;
			accum  |= value;

			if (shift >= 8)
			{
				shift -= 8;
				value  = accum >> shift;

				lpbyDecodeBuf[i++] = (unsigned char)value & 0xFF;
				if (i >= nDecodeBufSize)
				{
					break;
				}
			}
		}
		else if ( BASE64_IGNORE_CHAR == value)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	
	if (i > 0)
	{
		lpbyDecodeBuf[i] = '\0';
	}

	return i;
}

/**************************************************************
 * AdkBase64DecodeEx
 *
 * ����˵����
 *		lpszBase64Buf		- ָ��Base64���������
 *		nBase64BufLen		- Base64���볤��
 *		lpnDecodeLen		- �����ĳ��ȣ�ָ�룩
 *
 * ����ֵ��
 *		����ΪNULL��˵�������Ƿ��ַ�
 *		����Ϊ���������Ŀռ� (ע����ʹ��ʱ����Ҫ�ֹ�����AdkFree�����ͷ�)
 *
 */
__inline
PVOID AdkBase64DecodeEx(PCHAR		lpszBase64Buf,
						int			nBase64BufLen,
						int			*lpnDecodeLen)
{
	int		nDecodeLen = nBase64BufLen + 2;			// BASE64����ĳ��Ȼ�Сһ��
	PVOID	lpDecodeBuf = AdkMalloc(nDecodeLen);		

	if (lpDecodeBuf)
	{
		nDecodeLen = AdkBase64Decode(lpszBase64Buf, nBase64BufLen, (PUCHAR)lpDecodeBuf, nDecodeLen);
		if (nDecodeLen == 0)
		{
			AdkFree(lpDecodeBuf);
			return NULL;
		}

		if (lpnDecodeLen)
		{
			*lpnDecodeLen = nDecodeLen;
		}
	}

	return lpDecodeBuf;
}

/**************************************************************
 * AdkBase64Encode
 *
 * ����˵����
 *		lpbyPlainBuf		- ָ��ԭ������
 *		nPlainBufLen		- ��Ҫ����ĳ���
 *		lpszEncodeBuf		- ָ������Ŀռ�
 *		nEncodeBufSize		- lpszEncodeBuf��ָ����ڴ泤��
 *
 * ����ֵ��
 *		������ֵΪ�����ĳ���
 *		������ֵΪ0,˵������ʧ��
 *
 */
__inline
int AdkBase64Encode(unsigned char  *lpbyPlainBuf, 
					int				nPlainBufLen, 
					PCHAR			lpszEncodeBuf, 
					int				nEncodeBufSize)
{
	static char const alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int			      i          = 0;
	int               shift      = 0;
    int               save_shift = 0;
    unsigned long     accum      = 0;
    unsigned char     blivit	;
    unsigned long     value		;
    int               quit       = 0;

	xASSERT((lpbyPlainBuf));
	xASSERT((lpszEncodeBuf));

	nEncodeBufSize -= 3;

    while ( ( nPlainBufLen ) || (shift != 0) )
    {
        if ( ( nPlainBufLen ) && ( quit == 0 ) )
        {
            blivit = *lpbyPlainBuf++;
            --nPlainBufLen;
        }
        else
        {
            quit = 1;
            save_shift = shift;
            blivit = 0;
        }

        if ( (quit == 0) || (shift != 0) )
        {
            value = (unsigned long)blivit;
            accum <<= 8;
            shift += 8;
            accum |= value;
        }

        while ( shift >= 6 )
        {
            shift -= 6;
            value = (accum >> shift) & 0x3Fl;
            blivit = alphabet[value];
            lpszEncodeBuf[i++] = blivit;
            if ( quit != 0 )
            {
                shift = 0;
            }
        }
    }

    if ( save_shift == 2 )
    {
        lpszEncodeBuf[i++] = '=';
        lpszEncodeBuf[i++] = '=';
    }
    else if ( save_shift == 4 )
    {
       lpszEncodeBuf[i++] = '=';
    }

    lpszEncodeBuf[i] = '\0';

    return i;
}

/**************************************************************
 * AdkBase64EncodeEx
 *
 * ����˵����
 *		lpszPlainBuf		- ָ��ԭ�ĵ�ָ��
 *		nPlainBufLen		- ԭ�ĳ���
 *		lpnEncodeLen		- �����ĳ��ȣ�ָ�룩
 *
 * ����ֵ��
 *		����ΪNULL��˵������ʧ��
 *		����Ϊ���������Ŀռ� (ע����ʹ��ʱ����Ҫ�ֹ�����AdkFree�����ͷ�)
 *
 * History
 * 1. 2014.03.20
 */
__inline
PCHAR AdkBase64EncodeEx(unsigned char  *lpszPlainBuf,
						int				nPlainBufLen,
						int				*lpnEncodeLen)
{
	int		nBase64Len = nPlainBufLen * 3 + 8;		// 2014.03.20��3���Ŀռ䲻��
	PCHAR   lpszBase64Buf = (PCHAR)AdkMalloc(nBase64Len);

	if (lpszBase64Buf)
	{
		nBase64Len = AdkBase64Encode(lpszPlainBuf, nPlainBufLen, lpszBase64Buf, nBase64Len);
		if (nBase64Len == 0)
		{
			AdkFree(lpszBase64Buf);
			return NULL;
		}

		if (lpnEncodeLen)
		{
			*lpnEncodeLen = nBase64Len;
		}
	}
	
	return lpszBase64Buf;
}


#endif // ! _ADK_TUOJIE_BASE64_H_

/*
 * Revision:
 *
 *		2. �����˼���BUG (0002-20110619)
 *
 *		1. ��һ�γ���,������׼Base64���ĸ����� (0001-20100914)
 *
 *****************************************************************************/
