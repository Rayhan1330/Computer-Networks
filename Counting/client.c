#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{

	int sockD = socket(AF_INET, SOCK_STREAM, 0);
	char echo[50];

	int counts[] = {0,0,0,0};
	int i;
	char c;
	char servmsg[255] = " ",clntMsg[255];

	struct sockaddr_in servAddr;

	servAddr.sin_family = AF_INET;
	servAddr.sin_port= htons(atoi(argv[1])); // use some unused port number
	servAddr.sin_addr.s_addr = INADDR_ANY;

	int connectStatus= connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

	if (connectStatus == -1) {
		printf("Error...\n");
	}

    else {
        
        char strData[255];
        char clntMsg[255] = " ";
        printf("Enter message: ");
        scanf("%[^.]",clntMsg);
        send(sockD, clntMsg, sizeof(clntMsg), 0);
        while(strcmp(servmsg," ") == 0)
            recv(sockD,servmsg,sizeof(servmsg),0);
        printf("Message from server: %s\n",servmsg);
        
    }
	
	close(sockD);
	return 0;
}
