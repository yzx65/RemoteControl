/***************************************************************************
 * Module:
 *       PublicFileMap.h
 *
 * Author:
 *		XieBo(secman_xie@hotmail.com)
 *
 * Time:
 *		
 *
 * Notes:
 *		������ڴ�ӳ���ļ�
 *
 * Functions:
 *
 *     
 *
 * History:
 *
 *
 */
#ifndef _PUBLIC_FILE_MAP_H_
#define _PUBLIC_FILE_MAP_H_

#define PUBLIC_MAGIC  0x98765432
#define MEMORY_MAGIC  0x74965872

// the length of a mapping object
//
#define MAXIMUM_SIZE_HIGH      0          // A high-order DWORD for the maximum size of a file mapping object. 
#define MAXIMUM_SIZE_LOW       (128*1024) // A low-order DWORD for the maximum size of a file mapping object

// ���򻮷�
// 0   ~ 16K   ����DLL�����һЩ��Ϣ���ṹ��PUBLIC_FILE_MAP�ж���
// 16K ~ 48K   ����T5�Ľ���
#define T5_OFFSET    (16*1024)

typedef void (*LPTHREADATTACH)();      // �����ص�DLL�Ĵ���DLL_THREAD_ATTACH�¼��ĺ���ԭ��
typedef void (*LPTHREADDETACH)();      // �����ص�DLL�Ĵ���DLL_THREAD_DETACH�¼��ĺ���ԭ��
typedef void (*LPPROCESSDETACH)();     // �����ص�DLL�Ĵ���DLL_PROCESS_DETACH�¼��ĺ���ԭ��

typedef void *HMEMORYMODULE;
typedef HMEMORYMODULE (*LPLOADLIBRARYW)(LPWSTR);
typedef FARPROC (*LPGETPROCADDRESS)(HMEMORYMODULE, const char *);
typedef void (*LPFREELIBRARY)(HMEMORYMODULE);
typedef void (*LPREGISTERTHREADATTACH)(LPTHREADATTACH);
typedef void (*LPREGISTERTHREADDETACH)(LPTHREADDETACH);
typedef void (*LPREGISTERPROCESSDETACH)(LPPROCESSDETACH);


#pragma pack(push)
#pragma pack(1)

// ����DLL�����һЩ��Ϣ
//
typedef struct _PUBLIC_FILE_MAP {

	DWORD                   dwMagic;                    // Magic Number�� PUBLIC_MAGIC
	WCHAR                   wzProcName[MAX_PATH];       // ����ȫ·����
	WCHAR                   wzModuleFileName[MAX_PATH]; // פ��DLL�ļ�ȫ·����
	BOOL                    bOnlyExe;                   // ֻ����һ������
	LPLOADLIBRARYW          lpLoadLibraryW;             // �����ض���ʽ��DAT�ļ�����ʽ��MEM_LOADER�ж���
	LPGETPROCADDRESS        lpGetProcAddress;           // ��ȡ������ַ
	LPFREELIBRARY           lpFreeLibrary;              // FreeLibrary
	LPREGISTERTHREADATTACH  lpRegisterThreadAttach;     // ��DLL������ʱ�����ô˺��������ô���DLL_THREAD_ATTACH�¼��ĺ���ָ��
	LPREGISTERTHREADDETACH  lpRegisterThreadDetach;     // ��DLL������ʱ�����ô˺��������ô���DLL_THREAD_DETACH�¼��ĺ���ָ��
	LPREGISTERPROCESSDETACH lpRegisterProcessDetach;    // ��DLL������ʱ�����ô˺��������ô���DLL_PROCESS_DETACH�¼��ĺ���ָ��

} PUBLIC_FILE_MAP, *LPPUBLIC_FILE_MAP;

// DLL�ļ��ı����ʽ
//
typedef struct _MEM_LOADER {

	DWORD  dwMagic;                              // MEMORY_MAGIC
	CHAR   szRc4Key[64];                         // ��Ҫ\0��β����
	DWORD  dwLen;

} MEM_LOADER, *LPMEM_LOADER;

#pragma pack(pop)

#endif // !_PUBLIC_FILE_MAP_H_