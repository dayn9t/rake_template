#include <hen/net/downloader.hpp>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cr/cdd_adt.hpp>

using namespace hen;
using namespace std;
using namespace cr;

//hikn://admin:howell1409@10.1.0.21:8000/record/101?start_time=2024-08-01T19:40:00&end_time=2024-08-01T19:50:00 audio.raw
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage:\n\then-download <URL> <DST_FILE>\n" << endl;
        return 2;
    }

    try
    {
        auto src_url = argv[1];
        auto dst_file = argv[2];

        CrEndpoint endpoint = {};
        CrAuthInfo auth = {};
        string path;
        StrMap queries;
        cr_ensure(parse_url(src_url, endpoint, auth, path, queries));

        Session session(endpoint, auth);
        DeviceInfo device_info = session.device_info();

        MediaSegInfo media_seg_info = parse_record_info(path, queries);

        Downloader downloader(session, media_seg_info, dst_file);
        auto size = downloader.transfer();
        cout << "    Download size: " << size << std::endl;
    }
    catch (CrError& e)
    {
        cout << "Error: " << cr::to_string(e) << endl;
    }
    return 0;
}
