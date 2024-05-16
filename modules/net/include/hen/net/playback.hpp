#pragma once

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
        DatetimeMember begin;
        /// 结束时间
        DatetimeMember end;
    };


    class Playback
    {
    public:
        Playback(int session, PlaybackInfo info);
        ~Playback();

    public:
        /// 开始播放
        void start();
        /// 停止播放
        void stop();
        /// 获取倍速
        [[nodiscard]]
        int speed() const { return m_speed; };
        /// 设置倍速
        void set_speed(int speed);

    private:
        void control(unsigned code);

    private:
        int m_handle = 0;
        int m_speed = 1;
    };

}
