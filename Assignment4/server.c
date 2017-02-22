#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void handler(int);
int sum_total = 0;
int line = 0;

int main()
{
    // define sockfd
    int server_sockfd;
    if((server_sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)  
    {  
        perror("socket");  
        exit(1);  
    }

    // define sockaddr_in, port number is 10015
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(10020);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind to client
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr)) == -1){

        perror("bind");
        exit(1);
    }

    //listening
    if(listen(server_sockfd,100) == -1){

        perror("listen");
        exit(1);
    }

    //client socket
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn < 0){

        perror("connect");
        exit(1);
    }

    FILE *fp;
    int i = 0;
    int sum = 0;

    while(1){

        memset(buffer,0,sizeof(buffer));
        // receive data and put into buffer
        int len = recv(conn, buffer, sizeof(buffer),0);

        // if it's not "exit", calculate digits.
        if(strcmp(buffer,"exit\n") != 0){

            i = 0;
            sum = 0;
            while (buffer[i]!='\n'){

                if ((buffer[i] >= '0') && (buffer[i] <= '9')) sum++;
                i++;
            }
        
            //output the result in screen
            printf("---->>>> received: %s", buffer); 

            //calculate lines received
            line++; 

            // this is fot total counts of digits
            sum_total = sum_total + sum;

            // write data into file.
	       if ((fp = fopen("secrets.out","ab+")) == NULL) printf("error!");
                
            fprintf(fp,"original input:%sDigit count:%d\n",buffer,sum);
            fclose(fp);
        }else{  // if it's "exit", just exit;
            printf("---->>>> receiced exit\n");
            printf("---->>>> exiting...\n");
            break;
        }
        //detect CTRL+C and call handler
        signal(SIGINT, handler);
    }
    close(conn);
    close(server_sockfd);
    return 0;
}

// print lines and digits number.
void  handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("Received lines: %d\n",line);
    printf("Total digits: %d\n",sum_total);
    exit(0);
}
