// 下列 ifdef 块是创建使从 DLL 导出更简单的
//宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLL_UNZIPCAPFILE_EXPORTS
// 符号编译的。在使用此 DLL 的
//任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将 
// DLL_UNZIPCAPFILE_API 函数视为是从此 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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