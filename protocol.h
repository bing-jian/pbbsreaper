
/* protocol code for PBBS Message Packet Format */

#define	IAC	(char)	255

#ifndef ERROR
#define	ERROR	(char)	0   // already defined in WinGDI.h
#endif

#define	SESSION	(char)	1
#define	REJECT	(char)	2
#define	BYEBYE	(char)	3
#define	PECHO	(char)	4
#define	PROMPT	(char)	5
#define	SCRSIZE	(char)	6
#define	MENU	(char)	10
#define	DISPLAY	(char)	20
#define	ASK	(char)	21
#define	SUSPEND	(char)	22
#define	PASSWD	(char)	23
#define	POST	(char)	30
#define	GETPOST	(char)	31
#define	MAKEPOST (char)	32
#define	STOPPOST (char)	33
#define	INTRREAD (char) 34
#define	INTRSEL  (char) 25
#define	FILEPOST (char) 35
#define	DOWNLOAD (char) 40
#define	UPLOAD   (char)	41
#define	XFER_ACK (char)	42
#define	END_XFER (char) 43
#define	STOPXFER (char) 44
#define	TALK	 (char) 50
#define	STOPTALK (char) 51
#define	ENDTALK  (char) 52

