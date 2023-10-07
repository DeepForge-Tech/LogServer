#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>

#define PORT 576
#define MAXLINE 16384

using namespace std;
// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n;
    socklen_t len;
    // while(true)
    // {
    //     std::cout << "Enter string:";
    //     string str;
    //     getline(std::cin,str);
    //     const char *hello = str.c_str();
    //     sendto(sockfd, (const char *)hello, strlen(hello),
    //         MSG_CONFIRM, (const struct sockaddr *) &servaddr,
    //             sizeof(servaddr));
    //     std::cout<<"Hello message sent."<<std::endl;

    //     n = recvfrom(sockfd, (char *)buffer, MAXLINE,
    //                 MSG_WAITALL, (struct sockaddr *) &servaddr,
    //                 &len);
    //     buffer[n] = '\0';
    //     std::cout<<"Server :"<<buffer<<std::endl;
    // }
    while(true)
    {
        FILE *fp;
        char data[MAXLINE];
        if ((fp=fopen("./toJson.json", "rb"))==NULL) {
            printf ("Cannot open file.\n");
            exit(1);
        }
        fread(data, sizeof(char), MAXLINE, fp);
        // if(!=MAXLINE) {
        //     if(feof(fp)) printf("Premature end of file.");
        //     else printf("File read error.");
        // }
        fclose(fp);
        const char *hello = "data 1";
        sendto(sockfd, data, strlen(data),
            MSG_CONFIRM, (const struct sockaddr *)&servaddr,
            sizeof(servaddr));
        std::cout << "Hello message sent." << std::endl;

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *)&servaddr,
                    &len);
        buffer[n] = '\0';
        sleep(1);
    }
    close(sockfd);
    return 0;
}