#ifndef _PAKAGE_H
#define _PAKAGE_H

//��������
BOOL SetPwdRes(HINSTANCE hDll,_TCHAR* dll_path,_TCHAR* pwdStr)
//���������ļ�
BOOL EncryptDriverFile(HINSTANCE hDll,_TCHAR* driver_src_path,_TCHAR* driver_dst_path)
//�������ļ�����dll��Դ��
BOOL AddDriverFile(HINSTANCE hDll,_TCHAR* driver_src_path,_TCHAR* dll_dst_path);
//��dll���뵽��װ������Դ
BOOL AddDLLFile(HINSTANCE hDll,_TCHAR* src_dll_path,_TCHAR* dst_install_path);
#endif