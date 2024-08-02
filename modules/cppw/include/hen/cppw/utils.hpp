#pragma once

#include <cr/cdd/time.h>
#include <cr/cdd_adt.hpp>
#include "basic.hpp"

namespace hen {

    /// 字符串解析成时间
    CrTimePoint parse_time(string_view str);

    /// 解析录像记录
    MediaSegInfo parse_record_info(string_view path, cr::StrMap& queries);
}