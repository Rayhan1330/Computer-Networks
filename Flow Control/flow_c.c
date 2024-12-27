#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc,char *argv[]){
    int sockD = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int con = connect(sockD,(struct sockaddr *)&servAddr,sizeof(servAddr));
    char clear_buffer;
    if(con == -1)
        printf("Error!\n");
    else{
        printf("Connected!\n");
        char *input = (char *)malloc(sizeof(char)*255);
        printf("Enter the input data: ");
        scanf("%s",input);
        scanf("%c",&clear_buffer);
        
        //Splitting into packets of 4
        int input_length = strlen(input);
        int no_of_packets = input_length/4;
        if(input_length%4 != 0)
            no_of_packets++;
        printf("No of packets: %d\n",no_of_packets);
        char **packets = (char **)malloc(sizeof(char *)*no_of_packets);
        int index_of_input = 0;
        printf("Packets: ");
        for(int i = 0; i < no_of_packets; i++){
            packets[i] = (char *)malloc(sizeof(char)*4);
            for(int j = 0; j < 4; j++){
                if(input[index_of_input] == '\0') break;
                packets[i][j] = input[index_of_input++];
            }
            printf("%s ",packets[i]);
        }
        printf("\n");
        char dest;
        printf("Enter source: ");
        scanf("%c",&dest);
        scanf("%c",&clear_buffer);
        printf("Enter destination: ");
        scanf("%c",&dest);
        scanf("%c",&clear_buffer);
        char packet_to_send1[16];
        for(int i = 0; i < no_of_packets; i++){
            char choice;
            printf("Send or not?(Y/N): ");
            scanf("%c",&choice);
            scanf("%c",&clear_buffer);
            
            //Adding header
            char *packet_to_send = (char *)malloc(sizeof(char)*20);
            sprintf(packet_to_send,"F-%c-%d-%s-FCS-F",dest,i+1,packets[i]);
            int packet_length = strlen(packet_to_send);
            printf("Packet%d: %s, length: %d\n",i+1,packet_to_send,packet_length);
            if(choice == 'Y'){
                
                int bytes_sent = send(sockD,packet_to_send,16,0);
            }
            free(packet_to_send);
        }
        send(sockD,"END",sizeof("END"),0);
        
        char confirm[255];
        char length[255];
        int bytes_received = recv(sockD,confirm,sizeof(confirm),0);
        if(strcmp(confirm,"Success") != 0){// In case of error
            int number = atoi(confirm);
            printf("\n\nResending from packet no: %d\n",number);
            for(int i=number-1; i<no_of_packets; i++){
                char *packet_to_send = (char *)malloc(sizeof(char)*20);
                sprintf(packet_to_send,"F-%c-%d-%s-FCS-F",dest,i+1,packets[i]);
                int packet_length = strlen(packet_to_send);
                int bytes_sent = send(sockD,packet_to_send,16,0);
            }
            send(sockD,"END",sizeof("END"),0);
            
        }
    }
    printf("Transmission over!!\n");
}
