#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
	// create server socket similar to what was done in
	// client program
	int clntSockD = socket(AF_INET, SOCK_STREAM, 0);

	// string store data to send to client
	char ch;
	int ind = 0;
	int alp,vow,dig,spcl;

	//scanf("%[^\n]",clntMsg);

	// define server address
	struct sockaddr_in clntAddr;

	clntAddr.sin_family = AF_INET;
	clntAddr.sin_port = htons(atoi(argv[1]));
	clntAddr.sin_addr.s_addr = INADDR_ANY;

	// bind socket to the specified IP and port
	bind(clntSockD, (struct sockaddr*)&clntAddr,
		sizeof(clntAddr));

	// listen for connections
	listen(clntSockD, 1);

	// integer to hold client socket.
	int serverSocket = accept(clntSockD, NULL, NULL);
	
	
    char clntMsg[255] = " ",servmsg[255] = " ";
    // send's messages to client socket
    send(serverSocket, clntMsg, sizeof(clntMsg), 0);
    while(strcmp(servmsg," ") == 0)
        recv(serverSocket, servmsg, sizeof(servmsg), 0);
    printf("Message from Client: %s\n",servmsg);
    int n = strlen(servmsg);
    int counts[] = {0,0,0,0};
    char c;
    for(int i=0; i<n; i++){
        c = servmsg[i];
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
            counts[1]++;
            counts[0]++;
        }
        else if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U'){
            counts[1]++;
            counts[0]++;
        }
        else if((c>='a' && c<='z') || (c>='A' && c<='Z')){
            counts[0]++;
        }
        else if(c>='1' && c<='9'){
            counts[2]++;
        }
        else{
            counts[3]++;
        }
    }
    sprintf(clntMsg,"Alphabets: %d\nVowels:%d\nDigits: %d\nSpecial Characters: %d\n",counts[0],counts[1],counts[2],counts[3]);
    send(serverSocket,clntMsg,sizeof(clntMsg),0);
	
	close(clntSockD);
	return 0;
}

