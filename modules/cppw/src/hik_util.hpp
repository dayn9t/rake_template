#pragma once

#include <hik/HCNetSDK.h>
#include <hen/cppw/types.hpp>

#include <cr/dbc.hpp>
#include <cr/cdd_adt.hpp>

/// 确保条件成功，否则抛出 CrError(code)
#define hik_ensure(cond) cr_ensure_or(cond, NET_DVR_GetLastError())

using namespace cr;

namespace hen
{
    /// 版本号转字符串
    string version_string(U32 version);

    /// 转换设备信息类型
    DeviceInfo to_hen(const NET_DVR_DEVICEINFO_V40& device_info);

    /// 转换为海康登录信息
    NET_DVR_USER_LOGIN_INFO to_hik(const CrEndpoint& endpoint, const CrAuthInfo& auth);


    /// 获取 HIK 包时间
    DatetimeMember time_of(const NET_DVR_PACKET_INFO_EX& p);


    /// 转换为海康视频片段信息
    NET_DVR_VOD_PARA to_hik(const MediaSegInfo& info, U32 start_channel);


    /// 转换为海康时间
    NET_DVR_TIME to_hik(const CrTimePoint& time_point);

    /// 海康时间转字符串
    string to_string(const NET_DVR_TIME& t);
}
