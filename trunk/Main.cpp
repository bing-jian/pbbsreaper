/*!
    \file   Main.Cpp
    \brief  A general framework of winsock program
    \author Bing Jian (jianbing@ustc.edu)
    \date   01/20/2002
*/

#include "pbbs.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

//// Prototypes ////////////////////////////////////////////////////////

extern int DoWinsock(const char* pcHost, int nPort);

/*========================Main program ============================*/
int main(int argc, char *argv[])
{
    char ipaddr[50]; // 202.38.64.3
    int  bbsport;   // 6203

    // Start Winsock up
    WSAData wsaData;
    int nCode;
    if ((nCode = WSAStartup(MAKEWORD(1, 1), &wsaData)) != 0) {
        cerr << "WSAStartup() returned error code " << nCode << "." << endl;
        return 255;
    }

    //Call the main routine.
    strcpy(ipaddr, "bbs.ustc.edu.cn");
    bbsport = PBBS_DEFAULT_PORT;
    int retval = DoWinsock(ipaddr, bbsport);

    // Shut Winsock back down and take off.
    WSACleanup();
    return retval;
}


