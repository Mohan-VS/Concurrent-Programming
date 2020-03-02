//Write a C program running in Unix that execute in two different terminals communicate using Pipes and Fifos.
//The first program ask the user to select Pipes or Fifos; and type a text(or one word).
//The text will be transmitted via Pipe or Fifo and the output will be displayed by the second prorgram.

First.c :
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(void)
{
	int pd[2],pip,i,w,n,r,x;
	char text[100],arr[100],buf;
	char *myFIFO="./myFIFO";
	printf(" Enter your choice: 1)Pipes 2)Fifos : ");
	scanf("%d",&n);
	switch(n)
	{
	case 1: //pipes
	{	
		printf(" \nEnter text to trasmit: ");
		scanf("%s",text);
		pip= pipe(pd);
		if(pip<0){
			printf(" Pipe error");
			exit(1);
		}	
		pid_t id=fork();  //fork is called
		if(id == 0) //child process
		{
			close(pd[1]);  	//Closing writing end of pipe
			while(read(pd[0], &buf, 1)) //write output to the screen
			write(STDOUT_FILENO, &buf, sizeof(buf));
			write(STDOUT_FILENO, "\n", 1);
			close(pd[0]); 	//closing read end of pipe
		}
		else   //parent process
		{
			close(pd[0]);	//closing reading end of pipe
			//then writing input string and close writing end of pipe
			write(pd[1], text, strlen(text)); 
			close(pd[1]);
			wait(NULL);	//now wait until child is finished
			exit(0);
		}
	
		break;
	}
	case 2: //Fifos
	{
		printf(" \nEnter text to trasmit: ");
		scanf("%s", text);
		mkfifo(myFIFO, 0666);  //function call to create a FIFO
		w=open(myFIFO, O_WRONLY | O_CREAT);  //Open FIFO for write 
		if(w<0) return -1;
		write(w, text, strlen(text));   //write input on Fifo and close it.
		close(w);   //closing file and unlinking FIFO
		unlink(myFIFO);
		break;
	}
	default: printf(" Please enter valid choice (1 or 2)\n");
		break;
	}
}



//Second.c:
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define max 1024
int main(void)
{
	int fd;
	char *file = "./myFIFO";
	char buf[100];
	mkfifo(file,0666);
	fd=open(file, O_RDONLY);  //Open in read only and read input
	if(fd<0)
	   return -1;
	read(fd, buf, 100);
	printf(" User 1: %s ", buf);
	close(fd);
}
