#include <hen/net/downloader.hpp>

#include <iostream>
#include <hen/reader/session.h>

using namespace hen;
using namespace std;


CrError hen_session_create(const CrEndpoint* endpoint, const CrAuthInfo* auth, HenSession* session)
{
    return cr::catch_error([&]
    {
        auto ob = new Session(*endpoint, *auth);
        /// TODO: 提取函数 device_info
        auto d = ob->device_info();
        cout << "    Device serial: " << d.serial_number << endl;
        cout << "    Disk number: " << d.disk_num << endl;
        *session = cr_handle_cast(ob, HenSession);
    });
}

CrError hen_session_destroy(HenSession session)
{
    cr_destroy_fun_body(session, Session);
}

HenDeviceInfo cvt(DeviceInfo info)
{
    HenDeviceInfo d = {};
    strcpy(d.serial_number, info.serial_number.c_str());
    d.disk_number = info.disk_number;
    d.start_channel = info.start_channel;
    return d;
}

CrError hen_session_device_info(HenSession session, HenDeviceInfo* device_info)
{
    return cr::catch_error([&]
    {
        auto ob = cr_object_cast(session, Session);
        *device_info = cvt(ob->device_info());
    });
}
