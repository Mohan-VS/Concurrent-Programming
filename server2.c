//server2 to send even places of the string to client program

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#define PORT     8080 
#define MAXLINE 256 
void main()
{  
    char s2[256], str[100];  
    int sockfd,j,len,i,n;
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }  
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    servaddr.sin_family    = AF_INET;  //IPV4 family 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Binding socket with server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    printf("socket listening...\n");
    n = recvfrom(sockfd, buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr, &len);
    j=0;
    int a=strlen(buffer);
    for(i=0;i<=a;i=i+2)
    {
	    s2[j]=buffer[i];
	    j++;
    }
       s2[j]='\0'; 
      printf("to Client : %s\n", s2); 
      sendto(sockfd, s2, strlen(s2), 0, (const struct sockaddr *) &cliaddr, len); 
      printf("sent\n");
}
