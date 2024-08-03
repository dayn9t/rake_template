#include <hen/ce/session.h>
#include <hen/cppw/session.hpp>
#include <cr/cdd_adt/str_adt.hpp>

using namespace hen;
using namespace std;
using namespace cr;


CrError hen_session_create(const CrEndpoint* endpoint, const CrAuthInfo* auth, HenSession* session)
{
    return catch_error([&]
    {
        auto ob = new Session(*endpoint, *auth);
        *session = cr_handle_cast(ob, HenSession);
    });
}

CrError hen_session_destroy(HenSession session)
{
    cr_destroy_fun_body(session, Session);
}

HenDeviceInfo cvt(const DeviceInfo& info)
{
    HenDeviceInfo d = {};
    StrX(d.serial_number) = info.serial_number;
    d.disk_number = info.disk_number;
    d.start_channel = info.start_channel;
    return d;
}

CrError hen_session_device_info(HenSession session, HenDeviceInfo* device_info)
{
    return catch_error([&]
    {
        auto ob = cr_object_cast(session, Session);
        *device_info = cvt(ob->device_info());
    });
}
