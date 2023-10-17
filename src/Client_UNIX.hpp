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
#define BUFFER_MAX_LENGHT 16384
#define IP_ADDRESS "64.226.99.105"

using namespace std;
namespace UNIX
{
    int sockfd;
    char buffer[BUFFER_MAX_LENGHT];
    struct sockaddr_in servaddr;
    int n;
    socklen_t len;
    bool isOpen = false;

    class Client
    {
    public:
        void CreateSocket()
        {
            try
            {
                // Creating socket file descriptor
                if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
                {
                    perror("socket creation failed");
                    exit(EXIT_FAILURE);
                }
            }
            catch (const std::exception &e)
            {
                throw runtime_error("Error creating socket");
            }
            memset(&servaddr, 0, sizeof(servaddr));
            isOpen = true;
        }
        void SetInformation()
        {
            // Filling server information
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(PORT);
            servaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        }
        void SendJSON(string path)
        {
            /* This code is responsible for reading the contents of a file specified by the `path` variable and storing it in the `data` array. */
            FILE *fp;
            char data[BUFFER_MAX_LENGHT];
            if ((fp = fopen(path.c_str(), "rb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }
            fread(data, sizeof(char), BUFFER_MAX_LENGHT, fp);
            fclose(fp);
            // const char *new_message = message;
            sendto(sockfd, data, strlen(data), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        }
        // void SendMessage(string message)
        // {
        //     const char *new_message = message.c_str();
        //     sendto(sockfd,new_message,strlen(new_message),(const stuct sockaddr *)&serveraddr,sizeof(servaddr));
        // }
        void GetInformation()
        {
            n = recvfrom(sockfd, (char *)buffer, BUFFER_MAX_LENGHT, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
            buffer[n] = '\0';
        }
        void CloseSocket()
        {
            if (isOpen == true)
            {
                close(sockfd);
                isOpen = false;
            }
        }
        Client()
        {
            CreateSocket();
            SetInformation();
        }
        ~Client()
        {
            CloseSocket();
        }

    private:
    };
}