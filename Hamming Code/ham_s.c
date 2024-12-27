#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>

char *rev(char *str,int n){
    char *reverse = (char *)malloc(sizeof(char)*(n+1));
    for(int i = 0; i < n; i++){
        reverse[i] = str[n-1-i];
    }
    return reverse;
}

int main(int argc,char *argv[]){
    int clntSock = socket(AF_INET,SOCK_STREAM,0);
    char encoded[255] = " ";
    char *encode;
    char r_bits[1] = " ";
    struct sockaddr_in clntAddr;
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_port = htons(atoi(argv[1]));
    clntAddr.sin_addr.s_addr = INADDR_ANY;
    bind(clntSock,(struct sockaddr *)&clntAddr,sizeof(clntAddr));
    printf("Listening\n");
    listen(clntSock,1);
    int servSock = accept(clntSock,NULL,NULL);
    printf("Connected!\n");
    //Receiving the encoded data
    while(strcmp(encoded," ") == 0)
        recv(servSock,encoded,sizeof(encoded),0);
    printf("Received encoded data!\n");
    //Receiving the number of r bits
    while(strcmp(r_bits," ") == 0)
        recv(servSock,r_bits,1,0);
    printf("Received no of r bits!\n");
    //Converting to int
    int r = atoi(r_bits);
    printf("Encoded data: %s\n",encoded);
    int n = strlen(encoded);
    encode = rev(encoded,n);
    char *error = (char *)malloc(sizeof(char)*r);
    int r_temp = 0;
    for(int i =0; i<n; i++){
        int pos = pow(2,r_temp);
        if(i+1 == pos){
            int no_of_1 = 0;
            for(int j=i; j<n; j = j+pos){
                int last = j + pos;
                while(j<last){
                    if(encode[j] == '1')
                        no_of_1++;
                    j++;
                }
            }
            if(no_of_1 %2 == 0)
                error[r_temp] = '0';
            else
                error[r_temp] = '1';
            r_temp++;
        }
    }
    char *err = rev(error,r);
    printf("Error (in binary): %s\n",err);
    
    //Changing binary to integer
    int err_or = 0;
    for(int i=0; i<r; i++){
        int ind = error[i] - '0';
        err_or = err_or + ind*pow(2,i);
    }
    printf("There is an error in bit number: %d\n",err_or);
}
