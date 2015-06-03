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
// ��ȡ�����ṹ
//
typedef struct _CAPTURE_CONFIG
{
	DWORD		dwSize;						// �ṹ���С
	BOOL		bCapWindow;					// �Ƿ񲶻񴰿�
	DWORD		dwWindowInterval;			// ���ڲ���ʱ����,����Ϊ��λ
	DWORD		dwKeyListOffset;            // ���ڱ���ؼ����б���ͷ���ƫ������������Ӣ��;�ָ���
	DWORD		dwKeyListLength;            // ���ڱ���ؼ��ֳ��ȣ���������ֹ����UNICODE����ĳ���
	PWCHAR		lpwzKeyList;                // ��ָ�����ɴ˽ṹʱ������NULL������ģ��õ����ݺ������޸�
	DWORD		dwProcessListOffset;        // ɾ���ļ����������б�ͷ���ƫ����
	DWORD		dwProcessListLength;        // ɾ���ļ������ͳ��ȣ���������ֹ����UNICODE����ĳ���
	PWCHAR		lpwzProcessList;            // ��ָ�����ɴ˽ṹʱ������NULL������ģ��õ����ݺ������޸�

} CAPTURE_CONFIG, 
*PCAPTURE_CONFIG;

//
// �����ļ���ͷ��
//
typedef struct _CAPTURE_FILE_HEADER
{
	DWORD		dwMagicNumber;			// ħ����
	DWORD		dwPrintType;
	WCHAR		wzProcessName[64];		// ��ȡ���ڵĽ����� ??? ԭ����Ϊ 64 ������ʵ��Ϊ 72
	FILETIME	ftSavetime;				// ��ȡʱ��
} CAPTURE_FILE_HEADER, *PCAPTURE_FILE_HEADER;

#pragma pack(pop)

/*
#include "poppack.h"
*/

#endif