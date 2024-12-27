#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

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
        char *ip = malloc(sizeof(char)*100),*mac = malloc(sizeof(char)*100);
        printf("Enter IP address: ");
        scanf("%s",ip);
        printf("Enter mac address: ");
        scanf("%s",mac);
        char msg[255] = " ";
        while(strcmp(msg," ") == 0)
            recv(sockD,msg,sizeof(msg),0);
        printf("Received msg: %s\n",msg);
        if(strcmp(msg,ip)==0){
            printf("yup");
            send(sockD,mac,sizeof(mac),0);
        }
        else{
            send(sockD,"No",2,0);
        }
    }
}
