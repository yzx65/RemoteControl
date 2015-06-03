
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
    void  Send_PNG();

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
    void  Send_DOW(FileTask *fileTask, int startPos);
    void  Send_ERR(FileTask *fileTask);
    
private:

	// static std::map<std::string,TargetCmdHandler > commandHandlers;
                                                  
    int   DispatchCommand(std::vector<std::string> & args);
    void  RegisterCommandHandlers();

    int   Handle_HEL(std::vector<std::string> & args);
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

public:

    Target      *ownerTarget;
    char        *readBuf;           // For File Read

	CRITICAL_SECTION csTarConn;
	HANDLE ftkHandle;
};

typedef int  (TargetConnection::* TargetCmdHandler)(std::vector<std::string> &);

#endif
