/*--- standard header for PBBS ---*/

#include <sys/types.h>
//#include <sys/time.h>
//#include <sys/wait.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <dirent.h>

//#include <sys/resource.h>

#ifndef NEXTSTEP
#include <malloc.h>
#endif

/*#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <memory.h>
#include <sys/file.h>
*/
#include <winsock2.h>
#include "protocol.h"
/* #include "../setup.h" */

/*some system does not define SOMAXCONN constant like Linux*/
#ifndef SOMAXCONN
#define	SOMAXCONN 5
#endif

#define	SALT	"SC"	/*internal use (salt for crypt function)*/

/*avoid redefine by other head files (eg. curses.h)*/
#ifndef	TRUE
#define	TRUE	-1
#endif

#ifndef	FALSE
#define	FALSE	0
#endif
/****************************************************/

#define	MAX_BUF	  63488	 /*62K buffer*/
#define	MAX_HEAD  2048
#define MAX_PAGE  12
#define MAX_AREA  229
#define AREA_PAGE 19

#define PBBS_DEFAULT_PORT	23
#define	ACCEPT_VERSION	1	/*client required later than 1.0*/
#define PBBS_SERVER_VER	16	/*server protocol-arch version*/
/*
	if client's version is older than ACCEPT_VERSION.0 (1.0), connection
	will be reject

	if client's version is older than PBBS_SERVER_VER but later than
	ACCEPT_VERSION.0, connection accept but user will be informed a
	warnning message

	the structure of PBBS_SERVER_VER is

	|..4 bits..|..4 bits..|
	   prefix  . postfix

	eg. 16 = 0001 0000
	Version=    1.0
*/

/*
	function prototypes
*/
long	flength();

