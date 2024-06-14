#pragma once
#include <mutex>
#include <hen/net/types.hpp>

namespace hen
{
    struct PlaybackInfo
    {
        /// 通道号
        int channel;
        /// 码流类型： 0-主，1-子，2-三，3-延时摄影码流, IPC中获取录像时好像无效
        int stream;
        /// 音频回放类型：0-不回放音频文件，1-只回放音频，该功能需要设备支持
        int audio_type;
        /// 开始时间
        DatetimeMember start;
        /// 结束时间
        DatetimeMember end;
    };


    class Playback
    {
    public:
        using OnAudio = std::function<void(DatetimeMember time, std::byte* buffer, size_t size)>;

    public:
        Playback(int session, PlaybackInfo info);
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
