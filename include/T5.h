/**************************************************************
 * Module:
 *      t5.h
 *
 * Author:
 *      DING ZAHOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2009-10-05,Nanjing
 *
 * Notes:
 *		三端共用的结构
 *
 */

#ifndef __T5_H__
#define __T5_H__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#pragma pack( push )
#pragma pack(1)

//
// 反弹地址结构
//

#define DAEMON_IP_ADDR			0
#define DAEMON_DOMAIN_ADDR		1

typedef struct 
{
	DWORD	dwAddrType;
	DWORD	dwPort;
	DWORD	dwIp;
	CHAR	szDomainName[128];

} DAEMONADDR,
*PDAEMONADDR;

//
// 目录文件的头部
//

typedef struct tagDirInfoHeader
{
	DWORD			dwSize;
	DWORD			dwMagic;
	DWORD			dwLevel;
	LARGE_INTEGER	liGetTime;			// 获取目录的时间

} DirInfoHeader,
*PDirInfoHeader;

#pragma pack( pop )

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__T5_H__