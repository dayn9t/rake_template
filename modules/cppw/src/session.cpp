#include <hen/cppw/session.hpp>

#include "hik_util.hpp"

#include <iostream>

#include <string.h>


using namespace std;

namespace hen
{



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
        cr_ensure(this);
        return NET_DVR_GetSDKBuildVersion();
    }

    void NetSDK::set_log(int level, std::string_view path)
    {
        cr_ensure(this);
        auto r = NET_DVR_SetLogToFile(level, const_cast<char*>(path.data()), false);
        hik_ensure(r);
    }



    Session::Session(const CrEndpoint& endpoint, const CrAuthInfo& auth)
    {
        auto version = m_sdk.version();
        cout << "    Version: " << version_string(version) << endl;
        m_sdk.set_log(3, "/tmp/hen-app.log");

        NET_DVR_USER_LOGIN_INFO login_info = to_hik(endpoint, auth);

        NET_DVR_DEVICEINFO_V40 device_info = {};
        m_session_id = NET_DVR_Login_V40(&login_info, &device_info);
        hik_ensure(m_session_id >= 0);

        m_device_info = to_hen(device_info);

        cout << "    Device serial: " << m_device_info.serial_number << endl;
        cout << "    Disk number: " << m_device_info.disk_number << endl;
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
