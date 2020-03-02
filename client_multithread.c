//This is a client and 2 server model.. Check server1.c and server2.c  programs for servers

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include "pthread.h"
#include <sys/un.h>
#include <errno.h>
#define SERVER_PATH "tpf_unix_sock.server"
#define CLIENT_PATH "tpf_unix_sock.client"
#define PORT 8080 
#define MAXLINE 256 
char buffer[MAXLINE];
void *serv1(void *);
void *serv2(void *);
void main()
{
	pthread_t tid1, tid2;
	printf(" Enter a string: ");  //user input
           scanf("%[^\n]%*c", buffer);
	pthread_create(&tid1,NULL,&serv1,NULL);   //multithreading, creating two threads
	pthread_create(&tid2,NULL,&serv2,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	exit(0);
}

void *serv1(void *ptr)   //connection-oriented
{
      int client_sock, temp, len;
      struct sockaddr_un server_sockaddr; 
      struct sockaddr_un client_sockaddr; 
      char buf[256],str[100];
      memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
      memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
     
      client_sock = socket(AF_UNIX, SOCK_STREAM, 0);  //create a socket
      if (client_sock == -1)
      {
          printf("SOCKET ERROR = %d\n", errno);
          exit(1);
      }
      client_sockaddr.sun_family = AF_UNIX;   
      strcpy(client_sockaddr.sun_path, CLIENT_PATH); 
      len = sizeof(client_sockaddr);  
      unlink(CLIENT_PATH);
     //binding socket with local address
      temp = bind(client_sock, (struct sockaddr *) &client_sockaddr, len);
      if (temp == -1)
      {
           printf("BIND error: %d\n", errno);
           close(client_sock);
           exit(1);
      }
      //setup socket address
      server_sockaddr.sun_family = AF_UNIX;
      strcpy(server_sockaddr.sun_path, SERVER_PATH);
      temp = connect(client_sock, (struct sockaddr *) &server_sockaddr, len);
      if(temp == -1)
      {
            printf("Connection failure= %d\n", errno);
            close(client_sock);
            exit(1);
      }
    strcpy(buf, buffer);
    //sending data to server
    temp = send(client_sock, buf, strlen(buf), 0);
    if (temp == -1)
    {
        printf("SEND ERROR = %d\n", errno);
        close(client_sock);
        exit(1);
    }   
    else
        printf("Data sent to server 1\n");

    //receiving data from server
    memset(buf, 0, sizeof(buf));
    temp = recv(client_sock, buf, sizeof(buf),0);
    if (temp == -1)
    {
        printf("RECV ERROR = %d\n",errno);
        close(client_sock);
        exit(1);
    }   
    else
          printf("Server 1 = %s\n", buf);
    close(client_sock);
}

void *serv2(void *ptr)  //connectionless server
{
    int sockfd,n,len; 
    char buf[MAXLINE];  
    struct sockaddr_in servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    strcpy(buf, buffer);  //temporary variable
    sendto(sockfd, buf, strlen(buf),  0, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    printf("Data sent to server 2.\n"); 
    bzero(buf,256);
    n = recvfrom(sockfd,buf, MAXLINE, 0, NULL,NULL); 
    buf[n] = '\0';
    printf("Server 2 : %s\n", buf);
     close(sockfd); 
}
