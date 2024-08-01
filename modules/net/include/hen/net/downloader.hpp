#pragma once
#include "playback.hpp"
#include "session.hpp"
#include <cr/cdd_adt.hpp>

namespace hen
{
    /// 解析录像记录
    MediaSegInfo parse_record_info(cr::InString path, cr::StrMap& queries);

    class Downloader
    {
    public:
        Downloader(const Session& session, const MediaSegInfo& media_seg_info, string_view dst_file);
        ~Downloader();

    public:
        /// 传输
        size_t transfer();

    private:
        Playback m_playback;
    };
}
