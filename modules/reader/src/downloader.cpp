#include "hen/net/downloader.hpp"

#include <iostream>
#include <hen/reader/downloader.h>

using namespace hen;
using namespace std;

CrError hen_downloader_create(HenSession session, const HenMediaSegInfoCS* media_seg_info, const char* dst_file, HenDownloader* handle)
{
    return cr::catch_error([&]
    {
        auto s = cr_object_cast(session, Session);
        auto ob = new Downloader(*s, *media_seg_info, dst_file);
        *handle = cr_handle_cast(ob, HenDownloader);
    });
}

CrError hen_downloader_destroy(HenDownloader handle)
{
    return cr::catch_error([&]{
        auto ob = cr_object_cast(handle, Downloader);
        delete ob;
    });
}

CrError hen_downloader_transfer(HenDownloader handle, U32* size)
{
    cr_destroy_fun_body(handle, Downloader);
}
