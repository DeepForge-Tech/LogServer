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

#define PORT 743
#define MAXLINE 16384

using namespace std;

namespace LogClient
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    int n;
    socklen_t len;

    class Client
    {
    public:
        void CreateSocket()
        {
            // Creating socket file descriptor
            if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
            }

            memset(&servaddr, 0, sizeof(servaddr));
        }
        void SetInformation()
        {
            // Filling server information
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(PORT);
            servaddr.sin_addr.s_addr = inet_addr("64.226.99.105");
        }
        void SendMessage(char message[MAXLINE])
        {
            const char *new_message = message;
            sendto(sockfd, data, strlen(data), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        }
        void GetInformation()
        {
            n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len)
            buffer[n] = '\0';
        }
        char OpenJSON(string filename)
        {
            FILE *fp;
            char data[MAXLINE];
            if ((fp = fopen(filename.c_str(), "rb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }
            fread(data, sizeof(char), MAXLINE, fp);
            fclose(fp);
            return data;
        }
        void CloseSocket()
        {
            close(sockfd);
        }
        Server()
        {
            CreateSocket();
            SetInformation();
        }
        ~Server()
        {
            CloseSocket()
        }

    private:
    };
}