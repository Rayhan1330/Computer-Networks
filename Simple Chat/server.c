#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char c;
    int clnt1 = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in clntAddr1;
    clntAddr1.sin_family = AF_INET;
    clntAddr1.sin_port = htons(atoi(argv[1]));
    clntAddr1.sin_addr.s_addr = INADDR_ANY;
    bind(clnt1,(struct sockaddr*)&clntAddr1,sizeof(clntAddr1));
    listen(clnt1,1);
    int servSock1 = accept(clnt1,NULL,NULL);
    char servMsg[255];
    while(1){
        char clntMsg1[255] = " ";
        printf("Enter a message for the clients: ");
        scanf("%[^\n]",servMsg);
        scanf("%c",&c);
        send(servSock1,servMsg,sizeof(servMsg),0);
        if(strcmp(servMsg,"Bye")== 0)
            break;
        while(strcmp(clntMsg1," ") == 0)
            recv(servSock1,clntMsg1,sizeof(clntMsg1),0);
        printf("Message from client 1: %s\n",clntMsg1);
        if(strcmp(clntMsg1,"Bye") == 0)
            break;
        
    }
    close(clnt1);
    close(servSock1);
}

