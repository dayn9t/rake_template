#pragma once

#include <hen/net/types.hpp>


namespace hen
{
    /// 版本转字符串
    string version_string(uint32_t version);

    /// 网络SDK环境
    class NetSDK
    {
    public :
        NetSDK();
        ~NetSDK();

    public:
        [[nodiscard]] uint32_t version() const;

        void set_log(int level, string_view path);
    };


    /// 会话
    class Session
    {
    public:
        Session(string_view host, int port, string_view user, string_view password);
        ~Session();

    public:
        /// 获取设备信息
        [[nodiscard]]
        DeviceInfo device_info() const;

        /// 获取ID
        [[nodiscard]]
        int id() const { return m_session_id; }

        /// 获取起始数字通道号
        [[nodiscard]]
        int start_digit_channel() const;

    public:
    private:
        int m_session_id = 0;
        DeviceInfo m_device_info = {};
    };
}
