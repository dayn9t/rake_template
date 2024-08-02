#pragma once

#include "types.h"

#include <cr/cdd/error.h>
#include <cr/cdd/net.h>

#ifdef __cplusplus
extern "C" {
#endif

// session API

/// 会话句柄
typedef struct {
    U64 ptr;
} HenSession;


/// 创建会话
CrError hen_session_create(const CrEndpoint* endpoint, const CrAuthInfo* auth, HenSession* session);

/// 销毁会话
CrError hen_session_destroy(HenSession session);

/// 会话获取设备信息
CrError hen_session_device_info(HenSession session, HenDeviceInfo* device_info);

#ifdef __cplusplus
}
#endif
