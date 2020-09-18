#ifndef	__MYDASH_H
#define	__MYDASH_H

#include	<sys/types.h>	/* required for some of our prototypes */
#include	<stdio.h>		/* for convenience */
#include	<stdlib.h>		
#include	<sysexits.h>
#include	<string.h>
#include	<unistd.h>	
#include    <pwd.h>
#include    <readline/readline.h>
#include    <readline/history.h>

#define	MAXLINE	4096			/* max line length */

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */
typedef int bool;
#define true 1
#define false 0

/* prototypes for our own functions */

void	err_dump(const char *, ...);	/* {App misc_source} */
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

void checkHistory(void);
void changeDirectory(char *);
int checkCD(char *);
void refreshDash(char *);
const char *git_version(void);

/* parsing constants and prototypes */
#define MAX_LENGTH 1024
#define MAX_TOKENS 3000
char **parseInput(char *s, char *delimiter, int *numTokens);


#endif	/* __MYDASH_H */
