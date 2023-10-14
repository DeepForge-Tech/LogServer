#include "Server.hpp"

using namespace LogServer;

/**
 * The function creates a socket for a server to communicate with clients using UDP.
 */
void Server::CreateSocket()
{
    try
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        /* `memset(&servaddr, 0, sizeof(servaddr));` is a function that sets the memory of the `servaddr`
        structure to zero. It takes three arguments: the address of the structure (`&servaddr`), the
        value to set (0), and the size of the structure (`sizeof(servaddr)`). */
        memset(&servaddr, 0, sizeof(servaddr));
        /* The line `memset(&cliaddr, 0, sizeof(cliaddr));` is setting the memory of the `cliaddr`
        structure to zero. It takes three arguments: the address of the structure (`&cliaddr`), the
        value to set (0), and the size of the structure (`sizeof(cliaddr)`). This is commonly done to
        initialize a structure before using it to ensure that all its members are set to a known value. */
        memset(&cliaddr, 0, sizeof(cliaddr));
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
        throw runtime_error("❌ Error creating socket.");
    }
}

/**
 * The function sets the server information including the IP address and port number.
 */
void Server::SetInformation()
{
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("64.226.99.105");
    servaddr.sin_port = htons(PORT);
}

/**
 * The function "BindSocket" binds the socket to a specific address and port.
 */
void Server::BindSocket()
{
    try
    {
        bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
        throw runtime_error("❌ Error binding socket.");
    }
}
/**
 * The function takes a JSON object containing log information and inserts it into a database table.
 *
 * @param JSON_LOGS JSON_LOGS is a JSON object that contains log information. It has the following
 * properties:
 *
 * @return the value of the variable RESULT.
 */
int Server::JSON_to_DB(Json::Value JSON_LOGS)
{
    int RESULT = database.InsertLogInformationToTable("Logs", JSON_LOGS["Architecture"].asString(),
                                                      JSON_LOGS["OS_NAME"].asString(), JSON_LOGS["Channel"].asString(), JSON_LOGS["FunctionName"].asString(),
                                                      JSON_LOGS["LogText"].asString());
    return RESULT;
}

void Server::Start()
{
    CreateSocket();
    SetInformation();
    BindSocket();
    while (true)
    {
        len = sizeof(cliaddr); // len is value/result

        /* The line `n = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr
        *)&cliaddr, &len);` is receiving data from the socket `sockfd` and storing it in the buffer
        `buffer`. */
        n = recvfrom(sockfd, (char *)buffer, MAX_SIZE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        /* The line `buffer[n] = '\0';` is adding a null character (`'\0'`) at the end of the received
            data stored in the `buffer` array. This is done to ensure that the received data is treated
            as a null-terminated string, which is a requirement for many string manipulation functions
            in C++. */
        buffer[n] = '\0';
        try
        {
            if (buffer[0] == "{" && (end(buffer)-begin(buffer) - 1) == "}") cout << end(arr)-begin(arr) << endl;
            /* `Json::Value JSON_LOGS;` is declaring a variable named `JSON_LOGS` of type `Json::Value`.
            This variable is used to store a JSON object. */
            Json::Value JSON_LOGS;
            /* The line `Json::Reader reader;` is declaring a variable named `reader` of type
            `Json::Reader`. This variable is used to parse JSON data. The `Json::Reader` class provides
            functions to read and parse JSON data from a string or input stream. In this code, it is
            used to parse the data received from the socket into a `Json::Value` object named
            `JSON_LOGS`. */
            Json::Reader reader;
            /* The line `reader.parse(buffer, JSON_LOGS);` is parsing the data stored in the `buffer` array
            and storing it in the `JSON_LOGS` variable. */
            reader.parse(buffer, JSON_LOGS);
            /* The `JSON_to_DB(JSON_LOGS)` function takes a JSON object containing log information and
            inserts it into a database table. It calls the `InsertLogInformationToTable` function of the
            `database` object, passing the log information as parameters. The function returns the
            result of the database operation. */
            int RESULT = JSON_to_DB(JSON_LOGS);
        }
        catch (const std::exception &error)
        {
            std::cerr << error.what() << '\n';
            // throw
        }
        printf("Client: %s\n", buffer);
        /* The line `sendto(sockfd, (const char *)SUCCESS, strlen(SUCCESS), MSG_CONFIRM, (const struct
        sockaddr *)&cliaddr, len);` is sending a response message to the client. */
        if (RESULT == 0)
            sendto(sockfd, (const char *)SUCCESS, strlen(SUCCESS), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    }
}
// Driver code
int main()
{
    Server server;
    server.Start();
    return 0;
}