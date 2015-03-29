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
 *		共享的内存映射文件
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

// 区域划分
// 0   ~ 16K   基础DLL保存的一些信息，结构在PUBLIC_FILE_MAP中定义
// 16K ~ 48K   用于T5的交互
#define T5_OFFSET    (16*1024)

typedef void (*LPTHREADATTACH)();      // 被加载的DLL的处理DLL_THREAD_ATTACH事件的函数原型
typedef void (*LPTHREADDETACH)();      // 被加载的DLL的处理DLL_THREAD_DETACH事件的函数原型
typedef void (*LPPROCESSDETACH)();     // 被加载的DLL的处理DLL_PROCESS_DETACH事件的函数原型

typedef void *HMEMORYMODULE;
typedef HMEMORYMODULE (*LPLOADLIBRARYW)(LPWSTR);
typedef FARPROC (*LPGETPROCADDRESS)(HMEMORYMODULE, const char *);
typedef void (*LPFREELIBRARY)(HMEMORYMODULE);
typedef void (*LPREGISTERTHREADATTACH)(LPTHREADATTACH);
typedef void (*LPREGISTERTHREADDETACH)(LPTHREADDETACH);
typedef void (*LPREGISTERPROCESSDETACH)(LPPROCESSDETACH);


#pragma pack(push)
#pragma pack(1)

// 基础DLL保存的一些信息
//
typedef struct _PUBLIC_FILE_MAP {

	DWORD                   dwMagic;                    // Magic Number， PUBLIC_MAGIC
	WCHAR                   wzProcName[MAX_PATH];       // 进程全路径名
	WCHAR                   wzModuleFileName[MAX_PATH]; // 驻留DLL文件全路径名
	BOOL                    bOnlyExe;                   // 只进了一个进程
	LPLOADLIBRARYW          lpLoadLibraryW;             // 加载特定格式的DAT文件，格式在MEM_LOADER中定义
	LPGETPROCADDRESS        lpGetProcAddress;           // 获取函数地址
	LPFREELIBRARY           lpFreeLibrary;              // FreeLibrary
	LPREGISTERTHREADATTACH  lpRegisterThreadAttach;     // 在DLL被加载时，调用此函数，设置处理DLL_THREAD_ATTACH事件的函数指针
	LPREGISTERTHREADDETACH  lpRegisterThreadDetach;     // 在DLL被加载时，调用此函数，设置处理DLL_THREAD_DETACH事件的函数指针
	LPREGISTERPROCESSDETACH lpRegisterProcessDetach;    // 在DLL被加载时，调用此函数，设置处理DLL_PROCESS_DETACH事件的函数指针

} PUBLIC_FILE_MAP, *LPPUBLIC_FILE_MAP;

// DLL文件的保存格式
//
typedef struct _MEM_LOADER {

	DWORD  dwMagic;                              // MEMORY_MAGIC
	CHAR   szRc4Key[64];                         // 需要\0结尾符号
	DWORD  dwLen;

} MEM_LOADER, *LPMEM_LOADER;

#pragma pack(pop)

#endif // !_PUBLIC_FILE_MAP_H_