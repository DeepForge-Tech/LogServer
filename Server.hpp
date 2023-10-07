// Server side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "json/json.h"
#include <json/value.h>
#include "json/reader.h"
#include "../DatabaseConnect.cpp"

#define PORT 743
#define MAX_SIZE 16384

using namespace std;

namespace LogServer
{
    int sockfd;
    char buffer[MAX_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    int n;
    const char* SUCCESS = "Information added successfully";
    class Server
    {
    public:
        // Server();
        // ~Server();
        int JSON_to_DB(char[MAX_SIZE]);
        void CreateSocket();
        void SetInformation();
        void BindSocket();
        void Start();
    private:
    };
}