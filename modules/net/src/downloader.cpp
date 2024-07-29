#include <hen/net/downloader.hpp>
#include "hik_util.hpp"
#include <boost/url.hpp>
#include <memory>
#include <iostream>
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
        info.stream = n % 100 - 1; // URL中从1开始, 内部从0开始
        cr_ensure(parse(params["start_time"], info.start));
        cr_ensure(parse(params["end_time"], info.end));

        return info;
    }


    void show_parts(const Url& url)
    {
        cout << "    Scheme: " <<  url.scheme() << endl;
        cout << "    User: " <<  url.user() << endl;
        cout << "    Password: " <<  url.password() << endl;
        cout << "    Host: " <<  url.host() << endl;
        cout << "    Port: " <<  url.port() << endl;
        cout << "    Path: " <<  url.path() << endl;
        cout << "    Query: " <<  url.query() << endl;
        //cout << "Params: " <<  url.params() << endl;
        //cout << "Fragment: " <<  url.fragment() << endl;
    }


    Downloader::Downloader(const string_view src_url, const string_view dst_file)
    {
        Url url = Url(src_url);
        show_parts(url);
        auto record_info = parse_record_info(url);

        auto version = m_sdk.version();
        cout << "    Version: " <<  version_string(version) << endl;
        m_sdk.set_log(3, "/tmp/hen-app.log");

        m_session = std::make_unique<Session>(url.host(), url.port_number(), url.user(), url.password());
        auto d = m_session->device_info();
        cout << "    Device serial: " <<  d.serial_number << endl;
        cout << "    Disk number: " <<  d.disk_num << endl;

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
            cout << "    Audio len: " <<  audio_size << endl;
        }
        return audio_size;
    }
}
