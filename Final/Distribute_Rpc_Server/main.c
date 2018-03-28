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

#define PORT 8888   //The port on which to listen for incoming data
#define  SIZE 1000;
typedef struct {
    unsigned int length;
    unsigned char data[1000];
}Message;
typedef enum{
    OK,
    BAD,
    WRONGLENGTH,
    DivZero
} Status;
typedef struct sockaddr_in SocketAddress;
//excercise 2
typedef struct{
    enum{Request, Reply} MessageType;
    unsigned int RPCId, ProcedureId;
    int arg1, arg2;
}RPCMessage;

int arg1(char msg[], int index){
    char a[10];
    for(int i = 0; i < index; i++){
        if(msg[i] != ' '){
            a[i] = msg[i];
        }
    }
    int num = atoi(a);
    return  num;
}
int arg2(char* msg, int index){
    char a[10];
    for(int i = index; i < strlen(msg); i++){
        if(msg[index+1] != ' '){
            a[i - index] = msg[i+1];
        }
    }
    //printf("\n -- number[%s] --", a);
    int num = atoi(a);
    return  num;
}

Status Op(RPCMessage *rm, int arg1, int arg2, int* ans){
    switch (rm->ProcedureId){
        case 1: *ans = arg1 + arg2;
            return OK;
        case 2: *ans = arg1 - arg2;
            return OK;
        case 3: *ans = arg1 * arg2;
            return OK;
        case 4:
            if(rm->arg2 != 0){
                *ans = arg1 / arg2;
                return OK;
            }else{
                *ans = 000;
                return DivZero;
            }
        default:
            return BAD;
    }
}

void Marshall(RPCMessage *rm, Message *message){
    ntohs(message);
}
void unMarshall(RPCMessage *rm, Message *message){
    char msg[sizeof(message)];
    strcpy(msg, message);
    for(int i = 0; i < strlen(msg); i++){
        if(msg[i] == '+'){
            rm->ProcedureId = 1;
            rm->arg1 = arg1(msg, i);
            rm->arg2 = arg2(msg, i);
        }
        else if(msg[i] == '-'){
            rm->ProcedureId = 2;
            rm->arg1 = arg1(msg, i);
            rm->arg2 = arg2(msg, i);
        }
        else if(msg[i] == '*'){
            rm->ProcedureId = 3;
            rm->arg1 = arg1(msg, i);
            rm->arg2 = arg2(msg, i);
        }
        else if(msg[i] == '/'){
            rm->ProcedureId = 4;
            rm->arg1 = arg1(msg, i);
            rm->arg2 = arg2(msg, i);
        }
    }
    int ans;
    Status o = Op(rm,rm->arg1, rm->arg2, &ans);
    //memset(message,'\0',strlen(message));
    if(o == BAD){
        char temp[1000] = "Status [Bad Request]";
        strcpy(message,temp);
    }
    else if(o == DivZero){
        char temp[1000] = "Status [DivZero]";
        strcpy(message,temp);
    }
    else{
        char temp[100] = "Status [OK]\nThe answer to [ ", str1[30], str2[30] = " ] is [ ", final[30];
        strcpy(str1, message);
        snprintf(final, sizeof(final), "%d", ans);
        strcat(temp, str1);
        strcat(temp, str2);
        strcat(temp, final);
        strcat(temp, " ]");
        char string[strlen(temp)];
        strcpy(string, temp);
        strcpy(message,string);//outputs the answer
    }
    htonl(message);
}
void die(char *s)
{
    perror(s);
    exit(1);
}
Status SendReply(Message *replyMessage, int s, SocketAddress clientSA){
    int sendId = sendto(s, replyMessage, strlen(replyMessage), 0, (struct sockaddr*)&clientSA, sizeof(clientSA));
    Status sn = OK;
    if(sendId == -1){
        sn = BAD;
        die("sendto()");
    }
}
Status GetRequest(Message *callMessage, int s, SocketAddress *clientSA){
    int slen = sizeof(clientSA);
    if(strlen(callMessage) > 1000){
        return WRONGLENGTH;
    }
    else{
        if (recvfrom(s, callMessage, 1000, 0, (struct sockaddr*) &clientSA, &slen) == -1){ die("recvfrom()"); }
        memset(callMessage,'\0', strlen(callMessage));
        return OK;
    }
}

int main(void)
{
    struct sockaddr_in si_me, clientSA;
    int s;
    char buf[1024];
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){ die("socket"); }
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1){ die("bind"); }
    RPCMessage* ms;
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);
        //GetRequest(buf, s, &clientSA);//try to receive some data, this is a blocking call.
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', 1024);
        int slen = sizeof(clientSA);
        if ((recvfrom(s, buf, 1024, 0, (struct sockaddr *) &clientSA, &slen)) == -1){die("recvfrom()");}//receive data

        //try to receive some data, this is a blocking call
        printf("Received packet from %s:%d\n", inet_ntoa(clientSA.sin_addr), ntohs(clientSA.sin_port));//print details of the client.
        printf("Data from %s\n" , buf);//print data received by the client.
        for(int i=0; i < strlen(buf); i++){
            if(buf[i] == '+' || buf[i] == '-' || buf[i] == '*' || buf[i] == '/'){
                unMarshall(ms, &buf);
                break;
            }
        }
        Marshall(ms, &buf);
        if(buf[0] == 'q' || buf == "stop"){//check if input is stopping character!
            char msg[] = "you terminated the conncection";//now reply the client with the custom message.
            if (sendto(s, msg, strlen(msg), 0, (struct sockaddr*) &clientSA, slen) == -1){die("sendto()");}//sends data to client
            printf("process terminated by client");
            break;
        }
        //printf("\nMessage[%s]\n", buf);
        strcpy(buf, "SERVER: request received!");
        //SendReply(buf, s, clientSA);//now reply the client with the some data
        if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &clientSA, slen) == -1)
        {
            die("sendto()");
        }
    }
    close(s);
    return 0;
}
