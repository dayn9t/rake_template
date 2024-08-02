#include <hen/cppw/types.hpp>
#include "hik_util.hpp"
#include <boost/url.hpp>
#include <iostream>
#include <thread>

using namespace std;

namespace hen
{
    /// 字符串解析成时间
    CrTimePoint parse_time(string_view str)
    {
        TimePoint t = {};
        cr_ensure(parse_local_datetime(str, t));
        return to_c(t);
    }


    MediaSegInfo parse_record_info(string_view path, StrMap& queries)
    {
        int n = 0;
        cr_ensure(sscanf(path.data(), "/record/%d", &n) == 1);

        MediaSegInfo info = {};
        info.channel = n / 100;
        info.stream = n % 100;
        info.time_range.start = parse_time(queries["start_time"]);
        info.time_range.end = parse_time(queries["end_time"]);

        return info;
    }
}
