#include <hen/net/downloader.hpp>
#include <fmt/core.h>
#include "hik_util.hpp"
#include <boost/url.hpp>
#include <memory>
#include <thread>

using namespace std;

namespace hen
{
    map<string, string> get_params(const Url& url)
    {
        map<string, string> query_map;

        for (auto p : url.params())
        {
            query_map[p.key] = p.value;
        }

        return query_map;
    }


    RecordInfo parse_record_info(const Url& url)
    {
        int n = 0;
        cr_ensure(sscanf(url.path().c_str(), "/record/%d", &n) == 1);
        auto params = get_params(url);

        RecordInfo info = {};

        info.channel = n / 100;
        info.stream = n % 100;
        cr_ensure(parse(params["start_time"], info.start));
        cr_ensure(parse(params["end_time"], info.end));

        return info;
    }


    void show_parts(const Url& url)
    {
        fmt::println("Scheme: {}", url.scheme());
        fmt::println("User: {}", url.user());
        fmt::println("Password: {}", url.password());
        fmt::println("Host: {}", url.host());
        fmt::println("Port: {}", url.port());
        fmt::println("Path: {}", url.path());
        fmt::println("Query: {}", url.query());
        //fmt::println("Params: {}", url.params());
        fmt::println("Fragment: {}", url.fragment());
    }


    Downloader::Downloader(const string_view src_url, const string_view dst_file)
    {
        Url url = Url(src_url);
        show_parts(url);
        auto record_info = parse_record_info(url);

        auto version = m_sdk.version();
        fmt::println("Version: {}", version_string(version));
        m_sdk.set_log(3, "/tmp/hen-app.log");

        m_session = std::make_unique<Session>(url.host(), url.port_number(), url.user(), url.password());
        auto d = m_session->device_info();
        fmt::println("Device serial: {}", d.serial_number);
        fmt::println("  disk number: {}", d.disk_num);

        const PlaybackInfo info = {
            .channel = record_info.channel,
            .stream = record_info.stream, // stream 无影响
            .audio_type = 1,
            .start = record_info.start,
            .end = record_info.end,
        };
        m_playback = std::make_unique<Playback>(*m_session, info);
        m_playback->set_audio_path(dst_file);
    }

    Downloader::~Downloader() = default;

    size_t Downloader::transfer()
    {
        m_playback->start();

        size_t audio_size = 0;
        while (!m_playback->done())
        {
            this_thread::sleep_for(1s);
            audio_size = m_playback->audio_size();
            fmt::println("Audio len: {}", audio_size);
        }
        return audio_size;
    }
}
