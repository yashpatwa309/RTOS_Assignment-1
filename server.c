

#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char *argv[])
{
int csd,sd;

struct sockaddr_in serverAddress,clientAddress;
socklen_t clientLength;

char msg_receive[1000],msg_send[1000];
pid_t cpid;
bzero(&serverAddress,sizeof(serverAddress));
/*Socket address structure*/
serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
serverAddress.sin_port=htons(5555);
/*TCP socket is created, an Internet socket address structure is filled with
wildcard address & server’s well known port*/
sd=socket(AF_INET,SOCK_STREAM,0);
/*Bind function assigns a local protocol address to the socket*/
bind(sd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
/*Listen function specifies the maximum number of connections that kernel should queue
for this socket*/
listen(sd,5);
printf("%s\n","Server is running");
/*The server to return the next completed connection from the front of the
completed connection Queue calls it*/
csd=accept(sd,(struct sockaddr*)&clientAddress,&clientLength);
/*Fork system call is used to create a new process*/
cpid=fork();

if(cpid==0)
{
while(1)
{
bzero(&msg_receive,sizeof(msg_receive));
/*Receiving the request from client*/
recv(csd,msg_receive,sizeof(msg_receive),0);
printf("\nMessage from client : %s\n",msg_receive);
}
}
else
{
while(1)
{

bzero(&msg_send,sizeof(msg_send));
printf("\nType a message here ...  ");
/*Read the message from client*/
fgets(msg_send,10000,stdin);
/*Sends the message to client*/
send(csd,msg_send,strlen(msg_send)+1,0);
printf("\nMessage sent !\n");
}
}
return 0;
}
