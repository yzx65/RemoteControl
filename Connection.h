//---------------------------------------------------------------------------

#ifndef connectionH
#define connectionH
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

//---------------------------------------------------------------------------

class Connection
{
public:
     Connection(SOCKET s);
     ~Connection();

    void  DataArrivedOnSocket();    
    void  CloseConnection();

	virtual void  HandleIncomingData() = 0;
    virtual void  ConnectionCompleted()= 0;
    virtual void  ConnectionClosed()   = 0;

	virtual void  FlowStatistics(unsigned int bytes) = 0;

protected:

    bool  IsWholeLineAvailable();
    bool  IsWholeDataAvailable(unsigned int dataLen);

    std::vector<std::string>  GetLine();
	std::string	 GetData(unsigned int dataLen);
    
    void  RecoverCommand();

    int   Write(const std::ostringstream & ss);
    int   Write(const std::string dataStr);
    int   WriteDataCmd(const std::string cmdStr, const char *data, const unsigned int dataLen);


private:
	int	  WriteBinaryData(char *data, unsigned int len);
    
protected:

    SOCKET          sock;
    
	std::string	    tmpReadLine;
	std::string		readBuffer;
    PBYTE           lpbyWriteBuffer;

private:

	CRITICAL_SECTION	critSection;
};
//---------------------------------------------------------------------------
#endif
