#ifndef _PAKAGE_H
#define _PAKAGE_H
extern "C"
{
	//设置密码
	typedef BOOL (*SetPwdRes)(HINSTANCE hDll,wchar_t* dll_path,wchar_t* pwdStr);
	//加密驱动文件
	typedef BOOL (*EncryptDriverFile)(HINSTANCE hDll,wchar_t* driver_src_path,wchar_t* driver_dst_path);
	//将驱动文件打入dll资源里
	typedef BOOL (*AddDriverFile)(HINSTANCE hDll,wchar_t* driver_src_path,wchar_t* dll_dst_path);
	//将dll打入到安装程序资源
	typedef BOOL (*AddDLLFile)(HINSTANCE hDll,wchar_t* src_dll_path,wchar_t* dst_install_path);

	typedef BOOL (*AddResFile)(HINSTANCE hDll,wchar_t* src_res_path,wchar_t* dst_install_path,wchar_t* resName);
};

#endif