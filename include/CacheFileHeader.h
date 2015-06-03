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
 *		�Զ��ش����ļ�
 *			USB��Ŀ¼�б���
 *			USB���ļ�����
 *			ɾ���ļ�����
 *			�����ļ����
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
// �Զ��ش����ļ�����
//
#define	CACHED_USBFILE		0x0001
#define CACHED_USBDIR		0x0002
#define	CACHED_DELFILE		0x0003
#define SEARCHED_FILE		0x0004

// 
// ��������Ľṹ����ǰ�˺Ϳ��ƶ�ʹ�ã���ͳһ���ֽڶ���Ϊ1�ֽ�
//
#pragma pack(1)

//
// �ļ����� ͷ��
//
typedef struct tag_TCACHED_FILE_HEADER
{
	DWORD		dwSingnature;				// ��ʶ
	DWORD		dwHeaderType;				// ͷ����
	DWORD		dwHeaderSize;				// ͷ��С

	WCHAR		wzRealPath[MAX_PATH];		// �ļ�ԭ·��
	DWORD		dwFileSize;					// �ļ���С

	FILETIME	ftCreationTime;				// �ļ�����ʱ��
	FILETIME	ftLastAccessTime;			// �ļ�������ʱ��
	FILETIME	ftLastWriteTime;			// �ļ�����޸�ʱ��

	FILETIME	ftActionTime;				// �ļ�����ʱ��

} TCACHED_FILE_HEADER,
*PTCACHED_FILE_HEADER;

//
// Ŀ¼���� ͷ��
//

typedef struct tag_TCACHED_USBDIR_HEADER
{
	DWORD		dwSingnature;				// ��ʶ
	DWORD		dwHeaderType;				// ͷ����
	DWORD		dwHeaderSize;				// ͷ��С
	
	WCHAR		wcDriverLetter;				// �����̷�
	FILETIME	ftInTime;					// USB����ʱ��
	FILETIME	ftOutTime;					// USB�γ�ʱ��

} TCACHED_USBDIR_HEADER,
*PTCACHED_USBDIR_HEADER;

#pragma pack()		// ȡ��1�ֽڶ��뷽ʽ

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ! _DZK_19780810_FILETASK_H_
