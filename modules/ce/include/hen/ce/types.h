#pragma once

#include <cr/cdd/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/// 设备信息
typedef struct
{
    /// 设备序列号
    char serial_number[24];
    /// 设备磁盘数量
    U32 disk_number;
    /// 起始通道号，1-IPC从1开始; N-DVR从一个较大的值开始
    U32 start_channel;
} HenDeviceInfo;


/// 媒体片段信息
typedef struct
{
    /// 通道号, 从 1 开始
    U32 channel;
    /// 码流类型： 1-主，2-子，3-三，4-延时摄影码流, IPC中获取录像时好像无效
    U32 stream;
    /// 媒体类型位集合：1bit-视频, 2bit-音频
    U32 media_type;
    /// 时间范围
    CrTimeRange time_range;
} HenMediaSegInfo;


#ifdef __cplusplus
}
#endif
