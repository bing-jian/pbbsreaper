/****************************************************************************
 * global.h ---  declare some external variables which are used at most     *
 *	 	 modules						    *
 *		 by Samson Chen, Dec 2, 1993				    *
 ****************************************************************************/

/*
	for debugging
*/
extern	char debug_mode;	/*TRUE for debug mode*/


/*
	basic tested client specifications
*/
extern	char client_site[30];		/*client's readable address*/
extern	unsigned char platform;		/*client's platform*/
extern	int on_line_users;		/*number of on-line users*/


/*
	system control
*/
extern	unsigned int	idling;		/*for alarm*/


/*
	login user data
*/
extern	int putmp_rec;		/*record # of putmp of current user*/
extern	unsigned int user_uid;	/*user database id number*/
extern	char user_name[20];	/*user id name*/
extern	char user_email[40];	/*user email address*/
extern	unsigned int user_level;/*user security level*/
extern	int total_regs;		/*total registered people*/
extern	int total_login;	/*total login people*/
extern	char system_operator;	/*sysop level falg*/

/*
	bulletin
*/
extern	char bstack[256];

/*
	mail control
*/
extern	char current_group[30];		/*current posting group*/
extern	char group_areaname[30];	/*current group name description*/
extern	unsigned int mini_post_level;	/*minimum posting level of current_group*/
extern	char group_moderator;	/*moderator flag*/

/*
	file_download control
*/
extern	char file_area[30];			/*current file area*/
extern	int toggles;				/*total toggles*/
/* extern	char tagged[_ALLOW_TAG][120]; */	/*tagged files*/

