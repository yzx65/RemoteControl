//---------------------------------------------------------------------------

#ifndef EventSelectH
#define EventSelectH
//---------------------------------------------------------------------------

#include <winsock2.h>

//
// Add Connection for eventSelect
//
bool  ConnectToServer(const char *ipAddr, USHORT port, bool bCtrConnFlag, DWORD dwTargetId = 0);
bool  InitialEventSelect();

#endif
