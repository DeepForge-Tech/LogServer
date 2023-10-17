#if defined(__linux__) || __APPLE__
#include "Client_UNIX.hpp"
using namespace UNIX;
#elif _WIN32
#include "Client_POSIX.hpp"
using namespace POSIX;
#endif

int main()
{
    Client client;
    // char *data = client.OpenJSON("./toJSON.json");
    client.SendJSON("./toJSON.json");
    return 0;
}