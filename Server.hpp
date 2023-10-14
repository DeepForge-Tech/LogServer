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
    Database database;

    class Server
    {
    public:
        int JSON_to_DB(Json::Value JSON_LOGS);
        void CreateSocket();
        void SetInformation();
        void BindSocket();
        void Start();
        Server()
        {
            database.open(to_string("./DB/Logs.db"));
        }
        ~Server();
    private:
    };
}