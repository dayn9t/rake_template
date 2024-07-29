#include <hen/net/downloader.hpp>
#include <sstream>
#include <iostream>
#include <stdio.h>


using namespace hen;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage:\n\then-download <URL> <DST_FILE>\n" << endl;
        return 2;
    }

    try
    {
        Downloader downloader(argv[1], argv[2]);
        auto size = downloader.transfer();
        cout << "    Download size: " << size << std::endl;
    }
    catch (CrError& e)
    {
        cout << "Error: " << cr::to_string(e) << endl;
    }
    return 0;
}
