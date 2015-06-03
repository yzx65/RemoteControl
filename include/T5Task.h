/**************************************************************
 * Module:
 *        T5Task.h
 *
 * Author:
 *        DING ZhaoKun (dzkad@hotmail.com)
 *
 * Time:
 *        2007-3-8, Nanjing
 *
 * Notes
 *
 *
 */

#ifndef __T5_TJ_DZK_TASK_H__
#define __T5_TJ_DZK_TASK_H__

//
// ������
//
typedef enum _TaskDirect
{
	FILEUP	= 0,			// �ϴ�   Control --> Daemon --> Target
	FILEDOWN,				// ����   Target  --> Daemon --> Control

} TaskDirect;

//
// ����״̬
//
typedef enum _TaskStatus
{
	WORKING = 0,			// ������..
	PAUSED,					// ��ͣ
	PAUSEDBYNET,
	CANCELED,				// ȡ��
	ERRORED,				// ����
	FINISHED,				// ����

	UNUSED					// ռλ��

} TaskStatus;


typedef enum _TaskType
{
	// FILE_TASK�����е�����
	//
	TASK_FILEDATA = 0,							// �����ļ�����
	TASK_PLUGINDATA,							// ��������Զ��ش�
	TASK_PLUGINUPT,								// �������

	TASK_DIRINFO,								// ������Ŀ¼��Ϣ��ȡ
	TASK_DIRFILE,								// Ŀ¼�ش����ļ�
	TASK_SEARCHINFO,							// �����ڴ�����
	TASK_SEARCHFILE,							// �����ش����ļ�

	// �߼�����
	//
	TASK_DIR,									// DIR_TASK
	TASK_SEARCH									// SEARCH_TASK

} TaskType;

#endif // __T5_TJ_DZK_TASK_H__