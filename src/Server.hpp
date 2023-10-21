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
    /* `int sockfd;` is declaring a variable `sockfd` of type `int`. This variable is used to store the file descriptor of the socket that will be created for the server. The file descriptor is a unique identifier for the socket that is used to perform various operations on the socket, such as sending and receiving data. */
    int sockfd;
    char buffer[MAX_SIZE];
    /* The line `struct sockaddr_in servaddr, cliaddr;` is declaring two variables `servaddr` and `cliaddr` of type `struct sockaddr_in`. */
    struct sockaddr_in servaddr, cliaddr;
    /* `socklen_t len;` is declaring a variable `len` of type `socklen_t`. */
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
        Server(string ip_address)
        {
            IP_ADDRESS = ip_address;
            database.open(&DatabasePath);
            cout << "Server started on " << IP_ADDRESS << ":" << PORT << endl;
        }
        // ~Server();
    private:
    };
}