#pragma once

#include "session.h"
#include <cr/cdd/time.h>

#ifdef __cplusplus
extern "C" {
#endif

// downloader API

/// 下载器句柄
typedef struct HenDownloaderCS
{
    U64 ptr;
} HenDownloader;

/// 媒体片段信息
typedef struct HenMediaSegInfoCS
{
    /// 通道号
    U32 channel;
    /// 码流类型： 0-主，1-子，2-三，3-延时摄影码流, IPC中获取录像时好像无效
    U32 stream;
    /// 媒体类型位集合：1bit-视频, 2bit-音频
    U32 media_type;
    /// 开始时间
    CrTimeRange time_range;
} HenMediaSegInfo;


/// 创建下载器
CrError hen_downloader_create(HenSession session, const HenMediaSegInfoCS* info, HenDownloader* handle);

/// 销毁下载器
CrError hen_downloader_destroy(HenDownloader handle);

/// 下载器传输
CrError hen_downloader_transfer(HenDownloader handle, U32* size);

#ifdef __cplusplus
}
#endif
