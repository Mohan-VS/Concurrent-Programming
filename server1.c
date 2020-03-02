//server 1 to send reverse of the string to the client program

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/un.h>
#define SOCK_PATH  "tpf_unix_sock.server"
void main()
{
    int server_sock, client_sock, len, temp,i,j,l;
    int bytes_rec = 0;
    char str[256],s2[256];
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;     
    char buf[256];
    int backlog = 10;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);                
    // socket 
    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);  //socket system call
    if (server_sock == -1)
   {
        printf("SOCKET ERROR: %d\n", errno);
        exit(1);
    }
    server_sockaddr.sun_family = AF_UNIX;   
    strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);
    temp = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);  //binding socket
    if (temp == -1)
   {
        printf("BIND ERROR: %d\n", errno);
        close(server_sock);
        exit(1);
    }
    // Listen for any client sockets 
    temp = listen(server_sock, backlog);  //listening for requests
    if (temp == -1)
   { 
        printf("LISTEN ERROR: %d\n", errno);
        close(server_sock);
        exit(1);
    }
    printf("socket listening...\n");
    // Accept an incoming connection
    client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len);
    if (client_sock == -1)
   {
        printf("ACCEPT ERROR: %d\n", errno);
        close(server_sock);
        close(client_sock);
        exit(1);
    }

    len = sizeof(client_sockaddr);
    temp = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);
    if (temp == -1)
   {
        printf("GETPEERNAME ERROR: %d\n", errno);
        close(server_sock);
        close(client_sock);
        exit(1);
    }
    else {
        printf("Client socket filepath: %s\n", client_sockaddr.sun_path);
    }
    
    // Read and print the data incoming on the connected socket
    printf("waiting to read...\n");
    bytes_rec = recv(client_sock, buf, sizeof(buf), 0); 
    if (bytes_rec == -1)
   {
        printf("RECV ERROR: %d\n", errno);
        close(server_sock);
        close(client_sock);
        exit(1);
    }
    else   //logic to reverse a string
   {
	printf("DATA RECEIVED = %s\n", buf);
	l=strlen(buf)-1;
	j=0;
	for(i=l;i>=0;i--)
	{
		s2[j]=buf[i];
		j++;
	}
	s2[j]='\0';
	printf("\n");
    }
    /* Send data back to the connected socket */
    memset(buf, 0, 256);
    strcpy(buf, s2);      
    printf("Sending reversed string...\n");
    temp = send(client_sock, buf, strlen(buf), 0);
    if (temp == -1)
   {
        printf("SEND ERROR: %d",errno);
        close(server_sock);
        close(client_sock);
        exit(1);
    }   
    else {
        printf("Data sent!\n\n");
    }
    close(server_sock);
    close(client_sock);
}
