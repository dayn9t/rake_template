#include <sstream>
#include <fmt/format.h>
#include <hen/net/downloader.hpp>
#include <iostream>

using namespace hen;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fmt::println("Usage:\n\then-download <URL> <DST_FILE>\n");
        return 2;
    }

    try
    {
        Downloader downloader(argv[1], argv[2]);
        auto size = downloader.transfer();
        std::cout << "    Download size: " << size << std::endl;
    }
    catch (CrError& e)
    {
        fmt::println("Error: {}", cr::to_string(e));
    }
    return 0;
}
