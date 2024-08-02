#pragma once
#include <mutex>
#include <hen/net/types.hpp>

#include <../../../../reader/include/hen/net_ce>

namespace hen
{

    class Session;

    class Playback
    {
    public:
        using OnAudio = std::function<void(DatetimeMember time, std::byte* buffer, size_t size)>;

    public:
        Playback(const Session& session, const MediaSegInfo& info);
        ~Playback();

    public:
        /// 获取文件总长度, 时间回放时有效, IPC好像无效
        [[nodiscard]]
        uint64_t total_len() const;

        /// 获取播放时长, 文件回放时有效
        [[nodiscard]]
        uint32_t time() const;
        /// 获取总时长, 文件回放时有效
        [[nodiscard]]
        uint32_t total_time() const;
        /// 获取倍速
        [[nodiscard]]
        int speed() const { return m_speed; };
        /// 设置倍速
        void set_speed(int speed);

    public:
        /// 开始播放
        void start();
        /// 停止播放
        void stop();
        /// 设置音频接收函数
        void set_audio_path(string_view path);
        /// 设置音频接收函数
        size_t audio_size() const;
        /// 检查传输是否结束
        bool done() const;
    public:
        void append_audio(DatetimeMember time, std::byte* buffer, size_t size);

    private:
        void close_audio();

        void control(unsigned code);
        [[nodiscard]]
        uint32_t get(unsigned code) const;

        [[nodiscard]]
        uint32_t get_u64(unsigned code, uint64_t& value) const;

    private:
        int m_handle = 0;
        int m_speed = 1;

        mutable std::mutex m_audio_mutex;
        FILE* m_audio_file = nullptr;
        size_t m_audio_total = 0;
        cr::TimePoint m_audio_update;
    };
}
