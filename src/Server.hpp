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
// #define IP_ADDRESS "64.226.99.105"
using namespace std;

namespace LogServer
{
    int sockfd;
    char buffer[MAX_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    int n;
    const char* SUCCESS = "Information added successfully";
    string ProjectDir = std::filesystem::current_path().generic_string();
    Database database;
    string DatabasePath = ProjectDir + "/DB/Logs.db";
    string IP_ADDRESS;

    class Server
    {
    public:
        int JSON_to_DB(Json::Value JSON_LOGS);
        void CreateSocket();
        void SetInformation();
        void BindSocket();
        void Start();
        Server(char ip_address)
        {
            IP_ADDRESS = to_string(ip_address);
            database.open(&DatabasePath);
            cout << "Server started on " << IP_ADDRESS << ":" << PORT << endl;
        }
        // ~Server();
    private:
    };
}