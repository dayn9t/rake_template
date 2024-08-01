#include <hen/reader/downloader.h>
#include <cr/dbc.hpp>
#include <iostream>
#include <cr/cdd_adt.hpp>

#include <hen/net/downloader.hpp>

using namespace std;
using namespace cr;
using namespace hen;

// "hikn://admin:howell1409@10.1.0.21:8000/record/101?start_time=2024-07-29T12:00:00&end_time=2024-07-29T12:10:00"

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage:\n\then-download <URL> <DST_FILE>\n" << endl;
        return 2;
    }

    auto src_url = argv[1];
    auto dst_file = argv[2];

    CrEndpoint endpoint = {};
    CrAuthInfo auth = {};
    string path;
    StrMap queries;
    cr_ensure(parse_url(src_url, endpoint, auth, path, queries));

    HenSession session{};
    auto r = hen_session_create(&endpoint, &auth, &session);
    cr_ensure_ret(r);

    HenDeviceInfo device_info{};
    r = hen_session_device_info(session, &device_info);
    cr_ensure_ret(r);


    MediaSegInfo media_seg_info = parse_record_info(path, queries);

    HenDownloader downloader{};
    r = hen_downloader_create(session, &media_seg_info, dst_file, &downloader);
    cr_ensure_ret(r);

    U32 size = 0;
    r = hen_downloader_transfer(downloader, &size);
    cr_ensure_ret(r);

    cout << "Download size: " << size << endl;;

    r = hen_downloader_destroy(downloader);
    cr_ensure_ret(r);

    cout << "Done" << endl;

    return 0;
}
