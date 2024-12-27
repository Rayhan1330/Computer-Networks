#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


int main(int argc,char *argv[]){
    //Creation of client sockets
    int clntSock1 = socket(AF_INET,SOCK_STREAM,0);
    int clntSock2 = socket(AF_INET,SOCK_STREAM,0);
    int clntSock3 = socket(AF_INET,SOCK_STREAM,0);
    int clntSock4 = socket(AF_INET,SOCK_STREAM,0);
    
    //Binding the sockets
    //Client 1
    struct sockaddr_in clntAddr1;
    clntAddr1.sin_family = AF_INET;
    clntAddr1.sin_port = htons(atoi(argv[1]));
    clntAddr1.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock1,(struct sockaddr *)&clntAddr1,sizeof(clntAddr1));
    
    //Client 2
    struct sockaddr_in clntAddr2;
    clntAddr2.sin_family = AF_INET;
    clntAddr2.sin_port = htons(atoi(argv[2]));
    clntAddr2.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock2,(struct sockaddr *)&clntAddr2,sizeof(clntAddr2));
    
    //Client 3
    struct sockaddr_in clntAddr3;
    clntAddr3.sin_family = AF_INET;
    clntAddr3.sin_port = htons(atoi(argv[3]));
    clntAddr3.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock3,(struct sockaddr *)&clntAddr3,sizeof(clntAddr3));
    
    //Client 4
    struct sockaddr_in clntAddr4;
    clntAddr4.sin_family = AF_INET;
    clntAddr4.sin_port = htons(atoi(argv[4]));
    clntAddr4.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock4,(struct sockaddr *)&clntAddr4,sizeof(clntAddr4));
    
    //Listening
    listen(clntSock1,1);
    listen(clntSock2,1);
    listen(clntSock3,1);
    listen(clntSock4,1);
    
    //Accepting connections
    int servSock1 = accept(clntSock1,NULL,NULL);
    int servSock2 = accept(clntSock2,NULL,NULL);
    int servSock3 = accept(clntSock3,NULL,NULL);
    int servSock4 = accept(clntSock4,NULL,NULL);
    
    //Getting the inputs
    char ip[255];
    printf("Enter the IP address: ");
    scanf("%s",ip);
    send(servSock1,ip,sizeof(ip),0);
    send(servSock2,ip,sizeof(ip),0);
    send(servSock3,ip,sizeof(ip),0);
    send(servSock4,ip,sizeof(ip),0);
    
    char mac[255] = " ";
    while(1){
        while(strcmp(mac," ") == 0)
            recv(servSock1,mac,sizeof(mac),0);
        if(strcmp(mac,"No")){
            printf("Mac address: %s\n",mac);
            break;
        }
        strcpy(mac," ");
        while(strcmp(mac," ") == 0)
            recv(servSock2,mac,sizeof(mac),0);
        if(strcmp(mac,"No")){
            printf("Mac address: %s\n",mac);
            break;
        }
        strcpy(mac," ");
        while(strcmp(mac," ") == 0)
            recv(servSock3,mac,sizeof(mac),0);
        if(strcmp(mac,"No")){
            printf("Mac address: %s\n",mac);
            break;
        }
        strcpy(mac," ");
        while(strcmp(mac," ") == 0)
            recv(servSock4,mac,sizeof(mac),0);
        if(strcmp(mac,"No")){
            printf("Mac address: %s\n",mac);
            break;
        }
        printf("No mac address found!\n");
        break;
    }
}
