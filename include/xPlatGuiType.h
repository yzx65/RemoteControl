/***************************************************************************
 * Module:
 *       xPlatGuiType.h
 *
 * Author:
 *		XieBo(secman_xie@hotmail.com)
 *
 * Time:
 *		2011-05,Nanjing
 *
 * Notes:
 *		驻留平台供各产品使用的导出函数
 *
 * Example:
 * 
    HMODULE hMod = LoadLibrary(L"E:\\VS2010\\xPlat2\\Debug\\xPlatGui.dll");
	LPXPLATGUIINIT lpfnxPlatGui ;
	XPLAT_FUNCTION_POINTER xPlatFunc;

	if ( hMod )
	{
		lpfnxPlatGui = (LPXPLATGUIINIT)GetProcAddress(hMod, "xPlatGuiInit");
		if ( lpfnxPlatGui )
		{
			lpfnxPlatGui(&xPlatFunc);

			xPlatFunc.lpfnNewFile();

			xPlatFunc.lpfnAddFile(L"D:\\Temp\\1.cfg", L"Data\\11.cfg", XPLAT_GUI_FILE_TYPE_0);
			xPlatFunc.lpfnAddFile(L"D:\\Temp\\1.dll", L"11.dll", XPLAT_GUI_FILE_TYPE_1);
			xPlatFunc.lpfnAddFile(L"D:\\Temp\\2.dll", L"22.dll", XPLAT_GUI_FILE_TYPE_0);

			xPlatFunc.lpfnShowGui(g_hWnd, XPLAT_GUI_PRODUCT_ID0);   // T5
		}
		FreeLibrary(hMod);
	}
 *
 * History:
 *
 */
#ifndef _XPLAT_GUI_TYPE_H_
#define _XPLAT_GUI_TYPE_H_

#include "AdkPrecomp.h"

// //////////////////////////////////////////////////////////////////
// 一些常量
//

// 文件类型
// 此处的值与xPlatType.h中的值对应
//
#define XPLAT_GUI_FILE_TYPE_0                     0         // 不需要加载的文件
#define XPLAT_GUI_FILE_TYPE_1                     1         // 需要加载的DLL
#define XPLAT_GUI_FILE_TYPE_2                     10        // 需要加载的64位DLL

#define MAX_FILE_COUNTER                          16         // 最大文件数量

// 产品ID
//
#define XPLAT_GUI_ANTIVIRUS                       0          // 支持的杀毒软件列表
#define XPLAT_GUI_PRODUCT_ID_T5                   1          // T5000
#define XPLAT_GUI_PRODUCT_ID_T3                   2          // T3000
#define XPLAT_GUI_PRODUCT_ID_E3                   3          // E3000

// //////////////////////////////////////////////////////////////////
// 供用户调用的函数原型
//
typedef VOID (WINAPI *LPNEWFILE)();                                      // 新的生成任务
typedef BOOL (WINAPI *LPADDFILE)(LPCWSTR lpwzLocalFileName, LPCWSTR lpwzTargetFileName, DWORD dwFileType, BOOL bRc4Encrypt);// 增加文件
typedef BOOL (WINAPI *LPADDFILEDLL2DAT)(LPCWSTR lpwzLocalFileName, LPCWSTR lpwzTargetFileName, DWORD dwFileType, BOOL bRc4Encrypt);// 增加DLL文件，要求变换为DAT
typedef VOID (WINAPI *LPSHOWGUI)(HWND hWnd, DWORD dwProductId);          // 显示界面

// //////////////////////////////////////////////////////////////////
// 一些函数指针
//
typedef struct _XPLAT_FUNCTION_POINTER
{
	// DLL提供给上层的功能函数
	//
	LPNEWFILE         lpfnNewFile;
	LPADDFILE         lpfnAddFile;
	LPADDFILEDLL2DAT  lpfnAddFileDll2Dat;
	LPSHOWGUI         lpfnShowGui;

} XPLAT_FUNCTION_POINTER, *LPXPLAT_FUNCTION_POINTER;


// //////////////////////////////////////////////////////////////////
// DLL导出的函数原型
//
typedef BOOL (WINAPI *LPXPLATGUIINIT)(LPXPLAT_FUNCTION_POINTER lpFunctionPointer);


#endif // !_XPLAT_GUI_TYPE_H_