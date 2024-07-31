#include "hen/net/downloader.hpp"
#include <hen/reader/downloader.h>

using namespace hen;
using namespace std;


CrError hen_downloader_create(const char* src_url, const char* dst_file, HenDownloader* handle)
{
    auto ob = new Downloader(src_url, dst_file);
    *handle = cr_handle_cast(ob, HenDownloader);
    return CRE_OK;
}

CrError hen_downloader_destroy(HenDownloader handle)
{
    auto ob = cr_object_cast(handle, Downloader);
    delete ob;
    return CRE_OK;
}

CrError hen_downloader_transfer(HenDownloader handle, U32* size)
{
    auto ob = cr_object_cast(handle, Downloader);
    *size = U32(ob->transfer());
    return CRE_OK;
}
