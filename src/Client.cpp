#if defined(__linux__) || __APPLE__
#include "Client_UNIX.hpp"
using namespace UNIX;
#elif _WIN32
#include "Client_POSIX.hpp"
using namespace POSIX;
#endif
#include <filesystem>

int main()
{
    Client client;
    string ProjectDir = std::filesystem::current_path().generic_string();
    string JSON_STRING = R"({
        "Entries":
        [
        {
        "Architecture":"amd64",
        "Channel":" "stable\\latest",
        "OS_NAME":"Windows",
        "FunctionName":"Download",
        "LogText":"LogText",
        }
        ]
    })";
    client.SEND_JSON_ARRAY(JSON_STRING);
    return 0;
}