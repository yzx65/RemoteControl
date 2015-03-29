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
// 任务方向
//
typedef enum _TaskDirect
{
	FILEUP	= 0,			// 上传   Control --> Daemon --> Target
	FILEDOWN,				// 下载   Target  --> Daemon --> Control

} TaskDirect;

//
// 任务状态
//
typedef enum _TaskStatus
{
	WORKING = 0,			// 工作中..
	PAUSED,					// 暂停
	PAUSEDBYNET,
	CANCELED,				// 取消
	ERRORED,				// 出错
	FINISHED,				// 结束

	UNUSED					// 占位符

} TaskStatus;


typedef enum _TaskType
{
	// FILE_TASK所具有的类型
	//
	TASK_FILEDATA = 0,							// 基本文件数据
	TASK_PLUGINDATA,							// 插件数据自动回传
	TASK_PLUGINUPT,								// 插件升级

	TASK_DIRINFO,								// 仅用于目录信息获取
	TASK_DIRFILE,								// 目录回传的文件
	TASK_SEARCHINFO,							// 仅用于纯搜索
	TASK_SEARCHFILE,							// 搜索回传的文件

	// 高级任务
	//
	TASK_DIR,									// DIR_TASK
	TASK_SEARCH									// SEARCH_TASK

} TaskType;

#endif // __T5_TJ_DZK_TASK_H__