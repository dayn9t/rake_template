#pragma once
#include "playback.hpp"
#include "session.hpp"
#include <memory>
#include <boost/url.hpp>
#include <map>

namespace hen
{
    using Url = boost::url;


    /// 获取查询字符串参数
    std::map<string, string> get_params(const Url& url);

    /// 输出URI的各个组件
    void show_parts(const Url& url);


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
    RecordInfo parse_record_info(const Url& url);

    class Downloader
    {

    public:
        Downloader(string_view src_url, string_view dst_file);
        ~Downloader();

    public:
        /// 传输
        size_t transfer();

    private:
        NetSDK m_sdk;
        std::unique_ptr<Session> m_session;
        std::unique_ptr<Playback> m_playback;
    };
}
