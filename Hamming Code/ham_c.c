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
    //Main program
    
    printf("Enter the input: ");
    char input[100];
    scanf("%s",input);
    
    //Length of string
    int m = strlen(input);
    printf("Length of string: %d\n",m);
    
    //To find m
    int r = 0;
    while(1){
        if(pow(2,r) >= (m + r + 1))
            break;
        r++;
    }
    printf("Number of r bits: %d\n",r);
    
    //Filling the redundant bits
    char *encoded = (char *)malloc(sizeof(char)*(m+r+1));
    int ind_of_input = m-1; //we are going to take indexes from reverse
    int r_temp = 0;
    for(int i = 0; i < m+r+1; i++){
        if(i+1 == pow(2,r_temp)){
            encoded[i] = 'r';
            r_temp++;
        }
        else{
            encoded[i] = input[ind_of_input--];
        }
    }
    char *reverse = rev(encoded,m+r);
    printf("Data before encoding: %s\n",reverse);
    
    //Encoding
    r_temp = 0;
    for(int i=0; i<m+r; i++){
        if(encoded[i] == 'r'){
            printf("r%d\n",r_temp+1);
            int skip = pow(2,r_temp++);
            int no_of_1 = 0;
            for(int j=i; j<m+r; j = j+skip){
                int last = j+skip;
                while(j<last){
                    if(encoded[j] == '1')
                        no_of_1++;
                    j++;
                }
            }
            printf("No of 1: %d\n",no_of_1);
            if(no_of_1%2 == 1)
                encoded[i] = '1';
            else
                encoded[i] = '0';
            printf("Value of r%d: %c\n",r_temp,encoded[i]);
        }
        
    }
    encoded = rev(encoded,m+r);
    printf("Data after encoding: %s\n",encoded);
    
    printf("Which bit do you want to change? (Indexes start from 1): ");
    int change;
    scanf("%d",&change);
    int changed_index = (m+r)-1-(change-1);
    if(encoded[changed_index] == '1')
        encoded[changed_index] = '0';
    else
        encoded[changed_index] = '1';
    printf("Changed value: %s\n",encoded);
    
    //Client server connection
    int sockD = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int con = connect(sockD,(struct sockaddr *)&servAddr, sizeof(servAddr));
    if(con == -1)
        printf("Error!!\n");
    else{
        printf("Successfully connected!\n");
        send(sockD,encoded,m+r,0);
        char *r_bit = (char *)malloc(sizeof(char));
        sprintf(r_bit,"%d",r);
        send(sockD,r_bit,1,0);
    }
    
}
