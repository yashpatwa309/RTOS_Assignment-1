
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "netdb.h"
#include "arpa/inet.h"

int main()
{
int sd;

struct sockaddr_in serverAddress;
char send_msg[1000],receive_msg[1000];

pid_t cpid;

bzero(&serverAddress,sizeof(serverAddress));

serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=inet_addr("3.21.166.33");
serverAddress.sin_port=htons(5555);

/*Creating a socket, assigning IP address and port number for that socket*/
sd=socket(AF_INET,SOCK_STREAM,0);

/*Connect establishes connection with the server using server IP address*/
connect(sd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

/*Fork is used to create a new process*/
cpid=fork();
if(cpid==0)
{
while(1)
{
bzero(&send_msg,sizeof(send_msg));
printf("\nEnter the message ");
/*This function is used to read from server*/
fgets(send_msg,10000,stdin);
/*Send the message to server*/
send(sd,send_msg,strlen(send_msg)+1,0);
printf("\nsent !\n");
}
}
else
{
while(1)
{
bzero(&receive_msg,sizeof(receive_msg));
/*Receive the message from server*/
recv(sd,receive_msg,sizeof(receive_msg),0);
printf("\nMessage from server: %s\n",receive_msg);
}
}
return 0;
}
