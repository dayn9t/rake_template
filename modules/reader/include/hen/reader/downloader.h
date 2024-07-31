#pragma once

#include <cr/cdd/error.h>


#ifdef __cplusplus
extern "C" {
#endif

// hec downloader CAPI

/// 下载器对象句柄
typedef struct HenDownloaderCS
{
    U64 ptr;
} HenDownloader;


/// 创建下载器
CrError hen_downloader_create(const char* src_url, const char* dst_file, HenDownloader* handle);

/// 创建下载器
CrError hen_downloader_destroy(HenDownloader handle);

/// 下载器
CrError hen_downloader_transfer(HenDownloader handle, U32* size);

#ifdef __cplusplus
}
#endif
