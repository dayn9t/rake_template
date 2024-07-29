#pragma once

#include <cr/dbc.hpp>
#include <hik/HCNetSDK.h>
#include <hen/net/types.hpp>

/// 确保条件成功，否则抛出 CrError(code)
#define hik_ensure(cond) cr_ensure_or(cond, NET_DVR_GetLastError())

namespace hen {

    inline NET_DVR_TIME to_hik(DatetimeMember &dt) {
        NET_DVR_TIME time = {};
        time.dwYear = dt.year;
        time.dwMonth = dt.month;
        time.dwDay = dt.day;
        time.dwHour = dt.hour;
        time.dwMinute = dt.minute;
        time.dwSecond = int(dt.second);
        return time;
    }
}
