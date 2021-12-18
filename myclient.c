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
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    else{
        printf("Socket successfully created\n");
    }
    memset(&servaddr, 0, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed\n");
        exit(0);
    }
    else{
        printf("Connected to the server\n");
   }
   printf("Start guessing numbers from 1 to 10\n");
   
     char buffer[MAX];
    int n;
    while(1) {
        memset(buffer, 0, MAX);
        printf("Enter the guess : ");
        n = 0;
        while ((buffer[n++] = getchar()) != '\n');
        write(sockfd, buffer, sizeof(buffer));
        memset(buffer, 0, MAX);
        read(sockfd, buffer, sizeof(buffer));
        printf("From Server: %s", buffer);
        
        if ((strncmp(buffer, "Congrats you", 12)) == 0) {
            printf("Client Exit\n");
            break;
        }
        
    }
    close(sockfd);
}