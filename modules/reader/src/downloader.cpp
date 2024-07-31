#include "hen/net/downloader.hpp"

#include <iostream>
#include <hen/reader/downloader.h>

using namespace hen;
using namespace std;


CrError hen_downloader_create(const char* src_url, const char* dst_file, HenDownloader* handle)
{
    return cr::catch_error([&]
    {
        auto ob = new Downloader(src_url, dst_file);
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
