/**************************************************************
 * Module:
 *      common.h
 *
 * Author:
 *      DING ZAHOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2009-10-05,Nanjing
 *
 * Notes:
 *		Common Struct For T4000(T5000)
 *
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <winsock2.h>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
using namespace std;

// 每次读取文件的块长度
//
#define FILE_BLOCK_LENGTH			(1024*4)

// 编译区别OEM版本
//
//#define T5000_OEM

// 编译区别单用户版和多用户版
//
#define MULTIUSER_CONTROL

#define OS_WIN2K					(2195)
#define OS_WINXP					(2600)
#define OS_WIN2003					(3790)				// XP 64位也是3790
#define OS_WINVISTA					(6000)
#define OS_WIN2008					(6001)
#define OS_WINVISTASP2				(6002)
#define OS_WIN7PRO					(7600)				// 2008 R2也是7600
#define OS_WIN7SP1					(7601)				// SP1
#define OS_WIN8						(9200)
#define OS_WIN8_PREVIEW				(9431)
#define OS_WIN81					(9600)

#define MACOS_X_VERSION_10_4   (100400)
#define MACOS_X_VERSION_10_6   (100600)
#define MACOS_X_VERSION_10_7   (100700)
#define MACOS_X_VERSION_10_8   (100800)
#define MACOS_X_VERSION_10_9   (100900)
#define MACOS_X_VERSION_10_10  (101000)

#define IOS_VERSION_1 (200001)
#define IOS_VERSION_2 (200002)
#define IOS_VERSION_3 (200003)
#define IOS_VERSION_4 (200004)
#define IOS_VERSION_5 (200005)
#define IOS_VERSION_6 (200006)
#define IOS_VERSION_7 (200007)
#define IOS_VERSION_8 (200008)

#define ANDROID_2_0_VERSION					0x20000
#define ANDROID_2_1_VERSION					0x20100
#define ANDROID_2_2_VERSION					0x20200
#define ANDROID_2_3_VERSION					0x20300
#define ANDROID_4_0_VERSION					0x40000
#define ANDROID_4_1_VERSION					0x40100
#define ANDROID_4_2_VERSION					0x40200
#define ANDROID_4_3_VERSION					0x40300
#define ANDROID_4_4_VERSION					0x40400
#define ANDROID_5_0_VERSION					0x50000
#define ANDROID_5_1_VERSION					0x50100
#define ANDROID_5_2_VERSION					0x50200

typedef enum tagSystemType
{
	SYSTEM_WINDOWS,
	SYSTEM_MACOSX,
	SYSTEM_IOS,
	SYSTEM_ANDROID,
	SYSTEM_UNKNOWN
}SystemType;

// 连接区别码 (用于使用同一端口进行通信时对不同类型的连接进行区别)
//

#define TARGET_CONN_IDENTITY				"0 0 IDE TARG\r\n"
#define CONTROL_CONN_IDENTITY				"0 0 IDE CONT\r\n"
#define CONTROL_FILECONN_IDENTITY			"0 0 IDE COFI\r\n"

#define MAC_OS_TARGET_CONN_IDENTITY         "0 1 IDE TARG\r\n"
#define IOS_TARGET_CONN_IDENTITY            "1 0 IDE TARG\r\n"

#define DAEMON_DEFPORT_FORTARGET			(8080)
#define DAEMON_DEFCTRPORT_FORCONTROL		(8088)
#define DAEMON_DEFDATAPORT_FORCONTROL		(8089)

//
// 目标相关属性
//

typedef enum _TargetStatus
{
	TAROFFLINE=0,
	TARONLINE

} TargetStatus;

 //
 // 中转服务器配置参数
 //

typedef struct _DAEMON_PARAM
{
	BYTE	    byShowWindow;
	BYTE	    byLogFile;
    USHORT      usPortForTarget;
	USHORT		usCtrPortForControl;
	USHORT		usDataPortForControl;
	USHORT		usPortForManager;

	BYTE		byPassHash[16];

} DAEMON_PARAM,
* PDAEMON_PARAM;

//
// 插件相关变量及结构
//

#define MAX_PLG_COUNT		(32)

// Load type
//
#define AUTO_LOAD			0
#define COMMAND_LOAD		1

// UpdateType
//
#define DEFAULT_UPDATE		0
#define DEFAULT_NO_UPDATE	1

/**************************************************************
 *	GetIPStrFromInt32 @@ADK
 * 
 */
__inline
PCHAR GetIPStrFromInt32(int nIp)
{
    in_addr     inAddrIp;

    inAddrIp.S_un.S_addr = nIp;

	return inet_ntoa(inAddrIp);
}

#endif // __COMMON_H__