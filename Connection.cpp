//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "adkprecomp.h"
#include "maindlg.h"
#include "connection.h"
#include "Utility.h"

#pragma comment(lib,"ws2_32.lib")

//---------------------------------------------------------------------------
 Connection::Connection(SOCKET s):sock(s)
{
    InitializeCriticalSectionAndSpinCount(&this->critSection, 1);
    lpbyWriteBuffer = (PBYTE)AdkMalloc(8196);    
}
//---------------------------------------------------------------------------
 Connection::~Connection()
{
    if (lpbyWriteBuffer)
    {
        AdkFree(lpbyWriteBuffer);
    }
}
//---------------------------------------------------------------------------
void  Connection::CloseConnection()
{
    if (this->sock)
    {
        closesocket(this->sock);
        this->sock = NULL;
    }
}
//---------------------------------------------------------------------------
void  Connection::DataArrivedOnSocket()
{
    char tempReadBuffer[8192];
    
    ZeroMemory(tempReadBuffer, 8192);
    
    int amountRead = recv(this->sock, tempReadBuffer, 8190, 0);
    if (SOCKET_ERROR != amountRead)
	{
		// @Note : there may have some binary data in string
		//
		FlowStatistics(amountRead);

        CryptData((BYTE*)tempReadBuffer,amountRead);
        readBuffer += string(tempReadBuffer, amountRead);

        HandleIncomingData();
	}
}
//---------------------------------------------------------------------------

bool  Connection::IsWholeLineAvailable()
{
	return (readBuffer.find("\r\n") != std::string::npos);
}


//---------------------------------------------------------------------------


bool  Connection::IsWholeDataAvailable(unsigned int dataLen)

{
	if (dataLen > this->readBuffer.size())
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------

std::vector<std::string>  Connection::GetLine()
{
	assert((this->IsWholeLineAvailable()));

	// @@Note:
	//
	// store readline temply, in order to restore readbuffer when
	// the data has not been received completely specialyy in msg
	// and not command
	//
	this->tmpReadLine = this->readBuffer.substr(0,this->readBuffer.find("\r\n"));
    
	// Remove line from readbuffer.
	//
	this->readBuffer = this->readBuffer.substr(this->readBuffer.find("\r\n") + 2);

	return SplitString(this->tmpReadLine, " ");
}
//---------------------------------------------------------------------------

std::string	 Connection::GetData(unsigned int dataLen)
{
	std::string data = this->readBuffer.substr(0,dataLen);
	this->readBuffer = this->readBuffer.substr(dataLen);
	int len = readBuffer.size();
	return data;
}
//---------------------------------------------------------------------------
void  Connection::RecoverCommand()
{
	// Restore this->readBuffer for next processing
	//
	this->readBuffer = this->tmpReadLine + "\r\n" + this->readBuffer;
}
//---------------------------------------------------------------------------
int  Connection::Write(const std::ostringstream & ss)
{
    return Write(ss.str());
}
//---------------------------------------------------------------------------
int  Connection::Write(const std::string dataStr)
{
    int nRet;
    EnterCriticalSection(&this->critSection);
    CopyMemory(lpbyWriteBuffer, dataStr.c_str(), dataStr.length());
	nRet = WriteBinaryData((char*)lpbyWriteBuffer, dataStr.length());
 	LeaveCriticalSection(&this->critSection);

    return nRet;
}
//---------------------------------------------------------------------------
int  Connection::WriteDataCmd(const std::string cmdStr, const char *data, const unsigned int dataLen)
{
    int nRet;

	EnterCriticalSection(&this->critSection);
    int nCmdLen = cmdStr.length();
    CopyMemory(lpbyWriteBuffer, cmdStr.c_str(), nCmdLen);
    if (dataLen > 0)
    {
        CopyMemory(lpbyWriteBuffer + nCmdLen, data, dataLen);
    }
    nRet = WriteBinaryData((char*)lpbyWriteBuffer, nCmdLen + dataLen);
 	LeaveCriticalSection(&this->critSection);
    
    return nRet;
}
//---------------------------------------------------------------------------
int	 Connection::WriteBinaryData(char *data, unsigned int len)
{
	int ret = 0;
    CHAR buf[256];

    xASSERT((len < 8192));
    CryptData((BYTE*)data, len);
    size_t written = 0;

    while (written < len)
	{
		size_t newWritten = send(this->sock, data + written, (int) (len - written), 0);

        if (newWritten == SOCKET_ERROR)
        {
			int errid = WSAGetLastError();
			if (errid == WSAEWOULDBLOCK)
			{
				continue;
			}
			else
			{
                break;
            }
		}
        
		written += newWritten;
	}

	return written;
}