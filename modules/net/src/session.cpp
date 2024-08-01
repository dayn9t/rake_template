#include <iostream>
#include <hen/net/session.hpp>
#include "hik_util.hpp"
#include <string.h>

using namespace std;

namespace hen
{
    string version_string(uint32_t version)
    {
        uint32_t parts[] = {
            version >> 24 & 0xFF,
            version >> 16 & 0xFF,
            version >> 8 & 0xFF,
            version & 0xFF,
        };
        char buff[32] = {};
        sprintf( buff, "%d.%d.%d.%d", parts[0], parts[1], parts[2], parts[3]);
        return buff;
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


    /// 转换设备信息类型
    DeviceInfo to_hen(const NET_DVR_DEVICEINFO_V40& device_info)
    {
        auto& d = device_info.struDeviceV30;
        DeviceInfo info = {
            .serial_number = string((const char*)d.sSerialNumber),
            .start_channel = d.byStartDChan,
            .disk_number = d.byDiskNum,
            .main_proto = d.byMainProto,
            .sub_proto = d.bySubProto,
        };

        // FIXME: Hik数值含义不一致
        // - IPC, 通道号从1开始, start_digit_channel 返回 0
        // - NVR, start_digit_channel 返回返回有效值
        if( info.start_channel == 0) // IPC 或者 DVR
        {
            info.start_channel = 1; // IPC 通道号从1开始
        }
        return info;
    }


    NET_DVR_USER_LOGIN_INFO to_hik(const CrEndpoint& endpoint, const CrAuthInfo& auth)
    {
        NET_DVR_USER_LOGIN_INFO login_info = {};
        login_info.bUseAsynLogin = false;
        login_info.wPort = endpoint.port_number;
        strncpy(login_info.sDeviceAddress, endpoint.hostname, CR_HOSTNAME_MAX_LEN);
        strncpy(login_info.sUserName, auth.user, CR_USER_MAX_LEN);
        strncpy(login_info.sPassword, auth.password, CR_PASSWORD_MAX_LEN);
        return login_info;
    }


    Session::Session(const CrEndpoint& endpoint, const CrAuthInfo& auth)
    {
        auto version = m_sdk.version();
        cout << "    Version: " <<  version_string(version) << endl;
        m_sdk.set_log(3, "/tmp/hen-app.log");

        NET_DVR_USER_LOGIN_INFO login_info = to_hik(endpoint, auth);

        NET_DVR_DEVICEINFO_V40 device_info = {};
        m_session_id = NET_DVR_Login_V40(&login_info, &device_info);
        hik_ensure(m_session_id >= 0);

        m_device_info = to_hen(device_info);

        cout << "    Device serial: " <<  m_device_info.serial_number << endl;
        cout << "    Disk number: " <<  m_device_info.disk_number << endl;
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
