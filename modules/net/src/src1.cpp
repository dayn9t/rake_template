
#include <hen/net/header1.hpp>
#include <cr/dbc.hpp>

#include <hik/HCNetSDK.h>

namespace hen
{
    inline Network::Network()
    {
        auto r = NET_DVR_Init();
        cr_ensure(r == NET_DVR_NOERROR);
    }

    inline Network::~Network()
    {
        auto r = NET_DVR_Cleanup();
        cr_ensure(r == NET_DVR_NOERROR);
    }
}
