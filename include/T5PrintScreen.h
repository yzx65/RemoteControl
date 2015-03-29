#ifndef _PRINT_SCREEN_H
#define _PRINT_SCRREN_H

#define		PRINT_SCREEN_MAGIC			0xFE801972
#define		KEYPROCESSWND				0x100
#define		KEYTITLEWINDOW				0x200
#define		FULLSCREEN					0x400

#define		THE_SAME_WINDOW(_LAST_WND)	\
	((_LAST_WND) == GetForegroundWindow())

#pragma pack(push)
#pragma pack(1)

//
// 截取参数结构
//
typedef struct _CAPTURE_CONFIG
{
	DWORD		dwSize;						// 结构体大小
	BOOL		bCapWindow;					// 是否捕获窗口
	DWORD		dwWindowInterval;			// 窗口捕获时间间隔,以秒为单位
	DWORD		dwKeyListOffset;            // 窗口标题关键字列表在头后的偏移量，内容以英文;分隔，
	DWORD		dwKeyListLength;            // 窗口标题关键字长度，不包含截止符，UNICODE编码的长度
	PWCHAR		lpwzKeyList;                // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改
	DWORD		dwProcessListOffset;        // 删除文件的类型在列表头后的偏移量
	DWORD		dwProcessListLength;        // 删除文件的类型长度，不包含截止符，UNICODE编码的长度
	PWCHAR		lpwzProcessList;            // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改

} CAPTURE_CONFIG, 
*PCAPTURE_CONFIG;

//
// 保存文件的头部
//
typedef struct _CAPTURE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// 魔术数
	DWORD		dwPrintType;
	WCHAR		wzProcessName[64];		// 截取窗口的进程名 ??? 原长度为 64 ，但是实际为 72
	FILETIME	ftSavetime;				// 截取时间
} CAPTURE_FILE_HEADER, *PCAPTURE_FILE_HEADER;

#pragma pack(pop)

/*
#include "poppack.h"
*/

#endif