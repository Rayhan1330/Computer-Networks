#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    int sockD = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int con = connect(sockD,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(con == -1)
        printf("Error!\n");
    else{
        printf("Connected!\n");
        printf("Enter filename: ");
        char filename[50];
        scanf("%s",filename);
        send(sockD,filename,50,0);
    }
}
