#include "hen/net/downloader.hpp"
#include <hen/reader/downloader.h>

using namespace hen;
using namespace std;


HenHandle hen_downloader_create(const char* src_url, const char* dst_file)
{
    auto p = new Downloader(src_url, dst_file);
    return HenHandle(p);
}


void hen_downloader_destroy(HenHandle handle)
{
    auto p = reinterpret_cast<Downloader*>(handle);
    delete p;
}


size_t hen_downloader_transfer(HenHandle handle)
{
    auto p = reinterpret_cast<Downloader*>(handle);
    return p->transfer();
}
