/*
Student No.: 0616222
Student Name: 黃立銘
Email: imsohandsome123.cs06@nctu.edu.tw
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not
supposed to be posted to a public server, such as a
public GitHub repository or a public web page.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<iostream>
using namespace std;

int main() {
	while (1) {

		char input[150];
		//char cmd[150];
		char command[150];
		char *arguments[50];
		char *temp[50];
		int count = 0;
		int flag = 0;
		int in = 0, out = 0;
		int fIn, fOut;
		char documents[150];
		//char *env = { (char*) "PATH=/bin", 0 };//enviroment parameter
		printf(">");
		cin.getline(input, 150);
		char *tok = strtok(input, " \n"); // split it if space or \n
		while (tok != NULL) {
			temp[count++] = strdup(tok); // temp is 2d
			tok = strtok(NULL, " \n");
		}
		strcpy( command, temp[0] );//first word in input
		for (int i = 0; i < count; i++) {
			arguments[i] = temp[i];
		}
		arguments[count] = NULL;
		if (strcmp(arguments[count - 1], "&") == 0) {
			flag = 1;
			arguments[count - 1] = NULL;
		}
		pid_t pid; /* fork another process */
		pid = fork();
		if (pid < 0) { /* error occurred */
			fprintf(stderr, "Fork Failed");
			exit(-1);
		}
			else if (pid == 0) { /* child process */
				//strcpy(cmd, "/bin/");
				//strcat(cmd, command);

			if (flag == 0) {
				for (int i = 0; i < count; i++) {
					if (strcmp(arguments[i], "<") == 0) {
						//puts("<");
						in = 1;
						arguments[i] = NULL;
						strcpy(documents, arguments[i + 1]);
						break;
					}
					if (strcmp(arguments[i], ">") == 0) {
						//puts("<");
						out = 1;
						arguments[i] = NULL;
						strcpy(documents, arguments[i + 1]);
						break;
					}
				}
			}
				else {
					for (int i = 0; i < count-1; i++) {
						if (strcmp(arguments[i], "<") == 0) {
							//puts("<");
							in = 1;
							arguments[i] = NULL;
							strcpy(documents, arguments[i + 1]);
							break;
						}
						if (strcmp(arguments[i], ">") == 0) {
							//puts("<");
							out = 1;
							arguments[i] = NULL;
							strcpy(documents, arguments[i + 1]);
							break;
						}
					}
				}

				if (out) {
					FILE* append = fopen(documents, "w");
					fclose(append);
					fOut = open(documents, O_WRONLY | O_APPEND | O_CREAT);
					out = 0;
					dup2(fOut, 1);
					close(fOut);
				}
				if (in) {
					fIn = open(documents, O_RDONLY);
					in = 0;
					//printf("fIn = %d\n", fIn);
					dup2(fIn, 0);
					close(fIn);
				}
				execvp(command, arguments);
			}
				else { /* parent process */
					/* parent will wait for the child to complete */
					if(flag != 0)
						signal(SIGCHLD, SIG_IGN);
						
					else {
						wait(NULL);
					}
					//exit(0);
				}
	}
}

//g++ -g -Wall os_hw1.cpp -o os_hw1