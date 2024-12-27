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
    int clnt2 = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in clntAddr2;
    clntAddr2.sin_family = AF_INET;
    clntAddr2.sin_port = htons(atoi(argv[2]));
    clntAddr2.sin_addr.s_addr = INADDR_ANY;
    bind(clnt1,(struct sockaddr*)&clntAddr1,sizeof(clntAddr1));
    bind(clnt2,(struct sockaddr*)&clntAddr2,sizeof(clntAddr2));
    listen(clnt1,1);
    listen(clnt2,1);
    int servSock1 = accept(clnt1,NULL,NULL);
    int servSock2 = accept(clnt2,NULL,NULL);
    char servMsg[255];
    send(servSock1,"Connected!",sizeof("Connected!"),0);
    send(servSock2,"Connected!",sizeof("Connected!"),0);
    while(1){
        char clntMsg1[255] = " ",clntMsg2[255] = " ";
        if(strcmp(servMsg,"Bye")== 0)
            break;
        while(1){
            
        }
        
            
        if(strcmp(clntMsg1,"Bye") == 0 || strcmp(clntMsg2,"Bye")==0)
            break;
        
    }
    close(clnt1);
    close(clnt2);
    close(servSock1);
    close(servSock2);
}
