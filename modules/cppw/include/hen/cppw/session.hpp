#pragma once

#include <cr/cdd/net.h>

#include "types.hpp"

namespace hen
{
    /// 版本转字符串
    string version_string(U32 version);

    /// 网络SDK环境
    class NetSDK
    {
    public :
        NetSDK();
        ~NetSDK();

    public:
        [[nodiscard]] U32 version() const;

        void set_log(int level, string_view path);
    };


    /// 会话
    class Session
    {
    public:
        Session(const CrEndpoint& endpoint, const CrAuthInfo& auth);
        ~Session();

    public:
        /// 获取设备信息
        [[nodiscard]]
        DeviceInfo device_info() const;

        /// 获取ID
        [[nodiscard]]
        int id() const { return m_session_id; }

        ///

    public:
    private:
        NetSDK m_sdk;
        int m_session_id = 0;
        DeviceInfo m_device_info = {};
    };
}
