// Server side implementation of UDP client-server model
// #include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "json/json.h"
#include "json/value.h"
#include "json/reader.h"
#include "DatabaseConnect.hpp"
#include <cstdlib>
#include <fstream>

#define MAX_SIZE 16384

using namespace std;
using namespace DB;

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
    const char *SUCCESS = "Information added successfully";
    string ProjectDir = std::filesystem::current_path().generic_string();
    Database database;
    string DatabasePath = ProjectDir + "/DB/Logs.db";
    const string IP_ADDRESS = "0.0.0.0";
    int PORT;

    class Server
    {
    public:
        int JSON_to_DB(Json::Value JSON_LOGS);
        void CreateSocket();
        void SetInformation();
        void BindSocket();
        void Start();
        Server(int port)
        {
            PORT = port;
            CheckDB();
            database.open(&DatabasePath);
            cout << "Server started on " << IP_ADDRESS << ":" << PORT << endl;
        }
        // ~Server();
    private:
        void CheckDB()
        {
            filesystem::path DB_DIR(DatabasePath);
            DB_DIR = DB_DIR.parent_path().string();
            if (filesystem::exists(DB_DIR) == false)
            {
                filesystem::create_directory(DB_DIR);
            }
            /* The bellow code is checking if a file exists at the specified path. If the file does not exist, it creates a new file and writes an empty string to it. Then, it opens a database connection using the file as the database path. It checks if a table named "Applications" exists in the database. If the table does not exist, it creates the table with the specified columns. Finally, it inserts values into the "Applications" table. */
            if (filesystem::exists(DatabasePath) == false)
            {
                ofstream file(DatabasePath);
                file << "";
                file.close();
            }
        }
    };
}