// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� DLL_UNZIPCAPFILE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// DLL_UNZIPCAPFILE_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef _XQT_DLL_UNZIPCAPFILE_H_
#define _XQT_DLL_UNZIPCAPFILE_H_

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifdef DLL_UNZIPCAPFILE_EXPORTS
#define DLL_UNZIPCAPFILE_API __declspec(dllexport)
#else
#define DLL_UNZIPCAPFILE_API __declspec(dllimport)
#endif

DLL_UNZIPCAPFILE_API
BOOL WINAPI UnzipCapFile(const PWCHAR lpwzFileName, const PWCHAR lpwzSavePath, BOOL bDelFileWhenUnziped);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif // _XQT_DLL_UNZIPCAPFILE_H_