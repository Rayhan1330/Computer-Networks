#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char *argv[]){
    char c;
    int sockD = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int connectStatus = connect(sockD,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(connectStatus == -1)
        printf("Error\n");
    else{
        char clntMsg[255] = " ";
        while(1){
            char servMsg[255] = " ";
            while(strcmp(servMsg," ") == 0)
                recv(sockD,servMsg,sizeof(servMsg),0);
            printf("Message from server: %s\n",servMsg);
            if(strcmp(servMsg,"Bye") == 0)
                break;
            printf("Enter message to pass: ");
            scanf("%[^\n]",clntMsg);
            scanf("%c",&c);
            send(sockD,clntMsg,sizeof(clntMsg),0);
            if(strcmp(clntMsg,"Bye") == 0)
                break;
        }
        
    }
    close(sockD);
}

