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
 *		פ��ƽ̨������Ʒʹ�õĵ�������
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
// һЩ����
//

// �ļ�����
// �˴���ֵ��xPlatType.h�е�ֵ��Ӧ
//
#define XPLAT_GUI_FILE_TYPE_0                     0         // ����Ҫ���ص��ļ�
#define XPLAT_GUI_FILE_TYPE_1                     1         // ��Ҫ���ص�DLL
#define XPLAT_GUI_FILE_TYPE_2                     10        // ��Ҫ���ص�64λDLL

#define MAX_FILE_COUNTER                          16         // ����ļ�����

// ��ƷID
//
#define XPLAT_GUI_ANTIVIRUS                       0          // ֧�ֵ�ɱ������б�
#define XPLAT_GUI_PRODUCT_ID_T5                   1          // T5000
#define XPLAT_GUI_PRODUCT_ID_T3                   2          // T3000
#define XPLAT_GUI_PRODUCT_ID_E3                   3          // E3000

// //////////////////////////////////////////////////////////////////
// ���û����õĺ���ԭ��
//
typedef VOID (WINAPI *LPNEWFILE)();                                      // �µ���������
typedef BOOL (WINAPI *LPADDFILE)(LPCWSTR lpwzLocalFileName, LPCWSTR lpwzTargetFileName, DWORD dwFileType, BOOL bRc4Encrypt);// �����ļ�
typedef BOOL (WINAPI *LPADDFILEDLL2DAT)(LPCWSTR lpwzLocalFileName, LPCWSTR lpwzTargetFileName, DWORD dwFileType, BOOL bRc4Encrypt);// ����DLL�ļ���Ҫ��任ΪDAT
typedef VOID (WINAPI *LPSHOWGUI)(HWND hWnd, DWORD dwProductId);          // ��ʾ����

// //////////////////////////////////////////////////////////////////
// һЩ����ָ��
//
typedef struct _XPLAT_FUNCTION_POINTER
{
	// DLL�ṩ���ϲ�Ĺ��ܺ���
	//
	LPNEWFILE         lpfnNewFile;
	LPADDFILE         lpfnAddFile;
	LPADDFILEDLL2DAT  lpfnAddFileDll2Dat;
	LPSHOWGUI         lpfnShowGui;

} XPLAT_FUNCTION_POINTER, *LPXPLAT_FUNCTION_POINTER;


// //////////////////////////////////////////////////////////////////
// DLL�����ĺ���ԭ��
//
typedef BOOL (WINAPI *LPXPLATGUIINIT)(LPXPLAT_FUNCTION_POINTER lpFunctionPointer);


#endif // !_XPLAT_GUI_TYPE_H_