#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_LINE 1024

int file_exist(char *dirpath,char *fname,char *dest){
    DIR *dr;
    if(!(dr = opendir(dirpath))){
        perror("Cannot open directory!");
        return 0;
    }
    struct dirent *de;
    struct stat file_stat;
    char full_path[1024];
    while((de = readdir(dr))!= NULL){
        snprintf(full_path,sizeof(full_path),"%s/%s",dirpath,de->d_name);
        if(lstat(full_path,&file_stat) == -1)
            continue;
        if(S_ISREG(file_stat.st_mode) && strcmp(de->d_name,fname) == 0){
            strcpy(dest,full_path);
            closedir(dr);
            return 1;
        }
        if(S_ISDIR(file_stat.st_mode) && strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0){
            if(file_exist(full_path,fname,dest)){
                return 1;
                closedir(dr);
            }
        }
        
    }
    closedir(dr);
    return 0;
}

int main(int argc,char *argv[]){
    int clntSock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in clntAddr;
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_port = htons(atoi(argv[1]));
    clntAddr.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock,(struct sockaddr *)&clntAddr,sizeof(clntAddr));
    listen(clntSock,1);
    int servSock = accept(clntSock,NULL,NULL);
    printf("Connected!\n");
    char filename[50];
    recv(servSock,filename,50,0);
    printf("File name is: %s\n",filename);
    char root_directory[] = ".";
    char dest[MAX_LINE];
    int check = file_exist(root_directory,filename,dest);
    char fcontent[1024] = " ";
    if(check == 1){
        int fd = open(dest,O_RDONLY);
        read(fd,fcontent,MAX_LINE);
        printf("%s\n",fcontent);
    }
    else{
        printf("Not found!\n");
    }
}
