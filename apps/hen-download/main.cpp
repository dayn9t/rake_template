#include <map>
#include <sstream>
#include <thread>
#include <fmt/format.h>
#include <hen/net/session.hpp>
#include <hen/net/playback.hpp>

using namespace hen;
using namespace std;

#include <boost/url.hpp>
#include <iostream>
#include <string>

/// 获取查询字符串参数
map<string, string> get_params(const boost::url& url)
{
    map<string, string> query_map;

    for (auto p : url.params())
    {
        query_map[p.key] = p.value;
    }

    return query_map;
}

/// 录像片段信息
struct RecordInfo
{
    int channel;
    int stream;
    int media_type;
    DatetimeMember start;
    DatetimeMember end;
};


/// 解析录像记录
RecordInfo parse_record_info(const boost::url& url)
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


/// 输出URI的各个组件
void show_parts(const boost::url& url)
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

// "hikn://admin:howell1409@10.1.0.21:8000/record/101?start_time=2024-06-14T17:07:00&end_time=2024-06-14T17:09:00";

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fmt::println("Usage:\n\then-download <URL> <DST_FILE>\n");
        return 2;
    }
    boost::url url = boost::url(argv[1]);
    string dst_file = argv[2];
    show_parts(url);
    auto record_info = parse_record_info(url);

    NetSDK sdk;
    auto version = sdk.version();
    fmt::println("Version: {}", version_string(version));

    sdk.set_log(3, "/tmp/hen-app.log");

    Session session(url.host(), url.port_number(), url.user(), url.password());
    auto d = session.device_info();
    fmt::println("Device serial: {}", d.serial_number);
    fmt::println("  disk number: {}", d.disk_num);

    const PlaybackInfo info = {
        .channel = record_info.channel,
        .stream = record_info.stream, // stream 无影响
        .audio_type = 1,
        .start = record_info.start,
        .end = record_info.end,
    };
    Playback playback(session.id(), info);

    playback.set_audio_path(dst_file);
    playback.start();

    while (!playback.done())
    {
        std::this_thread::sleep_for(1s);
        auto len = playback.audio_size();
        fmt::println("Audio len: {}", len);
    }

    return 0;
}
