#ifndef _AUDIO_PLG_H
#define _AUDIO_PLG_H

#pragma pack( push )
#pragma pack(1)

#define AUDIO_FILE_MAGIC		0x49445541

#ifdef _WIN32
#include <windows.h>
#else

typedef unsigned long            DWORD;

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

#endif

//
//	�ýṹ�е�ѹ����ѹ��==>��RC4���ܣ���Կ�ڽṹ��
//
typedef struct _AUDIO_PLUGIN_FILE
{
	DWORD		ullMagic;				//	Magic
	DWORD		dwFileType;				//	0 ��ʾΪ������ 1 ��ʾ¼��

	//
	//	FILETIME�ṹ����ʼ¼������ͨ��¼���Ŀ�ʼʱ��
	//	������ʶһ��������¼�������統����¼����ť������������ͨ����ʼ������
	//	�ο��԰������ʱ������֯һ��¼��������5����Ƭ����ʵ���һ��¼������ͨ��
	//	���Ǳߣ��������ͬһ��¼�������ʱ��Ҫ����ͬ��
	//
	FILETIME	ftStartRecordTime;

	DWORD		dwCurBlockSize;			//	��ǰ��Ĵ�С
	DWORD		dwCurIndex;				//	��ǰ�����ڵ�˳��ÿ����������뱣֤�ܹ���������,���Ǳ�Ҫע��
	DWORD		dwTotalPieces;			//	һ�������ܼƿ���

	DWORD		dwCompressionType;		//  0 ZLIB 1 LZO Ĭ�Ͼ��������ɣ���ʲô�õ������㷨�����Լ�����,��İ汾ҲҪͳһ�����һ�����º��Ժ������һ������
	CHAR		szRc4Key[16];			//	rc4 ��Կ
	LONGLONG	dwDuration;				//	ʱ��
	BYTE		bData[1];				//	������
} AUDIO_PLUGIN_FILE, *PAUDIO_PLUGIN_FILE;

#pragma pack( pop )

#endif