#include <hen/reader/downloader.h>
#include <cr/dbc.hpp>
#include <iostream>

using namespace std;

// "hikn://admin:howell1409@10.1.0.21:8000/record/101?start_time=2024-07-29T12:00:00&end_time=2024-07-29T12:10:00"

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage:\n\then-download <URL> <DST_FILE>\n" << endl;
        return 2;
    }

    const char* src_url = argv[1];
    const char* dst_file = argv[2];

    HenDownloader downloader{};

    auto r = hen_downloader_create(src_url, dst_file, &downloader);
    cr_ensure_ret(r);

    U32 size = 0;
    r = hen_downloader_transfer(downloader, &size);
    cr_ensure_ret(r);

    cout << "Download size: " << size << endl;;

    hen_downloader_destroy(downloader);

    cout << "Done" << endl;

    return 0;
}
