#include <hen/net/downloader.hpp>
#include "hik_util.hpp"
#include <boost/url.hpp>
#include <memory>
#include <iostream>
#include <thread>

using namespace std;

namespace hen
{

    /// 字符串解析成时间
    CrTimePoint parse_time(InString str)
    {
        TimePoint t = {};
        cr_ensure(parse_local_datetime(str, t));
        return to_c(t);
    }


    MediaSegInfo parse_record_info(InString path, StrMap& queries)
    {
        int n = 0;
        cr_ensure(sscanf(path.c_str(), "/record/%d", &n) == 1);

        MediaSegInfo info = {};
        info.channel = n / 100;
        info.stream = n % 100;
        info.time_range.start = parse_time(queries["start_time"]);
        info.time_range.end = parse_time(queries["end_time"]);

        return info;
    }


    Downloader::Downloader(const Session& session, const MediaSegInfo& media_seg_info, string_view dst_file):
        m_playback(session, media_seg_info)
    {
        m_playback.set_audio_path(dst_file);
    }

    Downloader::~Downloader() = default;

    size_t Downloader::transfer()
    {
        m_playback.start();

        size_t audio_size = 0;
        while (!m_playback.done())
        {
            this_thread::sleep_for(1s);
            audio_size = m_playback.audio_size();
            cout << "    Audio len: " <<  audio_size << endl;
        }
        return audio_size;
    }
}
