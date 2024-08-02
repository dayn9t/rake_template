#pragma once

#include "session.h"

#ifdef __cplusplus
extern "C" {
#endif

// downloader API

/// 下载器句柄
typedef struct {
    U64 ptr;
} HenDownloader;

/// 创建下载器
CrError hen_downloader_create(HenSession session, const HenMediaSegInfo* media_seg_info, const char* dst_file, HenDownloader* handle);

/// 销毁下载器
CrError hen_downloader_destroy(HenDownloader handle);

/// 下载器传输
CrError hen_downloader_transfer(HenDownloader handle, U32* size);

#ifdef __cplusplus
}
#endif
