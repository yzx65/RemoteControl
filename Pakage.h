#ifndef _PAKAGE_H
#define _PAKAGE_H
extern "C"
{
	//��������
	typedef BOOL (*SetPwdRes)(HINSTANCE hDll,wchar_t* dll_path,wchar_t* pwdStr);
	//���������ļ�
	typedef BOOL (*EncryptDriverFile)(HINSTANCE hDll,wchar_t* driver_src_path,wchar_t* driver_dst_path);
	//�������ļ�����dll��Դ��
	typedef BOOL (*AddDriverFile)(HINSTANCE hDll,wchar_t* driver_src_path,wchar_t* dll_dst_path);
	//��dll���뵽��װ������Դ
	typedef BOOL (*AddDLLFile)(HINSTANCE hDll,wchar_t* src_dll_path,wchar_t* dst_install_path);

	typedef BOOL (*AddResFile)(HINSTANCE hDll,wchar_t* src_res_path,wchar_t* dst_install_path,wchar_t* resName);
};

#endif