#pragma once

#include <cr/cdd/error.h>
#include <cr/cdd/net.h>

#ifdef __cplusplus
extern "C" {
#endif

// session API

/// 会话句柄
typedef struct HenSessionCS
{
    U64 ptr;
} HenSession;

    /// 主机名最大长度
#define CR_SN_MAX_LEN 124

/// 设备信息
typedef struct HenDeviceInfoCS
{
    /// 设备序列号
    char serial_number[32];
    /// 设备磁盘数量
    U32 disk_number;
    /// 起始通道号，1-IPC从1开始; N-DVR从一个较大的值开始
    U32 start_channel;
} HenDeviceInfo;


/// 创建会话
CrError hen_session_create(const CrEndpoint* endpoint, const CrAuthInfo* auth, HenSession* session);

/// 销毁会话
CrError hen_session_destroy(HenSession session);

/// 会话获取设备信息
CrError hen_session_device_info(HenSession session, HenDeviceInfo* device_info);

#ifdef __cplusplus
}
#endif
