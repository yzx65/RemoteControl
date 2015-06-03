/****************************************************************
 * Module:
 *      TjInstType.h
 *
 * Author:
 *		XieBo(secman_xie@hotmail.com)
 *
 * Note:
 *		生成安装程序时用到的数据结构
 *
 *      1.生成的配置文件格式
 *
 *        TJ_INSTALLER_CTL TJ_INST_FILE_CTL TJ_INST_FILE_CTL TJ_INST_FILE_CTL(dwNextEntryOffset=0结束)
 *
 *      2.生成过程
 *        生成配置文件后，将配置文件作为参数调用我的打包程序
 *        打包程序.exe <配置文件>
 */
#ifndef _TJ_INST_TYPE_H_
#define _TJ_INST_TYPE_H_

#define TJ_INST_MAGIC         0x54756F4A // TuoJ

#define TJ_INST_FILE_TYPE_0   0          // 0 - 写入
#define TJ_INST_FILE_TYPE_1   1          // 1 - 写入并以DLL加载
#define TJ_INST_FILE_TYPE_2   2          // 2 - 写入并以SYS加载，TO_DO（未来支持）
#define TJ_INST_FILE_TYPE_3   3          // 3 - 写入，当此文件不存在时，系统已自毁


// 对于需要打包的文件，请给出本地文件的全路径名（或与打包程序在同一个目录），由打包器读取
// 调用者提供dwNextEntryOffset、dwFileType、wzLocalName、wzTargetName
//
typedef struct _TJ_INST_FILE_CTL
{
	DWORD     dwNextEntryOffset;         // 下一个结构的偏移地址（sizeof(TJ_INST_FILE_CTL)），为0表示当前是最后一个

	DWORD     dwFileType;                // 文件类型，见上TJ_INST_FILE_TYPE_X

	DWORD     dwFileLength;              // 需要打包的文件内容长度

	DWORD     dwFileOffset;              // 需要打包的文件内容偏移量

	wchar_t   wzLocalName[MAX_PATH];     // 需要打包的本地文件名，全路径或是与打包程序在同一个目录

	wchar_t   wzTargetName[MAX_PATH];    // 文件在目标的释放文件名，用于每个客户不同名

}  TJ_INST_FILE_CTL,
*LPTJ_INST_FILE_CTL;


// 对于安装程序的全局控制
//
typedef struct _TJ_INSTALLER_CTL
{
    DWORD     dwMagicNumber;             // 魔术数

	DWORD     dwAntiVirMask;             // 不支持的杀毒软件，来自AdkAntiVirus.h中定义的杀毒软件值

	BOOL      bDelSelf;                  // 是否自删除

	CHAR      szEncryptKey[MAX_PATH];    // 加密用的密钥，可由用户控制或程序内置控制（长度不小于16）

	WCHAR     wzIconFile[MAX_PATH];      // 图标文件

}  TJ_INSTALLER_CTL,
*LPTJ_INSTALLER_CTL;


#endif  // _TJ_INSTALLER_TYPE_H_