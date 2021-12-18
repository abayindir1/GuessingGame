#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX 80
#define PORT 8080
 
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // creating socket, and verifying
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    else
        printf("Socket successfully created\n");
   memset(&servaddr, 0, sizeof(servaddr));
   

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   // listening for request
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed\n");
        exit(0);
    }
    else
        printf("Server listening\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed\n");
        exit(0);
    }
    else
        printf("Server accept the client\n");
     
     
     //---------------------------------------game------------------------------------------
     char buffer[MAX];
    srand(time(NULL));
    int random = 1 + (rand() % 10);
    while(1){
        memset(buffer, 0, MAX);
   
        read(connfd, buffer, sizeof(buffer));
        if(atoi(buffer) > random){
          write(connfd, "Guess lower\n", sizeof("Guess lower"));
        }else if(atoi(buffer) < random){
          write(connfd, "Guess higher\n", sizeof("Guess higher"));
        }else{
          write(connfd, "Congrats you got it right\n", sizeof("Congrats you got it right"));
        }
        
    }
    //---------------------------------------------------------------------------------------
    //close(sockfd);
}