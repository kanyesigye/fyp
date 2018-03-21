/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
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

Status UDPSend(int s, Message *m, SocketAddress destination);
Status UPDReceive(int s, Message *m, SocketAddress *origin);
Status DoOperation(Message *message, Message *reply,int s, SocketAddress serverSA);
int main(){
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char replBuf[1024];
    char message[BUFLEN];

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    //memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1)
    {
        printf("Enter message : ");
        //gets(message);
        scanf("%[^\n]%*c", &buf);
        if(buf[0] == 'q'){
            Status sn = DoOperation(buf, replBuf,s, si_other);
            break;
        }
        //send the message
        //write(1,"\n%s\n", buf);
        Status sn = DoOperation(buf, replBuf,s, si_other);
        //printf("%s", sn);
        //puts(replBuf);
        memset(message, 0, sizeof(message));
        memset(buf, 0, sizeof(buf));
    }

    close(s);

    printf("You have terminated the discussion!!");
    return 0;
}
Status DoOperation(Message *message, Message *reply,int s, SocketAddress serverSA){
    int sendId = sendto(s, message, strlen(message), 0, (struct sockaddr *)&serverSA, sizeof(serverSA));
    Status sn = OK;
    if(sendId == -1){
        sn = BAD;
        die("sendto()");
    }

    memset(message,'\0', BUFLEN);
    int slen = sizeof(serverSA);
    //try to receive some data, this is a blocking call
    if (recvfrom(s, reply, BUFLEN, 0, (struct sockaddr *) &serverSA, &slen) == -1)
    {
        die("recvfrom()");
    }
    puts(reply);
    memset(reply,'\0', strlen(reply));
    return  sn;
}