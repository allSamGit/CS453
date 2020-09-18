/**
 *This program needs the file error.c and mydash.h to compile.
 *@author Saman Rastgar
 *
 */
#include <sys/types.h>
#include <sys/wait.h>
#include "mydash.h"

#include <unistd.h>	
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	char *prompt;
	char *cmd;

	//Variable for the dash prompt
	char *envPromptVariable = "DASH_PROMPT";
	char *defaultPromptName = "mydash>";

	char *line = NULL;
	char *lineCopy = NULL;
	int cmdDetected = 0;

	line = (char *) malloc(MAXLINE * sizeof(char));
	prompt = (char *) malloc(MAXLINE * sizeof(char));
	cmd = (char *) malloc(MAXLINE * sizeof(char));

	//Print mydash version 	
	if(argc > 1){
		if(strcmp(argv[1], "-v") == 0){
			const char *version = git_version();
			printf("argv[1] = %s\n", argv[1]);
			printf("mydash: Version 1: Revision %s (author: Saman Rastgar  Rastgarsaman@u.boisestate.edu)\n", version);
		}
		//if anything other than -v is typed print out an error
		else {
			fprintf(stderr, "Error, not valid command for version %s\n", argv[1]);
		}
		exit(0);
	}
	//Setting up the mydash prompt on the shell
	prompt = getenv(envPromptVariable);
	if (!prompt)
		prompt = defaultPromptName;
	//	using_history();
	using_history();//Create Readline history list

	while ((line = readline(prompt))) {
		//If the input is nothing then do not do anything
		if(line[0] == '\0'){
		}
		//If the input is nothing then do not do anything
		else if (line[0] == ' '){
		}
		else {
			cmdDetected = 0;
			lineCopy = (char *) malloc(sizeof(char) * strlen(line) + 1);
			strcpy(lineCopy, line);
			add_history(line);

			//Implementing cd command
			strncpy(cmd, line, 2);
			cmd[2] = '\0';
			if(cmd != NULL && cmd[0] != '\0' && strcmp(cmd, "cd") == 0){
				changeDirectory(line);
				cmdDetected = 1;
			} 

			//Implementing exit command
			strncpy(cmd, line, 4);
			cmd[4] = '\0';
			if(cmd != NULL && cmd[0] != '\0' && strcmp(cmd, "exit") == 0){

				free(line);
				//free(prompt);
				free(cmd);
				free(lineCopy);
				cmdDetected = 1;
				exit(0);
			} 

			//Implementing history command
			strncpy(cmd, line, 7);
			cmd[7] = '\0';
			if(cmd != NULL && cmd[0] != '\0' && strcmp(cmd, "history") == 0){

				checkHistory();
				cmdDetected = 1;
			} 

			if(!cmdDetected){
				char **cmdArgs;
				char *argument = '\0';
				int i = 0;
				cmdArgs = (char **)malloc(sizeof(char *)* MAXLINE);
				argument = strtok(line, " ");

				while (argument != NULL){
					if(strstr(argument, "&")!=NULL){
						break;
					}
					cmdArgs[i] = argument;
					i++;
					argument = strtok(NULL, " ");
				}
				cmdArgs[i++] = (char *) 0;

				if ( (pid = fork()) < 0)
					err_sys("fork error");

				//child
				else if (pid == 0) {

					execvp(cmdArgs[0], cmdArgs);
					err_ret("couldn't execute: %s", buf);
					exit(EXIT_FAILURE);
				}  

				//parent 
				if ( (pid = waitpid(pid, &status, 0)) < 0){
					err_sys("waitpid error");
				}
				free(cmdArgs);
			}

		}		
	}
	exit(EXIT_SUCCESS);
}
//Refresh the dash
void refreshDash(char * nextLocation){
	strcpy(nextLocation, getenv("DASH_PROMPT"));
	if(nextLocation != NULL && nextLocation[0] != '\0'){
		strcat(nextLocation, ">");
	}
}
//Change directory prompt and method
void changeDirectory(char *cmd) {
	uid_t uid = getuid();
	struct passwd wd;
	struct passwd *pwd;
	char buff[1024];
	char *tok = strtok(cmd, " ");
	tok = strtok(NULL, " "); 
	if(tok == NULL) {
		//no change to directory requested
		if(getpwuid_r(uid, &wd, buff, sizeof(buff), &pwd)){

			perror("getpwuid_r");
		}
		else {
			if(chdir(wd.pw_dir) != 0){
				// Failure
				perror("chdir");
			} 			
		}
	} else{
		if(chdir(tok) != 0){
			// Failure
			perror("chdir");
		} else{
			printf("changed directory: %s\n", tok);
		}
	}
}		
//Method to check history
void checkHistory(){
	int i = 0;
	register HIST_ENTRY **hist;
	hist = history_list();
	if (hist)
		for (i = 0; hist[i]; i++)
			printf ("%d: %s\n", i + history_base, hist[i]->line);
}

//getCD
int getCD(char *location) {
	char cd[MAX_LENGTH];
	char *tok;
	if (getcwd(cd, sizeof(cd) != 0)){
		tok = strtok(cd, "/");
		while(tok != NULL){
			strcpy(location, tok);
			tok = strtok(NULL, "/");
		}
		return 0;
	}
	else {
		perror("getCD");
		return 56;
	}
}
