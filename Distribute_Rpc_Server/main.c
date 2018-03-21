/*
    Simple udp server
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

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

Status SendReply(Message *replyMessage, int s, SocketAddress clientSA);
Status GetRequest(Message *callMessage, int s, SocketAddress *clientSA);
int main(void)
{
    SocketAddress si_me, si_other, *serverAD, *clientAd;

    int s;
    char buf[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        //try to receive some data, this is a blocking call

        GetRequest(buf, s, clientAd);

        if(buf[0] == 'q'){
            //now reply the client with the same data
            char msg[] = "you terminated the conncection";
            //SendReply(msg, s, si_other);
            printf("process terminated by client");
            break;
        }
        //now reply the client with the same data
        //SendReply(buf, s, si_other);
    }

    close(s);
    return 0;
}
Status SendReply(Message *replyMessage, int s, SocketAddress clientSA){
    int sendId = sendto(s, replyMessage, strlen(replyMessage), 0, (struct sockaddr *)&clientSA, sizeof(clientSA));
    Status sn = OK;
    if(sendId == -1){
        sn = BAD;
        die("sendto()");
    }
}
Status GetRequest(Message *callMessage, int s, SocketAddress *clientSA){
    int slen = sizeof(clientSA);
    if (recvfrom(s, callMessage, BUFLEN, 0, (struct sockaddr *) &clientSA, &slen) == -1)
    {
        die("recvfrom()");
    }
    SocketAddress si_me, si_other;
    //print details of the client/peer and the data received
    printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    printf("Data: %s\n" , callMessage);

    puts(callMessage);
    memset(callMessage,'\0', strlen(callMessage));
    return OK;
}