#ifndef _PAKAGE_H
#define _PAKAGE_H

//设置密码
BOOL SetPwdRes(HINSTANCE hDll,_TCHAR* dll_path,_TCHAR* pwdStr)
//加密驱动文件
BOOL EncryptDriverFile(HINSTANCE hDll,_TCHAR* driver_src_path,_TCHAR* driver_dst_path)
//将驱动文件打入dll资源里
BOOL AddDriverFile(HINSTANCE hDll,_TCHAR* driver_src_path,_TCHAR* dll_dst_path);
//将dll打入到安装程序资源
BOOL AddDLLFile(HINSTANCE hDll,_TCHAR* src_dll_path,_TCHAR* dst_install_path);
#endif