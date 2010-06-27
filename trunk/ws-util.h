/***********************************************************************
 ws-util.h - Declarations for the Winsock utility functions module.
***********************************************************************/

#if !defined(WS_UTIL_H)
#define WS_UTIL_H

// Uncomment one.
//#include <winsock.h>
#include <winsock2.h>

extern const char* WSAGetLastErrorMessage(const char* pcMessagePrefix,
        int nErrorID = 0);
extern bool ShutdownConnection(SOCKET sd);
extern u_long LookupAddress(const char* pcHost);
extern SOCKET EstablishConnection(u_long nRemoteAddr, u_short nPort);

#endif // !defined (WS_UTIL_H)


