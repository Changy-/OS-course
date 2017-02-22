#include <signal.h>
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	// create socket
	int sock_client;
	if((sock_client = socket(AF_INET,SOCK_STREAM,0)) < 0){

        perror("socket");
        exit(1);
    }

    // define sockaddr_in, port number is 10020
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10020);  
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //server ip
 
    //Conect to server
    if (connect(sock_client, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){

        perror("connect.....");
        exit(1);
    }

    printf("---->>>> has connected to server <<<<----\n");
    char sendbuf[1024];
    printf("---->>>> Input exit to exit<<<<----\n");

    // get user input
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL){
    	// if detect secret code, send it to server
        if(strstr(sendbuf, "C00L")!=NULL){

            printf("---->>>>detect code C00L<<<<----\n");
            send(sock_client, sendbuf, strlen(sendbuf),0);

        }else if(strcmp(sendbuf,"exit\n") == 0){
        	// if detect "exit", send it to server and exit the program
            send(sock_client, sendbuf, strlen(sendbuf),0); 
            break;
        }

        // set memory data into 0;
        // resuse it next time;
        memset(sendbuf, 0, sizeof(sendbuf));
    }
    // close socket
    close(sock_client);
    return 0;
}