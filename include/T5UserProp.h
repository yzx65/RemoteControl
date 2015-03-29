/**************************************************************
 * Module:
 *        T5UserProp.h
 *
 * Author:
 *        DING ZhaoKun (dzkad@hotmail.com)
 *
 * Time:
 *        2007-3-8, Nanjing
 *
 * Notes
 *
 *
 */

#ifndef _TI_T5_DZK_USERPROP_H_
#define _TI_T5_DZK_USERPROP_H_

//
// Communication Port Info
//
#define KJET_DAEMON_PORT					(8080)
#define KJET_TARGET_PORT					(2088)

//
// 平台相关常量
//

#define T5_DIR								L"Data"
#define T5_DELFILE_LIST						L"ttl.dat"
#define T5_SNIPPET_DIR						L"utd_CE31"

#define T5_CFGFILE							L"Dtl.dat"
#define T5_PLUGIN_CFGFILE					L"glp.uin"
#define T5_UPDATE_DIR						L"update"

// 插件1常量
//
#define MUTEX_NETWORK_PROCESS			"Global\\{A8859547-C62D-4e8b-A82D-BE1479C684C9}"
#define MUTEX_MEMORY_SHAREDATA			"Global\\{3C6FB3CA-69B1-454f-8B2F-BD157762810E}"
#define MUTEX_CFGDATA					"Global\\{A59CF429-D0DD-4207-88A1-04090680F714}"
#define MUTEX_MANAGER_PROCESS			"Global\\{43EE34A9-9063-4d2c-AACD-F5C62B849089}"
#define CAP_CUTOFFNET_EVENTNAME			"Global\\{34748A26-4EAD-4331-B039-673612E8A5FC}"


#endif // _TI_T5_DZK_USERPROP_H_