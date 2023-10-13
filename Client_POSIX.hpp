#include <iostream>
#include <winsock2.h>
#include <fstream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#define IP_ADDRESS "64.226.99.105" // or "localhost" - ip address of UDP server
#define BUFFER_MAX_LENGHT 16384           // max length of answer
#define PORT 743

using namespace std;

namespace POSIX
{
    class Client
    {
        WSADATA ws;
        sockaddr_in server;
        int client_socket;
        bool isOpen = false;

    public:
        void CreateSocket()
        {
            try
            {
                /* The code `WSAStartup(MAKEWORD(2, 2), &ws)` initializes the Winsock library. It is necessary to call this function before using any other Winsock functions. */
                WSAStartup(MAKEWORD(2, 2), &ws);
                if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
                {
                    printf("socket() failed with error code: %d", WSAGetLastError());
                    // return 2;
                }
                isOpen = true;
            }
            catch (exception &error)
            {
                throw runtime_error("Error creating socket.");
            }
        }

        void SetInformation()
        {
            memset((char *)&server, 0, sizeof(server));
            server.sin_family = AF_INET;
            server.sin_port = htons(PORT);
            server.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
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
            sendto(client_socket, data, strlen(data), 0, (sockaddr *)&server, sizeof(sockaddr_in));
        }

        void SendTextMessage(string message)
        {
            const char *new_message = message.c_str();
            sendto(client_socket, new_message, strlen(new_message), 0, (sockaddr*)&server, sizeof(sockaddr_in));
        }

        void GetInformation()
        {
            char answer[BUFFER_MAX_LENGHT];
            int slen = sizeof(sockaddr_in);
            int answer_length;
            answer_length = recvfrom(client_socket, answer, BUFFER_MAX_LENGHT, 0, (sockaddr *)&server, &slen);
        }

        void CloseSocket()
        {
            if (isOpen == true)
            {
                closesocket(client_socket);
                WSACleanup();
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