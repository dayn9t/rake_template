#include <hen/net/session.hpp>
#include <fmt/core.h>
#include "hik_util.hpp"

namespace hen
{
    string version_string(uint32_t version)
    {
        auto b = reinterpret_cast<std::byte*>(&version);
        return fmt::format("{}.{}.{}.{}", b[3], b[2], b[1], b[0]);
    }

    NetSDK::NetSDK()
    {
        auto r = NET_DVR_Init();
        hik_ensure(r);
    }

    NetSDK::~NetSDK()
    {
        auto r = NET_DVR_Cleanup();
        hik_ensure(r);
    }

    uint32_t NetSDK::version() const
    {
        return NET_DVR_GetSDKBuildVersion();
    }

    void NetSDK::set_log(int level, std::string_view path)
    {
        auto r = NET_DVR_SetLogToFile(level, const_cast<char*>(path.data()), false);
        hik_ensure(r);
    }


    Session::Session(string_view host, int port, string_view user, string_view password)
    {
        NET_DVR_USER_LOGIN_INFO login_info = {};
        NET_DVR_DEVICEINFO_V40 device_info = {};
        login_info.bUseAsynLogin = false;
        login_info.wPort = port;
        strncpy(login_info.sDeviceAddress, host.data(), NET_DVR_DEV_ADDRESS_MAX_LEN);
        strncpy(login_info.sUserName, user.data(), NAME_LEN);
        strncpy(login_info.sPassword, password.data(), NAME_LEN);

        m_session_id = NET_DVR_Login_V40(&login_info, &device_info);
        hik_ensure(m_session_id >= 0);

        auto& d = device_info.struDeviceV30;
        m_device_info.serial_number = string((const char*)d.sSerialNumber);
        m_device_info.disk_num = d.byDiskNum;
        m_device_info.main_proto = d.byMainProto;
        m_device_info.sub_proto = d.bySubProto;
    }

    Session::~Session()
    {
        auto r = NET_DVR_Logout(m_session_id);
        hik_ensure(r);
    }

    DeviceInfo Session::device_info() const
    {
        return m_device_info;
    }
}
