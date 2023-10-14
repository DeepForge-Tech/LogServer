#include "Server.hpp"

using namespace LogServer;

void Server::CreateSocket()
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
}

void Server::SetInformation()
{
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("64.226.99.105");
    servaddr.sin_port = htons(PORT);
}

void Server::BindSocket()
{
    if (bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}
int Server::JSON_to_DB(Json::Value JSON_LOGS)
{
    database.InsertLogInformationToTable("Logs",JSON_LOGS["Architecture"].asString(),
        JSON_LOGS["OS_NAME"].asString(),JSON_LOGS["Channel"].asString(),JSON_LOGS["FunctionName"].asString(),
        JSON_LOGS["LogText"].asString());
}

void Server::Start()
{
    CreateSocket();
    SetInformation();
    BindSocket();
    while (true)
    {
        len = sizeof(cliaddr); // len is value/result

        n = recvfrom(sockfd, (char *)buffer, MAX_SIZE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        buffer[n] = '\0';
        Json::Value JSON_LOGS;
        Json::Reader reader;
        reader.parse(buffer, JSON_LOGS);
        JSON_to_DB(JSON_LOGS);
        cout << JSON_LOGS["test"].asString() << endl;
        printf("Client: %s\n", buffer);
        sendto(sockfd, (const char *)SUCCESS, strlen(SUCCESS),MSG_CONFIRM, (const struct sockaddr *)&cliaddr,len);
        cout << "Hello message sent." << endl;
    }
}
// Driver code
int main()
{
    Server server;
    server.Start();
    return 0;
}