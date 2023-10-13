#include "Client.hpp"

using namespace LogClient;

int main()
{
    Client client;
    // char *data = client.OpenJSON("./toJSON.json");
    client.SendJSON("./toJSON.json");
    return 0;
}