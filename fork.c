//Write a program that uses all four fork system calls (fork, wait, exec and exit) in one program. Your program asks the user to input the name of a program for the child process to execute.

//First.c:
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>
int main(void)
{
	int pwait, c_stat, a;
	char text[20];
	pid_t p;
	p=fork();  //fork() call to create child process
	if(p < 0)
	exit(0);      //if error then exit
	else if(p == 0) //child process
	{
		// Exec replaces the current running process with a new process.
//First parameter is file name associated with the file being executed
    		a = execl("./hello","hello",NULL); 
		
	}
	else //parent
	{
		printf("\nparent process pid = %u ", getppid());
		wait(&c_stat);        //wait() for child process to terminate
//determines whether the child process ended normally.
		if(WIFEXITED(c_stat))
      			printf(" \nChild has terminated\n");
	}
}

//Hello.c:
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	printf(" We are in Hello.c program");
	printf(" Doing some other processing\n");
	return 0;
}
