/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define SERVER "127.0.0.1"
#define PORT 8888   //The port on which to send data

#define  SIZE 1000;
typedef struct {
    unsigned int length;
    unsigned char data[1000];
}Message;
typedef enum{
    OK,
    BAD,
    WRONGLENGTH
} Status;
typedef struct sockaddr_in SocketAddress;

void die(char *s)
{
    perror(s);
    exit(1);
}
//excercise 2
typedef struct{
    enum{Request, Reply} MessageType;
    unsigned int RPCId, ProcedureId;
    int arg1, arg2;
}RPCMessage;

Status UDPSend(int s, Message *m, SocketAddress destination);
Status UPDReceive(int s, Message *m, SocketAddress *origin);

Status DoOperation(Message *message, Message *reply,int s, SocketAddress serverSA);
int main(){
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[1024];
    char replBuf[1024];
    char message[1024];
    char server[50], client[1074]; int port;
    printf("--- Enter CLIENT name ---");
    scanf("%s", &client);
    printf("--- Input SERVER address ---\n");
    scanf("%s", &server);
    printf("--- Communication PORT --- \n");
    scanf("%d", &port);
    getchar();

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    //memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    if (inet_aton(server , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1)
    {
        printf("%s says : \n", client);
        scanf("%[^\n]%*c", &buf);
        strcat(client, " : ");
        strcat(client, buf);
        if(buf[0] == 'q'|| buf == "stop"){
            Status sn = DoOperation(client, replBuf,s, si_other);
            if(sn == BAD){printf("\nBad client request: Status[BAD]\n");}
            else if(sn == WRONGLENGTH){printf("\nWrong length from client request: Status[WRONGLENGTH]\n");}
            else{printf("\nSuccessful client request: Status[OK]\n");}
            break;
        }
        if(strlen(buf) > 1000){
            printf("\n\n -- -- too long -- -- \n\n");
        }else{
            Status sn = DoOperation(client, replBuf,s, si_other);
            if(sn == BAD){printf("\nBad client request: Status[BAD]\n");}
            else if(sn == WRONGLENGTH){printf("\nWrong length from client request: Status[WRONGLENGTH]\n");}
            else{printf("\nSuccessful client request: Status[OK]\n");}
        }
        //puts(replBuf);
        memset(message, 0, sizeof(message));
        memset(buf, 0, sizeof(buf));
    }

    close(s);
    return 0;
}
Status DoOperation(Message *message, Message *reply,int s, SocketAddress serverSA){

    alarm(1000);
    int sendId = sendto(s, message, strlen(message), 0, (struct sockaddr *)&serverSA, sizeof(serverSA));
    Status sn = OK;
    if(sendId < 0){ sn = BAD; die("sendto()"); }

    memset(message,'\0', 1000);
    int slen = sizeof(serverSA);
    if (recvfrom(s, reply, 1000, 0, (struct sockaddr *) &serverSA, &slen) < 0){
        if(errno == EINTR){ printf("Server took too long to reply"); }
        else{
            die("recvfrom()");
        }
    }
    puts(reply);
    memset(reply,'\0', strlen(reply));
    return  sn;
}