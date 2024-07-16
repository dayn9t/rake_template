#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// hec downloader CAPI

/// 对象句柄
typedef unsigned long long HenHandle;

/// 创建下载器
HenHandle hen_downloader_create(const char* src_url, const char* dst_file);

/// 创建下载器
void hen_downloader_destroy(HenHandle handle);

/// 下载器
size_t hen_downloader_transfer(HenHandle handle);

#ifdef __cplusplus
}
#endif
