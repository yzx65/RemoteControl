
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
    void  Send_FTK(ULONG targetId, ULONG taskId);     // 查询 FileTask (taskID为0，说明查询全部0
    void  Send_DTK(ULONG targetId, ULONG taskId, BOOL bDetail);                   // 查询 DirTask
    void  Send_STK(ULONG targetId, ULONG taskId);                   // 查询 SearchTask

    void  Send_AFT(ULONG        targetID,
                             TaskDirect   taskDirect,
                             const char*        ctrPathBase64,
                             const char*        tarPathBase64,
                             ULONG        totalLen);                // 增加 FileTask
                             
    void  Send_ADT(ULONG      targetID,
                             TaskDirect taskDirect,
                             const char*      tarDirPathBase64,
                             ULONG      level,
                             ULONG      autoDown);                  // 增加 DirTask

    void  Send_AST(ULONG          targetID,
                             TaskDirect     taskDirect,
                             PCHAR          tarDirPathBase64,
                             ULONG          level,
                             PSearchFilter  lpSearchFilter,
                             ULONG          autoDown);                  // 增加SearchTask

    void  Send_CFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // 清除 Task
    void  Send_PFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // 暂停 Task
    void  Send_RFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // 继续 Task
    void  Send_DFT(DWORD dwTargetID, DWORD dwTaskID, DWORD dwTaskType);   // 通知 Daemon直接删除 Task
    
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

    // FileTask相关指令解释函数
    //
    int   Handle_SCH(std::vector<std::string> & args);    // 重新调度
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
        
    // 文件上传下载
    //
	int   Handle_DOW(std::vector<std::string> & args);
	int   Handle_UPL(std::vector<std::string> & args);
    int   Handle_FDT(std::vector<std::string> & args);    // 文件时间信息

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
