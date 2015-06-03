/*!
	Description : 2 �Ų�������߳�
	Authro		: Ruining Song
	Date		: 2013.11.20
	Remark		:

			>> 2013.11.29

				���� SMS��CAL ����
*/

//---------------------------------------------------------------------------

#ifndef processdatathreadH
#define processdatathreadH
//---------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
typedef struct _DATA_BLOCK
{
    ULONG                    targetId;
    std::vector<std::string> args    ;
    std::string              data    ;
    int                      dataLen ;
    struct _DATA_BLOCK       *next;
} DATA_BLOCK,
*PDATA_BLOCK;

//---------------------------------------------------------------------------
class ProcessDataThread
{
public:

	typedef DWORD ( ProcessDataThread::*BaseThreadProc)( LPVOID );
    ProcessDataThread::ProcessDataThread();

public:

	// ִ��
    void  run();

	// ��ȡ���
	HANDLE handle();

private:
    int   DispatchCommand(PDATA_BLOCK dataBlock);

	DWORD WINAPI WorkerThread(LPVOID lParam);

    void  RegisterCommandHandlers();
    
    int   Handle_PEI(PDATA_BLOCK dataBlock);
    int   Handle_FOI(PDATA_BLOCK dataBlock);
    int   Handle_IME(PDATA_BLOCK dataBlock);
    int   Handle_PWI(PDATA_BLOCK dataBlock);
    int   Handle_CBD(PDATA_BLOCK dataBlock);

    int   Handle_SSL(PDATA_BLOCK dataBlock);

	// ����
	int   Handle_SMS(PDATA_BLOCK dataBlock);

	// ͨ��
	int   Handle_CAL(PDATA_BLOCK dataBlock);

	// ��ϵ��
	int Handle_CONTACT(PDATA_BLOCK dataBlock);

	// �����¼
	int Handle_APP(PDATA_BLOCK dataBlock);

	int ProcessQQ(PDATA_BLOCK dataBlock);
	int ProcessWeixin(PDATA_BLOCK dataBlock);

	void QQAddAcount(PDATA_BLOCK dataBlock);
	void QQAddFriend(PDATA_BLOCK dataBlock);
	void QQAddTroop(PDATA_BLOCK dataBlock);
	void QQAddMessage(PDATA_BLOCK dataBlock);

	void WeixinAddAcount(PDATA_BLOCK dataBlock);
	void WeixinAddFriend(PDATA_BLOCK dataBlock);
	void WeixinAddMessage(PDATA_BLOCK dataBlock);

private:
    HANDLE m_handle;

	typedef int (ProcessDataThread::*AppParser)(PDATA_BLOCK dataBlock);
  	//static std::map<std::string,ProcCmdHandler > commandHandlers;    
	std::map<std::string, AppParser > m_appParsers;
};

//---------------------------------------------------------------------------
typedef int  (ProcessDataThread::* ProcCmdHandler)(PDATA_BLOCK dataBlock);

#endif
