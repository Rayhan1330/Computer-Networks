#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc,char *argv[]){
    int clntSock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in clntAddr;
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_port = htons(atoi(argv[1]));
    clntAddr.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock,(struct sockaddr *)&clntAddr,sizeof(clntAddr));
    listen(clntSock,1);
    printf("Listening!\n");
    int servSock = accept(clntSock,NULL,NULL);
    printf("Connected!\n");
    int ack = 1;
    int seq_no;
    char packet_recv[16] = " ";
    int bytes_received;
    char dest;
    char remaining[20];
    int error = 0;
    char length[255] = " ";
    while(1){
        while(strcmp(packet_recv," ") == 0)
            bytes_received = recv(servSock,packet_recv,16,0);
        if(strcmp(packet_recv,"END") == 0)
            break;
        
        printf("\nReceived packet: %s\n",packet_recv);
        sscanf(packet_recv,"F-%c-%d-%s",&dest,&seq_no,remaining);
        if(ack == seq_no){
            ack++;
        }
        else{
            printf("\nExpecting ack: %d but received packet: %d\n",ack,seq_no);
            error = 1;
        }
        strcpy(packet_recv," ");
    }
    strcpy(packet_recv," ");
    if(error == 1){
        printf("\n\nMissing packet no: %d\n",ack);
        char *to_send = (char *)malloc(sizeof(char)*1);
        sprintf(to_send,"%d",ack);
        send(servSock,to_send,1,0);
        
        while(1){
            while(strcmp(packet_recv," ") == 0)
                bytes_received = recv(servSock,packet_recv,16,0);
            if(strcmp(packet_recv,"END") == 0)
                break;
            
            printf("Received packet: %s\n",packet_recv);
            strcpy(packet_recv," ");
        }
    }
    else{
        send(servSock,"Success",sizeof("Success"),0);
        
    }
    printf("Transmission over!!\n");
    
}
