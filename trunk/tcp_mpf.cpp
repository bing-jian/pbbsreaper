/**************************************************************************
 * psocket.c --- general network subroutie				  *
 *		 by Samson Chen, Nov 28, 1993				  *
 **************************************************************************/

#include "pbbs.h"
#include "ws-util.h"
#include "stdio.h"
#include "global.h"
//#include "tcp.c"

////////////////////////////////////////////////////////////////////////////////
//	local structure
struct	mpf_head_s
	{
		char	prot;
		char	length[8];
	}	mpf_head;

////////////////////////////////////////////////////////////////////////////////
//			Sending via Message Packet Format
//	fd:	socket file descriptor 
//	buffer:	transmit data buffer 
//	buf_len:	buffer length 
//	protocol:	mpf protocol code 
//	return: 0 = ok		-1 = error occurred	(standard) 
//	int CWinpbbsView::send_mpf( SOCKET fd, char* buffer, DWORD buf_len, char protocol )
int send_mpf( SOCKET fd, char* buffer, DWORD buf_len, char protocol )
{
	char	iac_buff = (char)IAC;
	
	mpf_head.prot=protocol;
	sprintf( mpf_head.length, "%ld", buf_len );

	if( send(fd, &iac_buff, 1, 0 ) == SOCKET_ERROR )	//	send IAC
	{
		//	disconnectTCP();
		return FALSE;
	}
	if( send(fd, (char*) &(mpf_head.prot), 1, 0 ) == SOCKET_ERROR )	//	send protocol code
	{
		//	disconnectTCP();
		return FALSE;
	}
	if( send(fd, (char*) mpf_head.length, 8, 0 ) == SOCKET_ERROR )	//	send packet length
	{
		//	disconnectTCP();
		return FALSE;
	}

	if( buf_len>0 )
	{
		if( send(fd, buffer, buf_len, 0) == SOCKET_ERROR )	//	send buffer
		{
			//	disconnectTCP();
			return FALSE;
		}
	}

	return TRUE;
}
//end of send_mpf 

////////////////////////////////////////////////////////////////////////////////
//		Receive fixed length from stream
//	fd:	socket file descriptor 
//	fix_len:	packet length 
//	buffer:	stored buffer 
//	return: standard
//int CWinpbbsView::fix_read( SOCKET fd, DWORD fix_len, char* buffer )
int fix_read( SOCKET fd, DWORD fix_len, char* buffer )
{
	char *pointer=buffer;
	unsigned long pcount=0;
	unsigned long n;

	while( pcount < fix_len )
	{
		// wait for any data
		do	{
			n = 0;
			ioctlsocket( fd, FIONREAD, &n );
		}
		while (n == 0);

		n = recv( fd, pointer, (fix_len-pcount), 0 );
		if( n==0 )
		{
			//	disconnectTCP();	//	abnormal_disconnect(fd);
			return FALSE;
		}

		//if (n > fix_len-pcount)
		//	TRACE1 ("abnormal recv(): Socket error: %d\n", WSAGetLastError ());

		pcount += n;

		if( pcount < MAX_BUF-1024 )
		  pointer = buffer + pcount;
		// Something deleted. Refer to DOS version source file
	}
	// Something deleted. Refer to DOS version source file
	return TRUE;	//	(0);
}
//end of fix_read 

////////////////////////////////////////////////////////////////////////////////
//		Receive via Message Packet Format
//	fd:			socket file descriptor 
//	buffer:		stored buffer 
//	buf_len:	length of stored buffer 
//	protocol:	fetched protocol code 
//	nowait:		block read_mpf or not 
//	return:		-1 = error occurred
//				-2 = garbage code received (in nowait mode)
//				0 = no data-in (in nowait mode)
//				1 = OK
//	Return:		TRUE = OK
//				FALSE = Error
//				TRUE+1 = Garbage code received (in nowait mode)
//				TRUE+2 = no data-in (in nowait mode)
//int CWinpbbsView::read_mpf( SOCKET fd, char* buffer, DWORD* buf_len, char* protocol, int nowait )
int read_mpf( SOCKET fd, char* buffer, DWORD* buf_len, char* protocol, int nowait )
{
	char 	iac_buff;
	fd_set	rset;
	struct timeval		timeout;
	int 	maxfd, n;

	struct mpf_head_s mpf_head = {0, {48, 0}};

	if( nowait )	//nowait will not block function 
	{
		//set mutiplex I/O check bit 
		maxfd=fd + 1;
		FD_ZERO(&rset);
		FD_SET(fd, &rset);
		timeout.tv_sec=0;
		timeout.tv_usec=1;

		if( (n=select(maxfd, &rset, NULL, NULL, &timeout)) == SOCKET_ERROR )
		{
			//	disconnectTCP();
			return FALSE;
		}

		if( FD_ISSET(fd, &rset) )
		{
			if( (n = recv(fd, &iac_buff, 1, 0 ) ) == 0 )
			{
				//	disconnectTCP();
				return FALSE;
			}
			if( iac_buff != IAC )
				return TRUE+1; //	(-2)	garbage code received 
		}
		else
			return TRUE+2;	//	(0)	no data-in

		//continue at fix_read the head 
	}
	else
	{
		do
		{ 
			n=recv(fd, &iac_buff, 1, 0 ); 
			//if (n == SOCKET_ERROR)
			//	TRACE1 ("recv() error, socket error: %d\n", WSAGetLastError ());
			if( n==0 )
			{
				//	disconnectTCP();	//abnormal_disconnect(fd);
				return FALSE;
			}
		} while( iac_buff != IAC );
			//skip until IAC appearred 
	}

	fix_read(fd, 1, (char*) &(mpf_head.prot));
	fix_read(fd, 8, (char*) mpf_head.length);
		//get packet head 

	*protocol = mpf_head.prot;
	sscanf(mpf_head.length, "%ld", buf_len);

	if( *buf_len > 0 )	//get the packet body if exist 
	{
		// if show readmpf status line when reading network 
		//	Many lines deleted by Thomas. Refer to original source file.
		fix_read(fd, *buf_len, buffer);
	}//end if 

	return TRUE;	//OK 
}
//end of read_mpf 

