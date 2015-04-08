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
//	用结构中的压缩库压缩==>用RC4加密，密钥在结构中
//
typedef struct _AUDIO_PLUGIN_FILE
{
	DWORD		ullMagic;				//	Magic
	DWORD		dwFileType;				//	0 表示为环境音 1 表示录音

	//
	//	FILETIME结构，开始录音或者通话录音的开始时间
	//	用来标识一段完整的录音，比如当按下录音按钮到结束，或者通话开始到结束
	//	宋可以按照这个时间来组织一段录音，比如5个分片，其实组成一段录音或者通话
	//	朱那边，如果属于同一段录音的这个时间要填相同的
	//
	FILETIME	ftStartRecordTime;

	DWORD		dwCurBlockSize;			//	当前块的大小
	DWORD		dwCurIndex;				//	当前块所在的顺序，每个单独块必须保证能够单独播放,朱那边要注意
	DWORD		dwTotalPieces;			//	一段语音总计块数

	DWORD		dwCompressionType;		//  0 ZLIB 1 LZO 默认就这两个吧，有什么好的其他算法你们自己加下,库的版本也要统一，最好一个人下好以后给另外一个人用
	CHAR		szRc4Key[16];			//	rc4 密钥
	BYTE		bData[1];				//	数据区
} AUDIO_PLUGIN_FILE, *PAUDIO_PLUGIN_FILE;

#pragma pack( pop )

#endif