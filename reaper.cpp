/*!
    \file    Reaper.Cpp
    \brief   Get articles from a specific group.
    \author  Bing Jian (jianbing@ustc.edu)
    \date    01/20/2002

    Implements a fairly basic client program that downloads articles from
    a specific discussing group of USTC BBS.

    Input:
        1. the group name;  eg. Programming
        2. the index range of the messages to be downloaded. eg. 200-300

*/


#include "ws-util.h"
#include "pbbs.h"
#include "tcp_mpf.cpp"
#include <winsock2.h>
#include <iostream>
#include <string.h>

using namespace std;

/* Attention!!
   Changes to version and platform may cause some problems
*/
#define VERSION   0x23
#define PLATFORM  3

int DoWinsock(const char* pcHost, int nPort);

/*!
   \fn int DoWinsock(const char* pcHost, int nPort)
   \brief main working function.
   \param pcHost: IP address or domain name.
   \param nPort:  port number.
   The module's driver function -- we just call other functions and
   interpret their results.
*/
int DoWinsock(const char* pcHost, int nPort)
{

    /* variants used to send and recv messages */
    int tcpstat, quit=0;
    unsigned long len;
    char prot;
    char buffer[MAX_BUF], pwbuffer[20];

    /* to store the basic information of groups */
    char areaname[80];              /* Name of the selected area; */
    char grplist[MAX_AREA+1][80];   /* The list of groups eg. grplist[40] = "bbsdev" */
    char area_id[5];                /* The ID of group */
    char strArea[80], strTotal[80], strMsgno[80];
    // char strPath[80],strFrom[80];
    // char strSubject[80],strMsgID[80],strDate[80],strOrg[80];

    /* to limit the scope of articles you want to download */
    int startno, endno, msgno, minno, maxno, ii = 0;

    /* some variants used to control the process */
    int firsttime = TRUE;
    int emptyboard = 0;
    int notfound = TRUE;

    /* file IO */
    FILE* fp;
    char fname[30];

    /* some temporary variants */
    char *p;
    int slen;
    int pd = 0;
    int i,j,count = 0;

    /* main entry */

    /* Print Author and Version Information */
    cout << endl << endl << " BBSReaper V1.0 "<< endl;
    cout << "   written by Bing_Jian, Jan 20, 2002." << endl << endl;
    fflush(stdout);

    /* Find the server's address */
    cout << "Looking up address ... " << flush;
    u_long nRemoteAddress = LookupAddress(pcHost);
    if (nRemoteAddress == INADDR_NONE)
    {
        cerr << endl << WSAGetLastErrorMessage("lookup address") <<
            endl;
        return 3;
    }
    in_addr Address;
    memcpy(&Address, &nRemoteAddress, sizeof(u_long));
    cout << inet_ntoa(Address) << ":" << nPort << endl;

    /* Connect to the BBS server */
    cout << "Connecting to the remote host " << inet_ntoa(Address) << " ... " << flush;
    SOCKET sd = EstablishConnection(nRemoteAddress, htons(nPort));
    if (sd == INVALID_SOCKET)
    {
        cerr << endl << WSAGetLastErrorMessage("connect to the server") << endl;
        return 3;
    }
    cout << "Connected!" << endl << endl << flush;

    recv(sd,buffer, 8000, 0);

    //read_mpf(sd, buffer, &len, &prot, 0);
    //buffer[len] = 0;
    cout<<buffer<<endl;
    /* Implement the handshake */
    /*  strcpy(buffer, "Samson");
    if (send_mpf(sd, buffer, strlen(buffer), SESSION)==-1)
    {
        ShutdownConnection(sd);
    }
    read_mpf(sd, buffer, &len, &prot, 0);
    buffer[len] = 0;
    if (strcmp("Aquarius", buffer))
    {
        cerr << "Handshaking failed" << endl << flush;
        ShutdownConnection(sd);
    }
    buffer[0] = VERSION;
    buffer[1] =(PLATFORM << 4) + 0;
    strcpy(&buffer[2], "POWERBBS");
    send_mpf(sd, buffer, 10, SESSION);
    */
    /*
        message loop
        send data; listen; parse received prot and buffer;
    */
    do
    {

    }
    while (!quit);
}

