//Write a C program that allows the user to run all file operations: create a new file, open an existing file, read and write a file. The program also lets delete an existing file.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main(void)
{
	int c,x,r,s;
	char f[20],text[100],buf[1000];
	printf(" 1)Create a new file \n 2)Open an existing file\n 3)Read  4)Write  5)Delete an existing file \n Enter your choice: ");
	scanf("%d",&c);
	switch(c)
	{
	case 1:{   //Create a file
		printf(" Enter a new file name:");
		scanf("%s",f);
		creat( f, S_IRUSR | S_IWUSR | S_IXUSR);  //read and write permissions
		printf(" Done!!\n");
		break;
		}
	case 2:{    	//Opening a file
		printf(" Enter filename to open:");
		scanf("%s", f);
		if((x=open( f, O_RDONLY))<0)   //open with read only
		perror("open() error");
		else
		{
			while((r=read(x, buf, sizeof(buf)-1))>0){  //reading data
			buf[r]=0;
			printf("File read: %s\n ", buf);
			}
		}
		break;
		}
	case 3:{     //reading file
		printf(" Enter filename to read:");
		scanf("%s",f);
		if((x=open( f, O_RDONLY))<0){  //open with read only
		perror("open() error");
		exit(1);
		}
		s=read(x, buf, sizeof(buf)-1);  //reading data
		printf(" File read: %s\n",buf);
		break;
		}
	case 4:{	//Writing to a file
		printf(" Enter filename to write:");
		scanf("%s", f);
		printf("\n Enter text: ");
		scanf("%s", text);
		x=open(f , O_RDWR |O_APPEND); //open with read,write,append mode 
		write(x, text, strlen(text)); //writing text
		printf("\nDone!!");
		break;
		}
	case 5:{
		printf(" Enter filename to delete:");
		scanf("%s",f);
		remove(f);   //deleting file
		printf(" Deleted\n");
		break;
		}
	}
}
