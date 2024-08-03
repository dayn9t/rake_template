#include <hen/cppw/playback.hpp>
#include <hen/cppw/session.hpp>

#include <cassert>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "hik_util.hpp"

using namespace std;

namespace hen
{
    using Lock = std::lock_guard<std::mutex>;
    /// 获取回放属性信息
    template <typename T>
    uint32_t play_back_get(int handle, unsigned code, T& value)
    {
        cout << "GET: {} ..." << code << endl;
        uint32_t value_len = 0;
        auto ok = NET_DVR_PlayBackControl_V40(handle, code, nullptr, 0, &value, &value_len);
        cr_ensure(!value_len || value_len == sizeof(T));
        //auto ok = NET_DVR_PlayBackControl_V40(handle, code);
        if (ok) return 0;

        auto e = NET_DVR_GetLastError();
        assert(e == 0);
        //NET_DVR_NETWORK_RECV_TIMEOUT

        return e;
    }

    /** 回放ES数据回调
    *
    *  不建议调用该SDK中接口.
    */
    void CALLBACK pay_es_callback(LONG play_handle, NET_DVR_PACKET_INFO_EX* pack_info, void* user_data)
    {
        auto playback = static_cast<Playback*>(user_data);

        static size_t count = 0;
        static size_t total = 0; // 2656551
        count++;

        auto& p = *pack_info;
        DatetimeMember time = time_of(p);

        //if (p.dwPacketType != 10) return;
        total += p.dwPacketSize;

        auto buffer = reinterpret_cast<std::byte*>(p.pPacketBuffer);
        auto size = static_cast<size_t>(p.dwPacketSize);

        if (p.dwPacketType == 10)
        {
            cr_ensure(size == 320);
            playback->append_audio(time, buffer, size);
        }
        else
        {
            /*
                        cout << "#{} {} {} rate:{} {}x{} flag:{} len:{}/{}",
                            count,
                            p.dwPacketType, // 0-文件头，1-I帧，2-B帧， 3-P帧， 10-音频包， 11-私有数据
                            to_string(time),
                            static_cast<int>(p.dwFrameRate),
                            p.wHeight, p.wWidth,
                            p.dwFlag,
                            p.dwPacketSize,
                            total
                        );*/
        }
    }

    Playback::Playback(const Session& session, const MediaSegInfo& info)
    {
        auto start_channel = session.device_info().start_channel;
        cout << "    Start_digit_channel: " << start_channel << endl;

        NET_DVR_VOD_PARA param = to_hik(info, start_channel);

        m_handle = NET_DVR_PlayBackByTime_V40(session.id(), &param);

        int channel = static_cast<int>(param.struIDInfo.dwChannel);
        int stream = static_cast<int>(param.byStreamType);
        printf("    Play: session=%d channel=%d stream=%d handle=%d\n", session.id(), channel, stream, m_handle);
        printf("    Time: %s - %s\n", to_string(param.struBeginTime).c_str(), to_string(param.struEndTime).c_str());
        hik_ensure(m_handle >= 0);
        auto r = NET_DVR_SetPlayBackESCallBack(m_handle, pay_es_callback, this);
        hik_ensure(r);
    }

    Playback::~Playback()
    {
        stop();
        close_audio();
    }

    uint64_t Playback::total_len() const
    {
        uint64_t len = 0;
        auto _r = play_back_get(m_handle, NET_DVR_PLAYGETTOTALLEN, len);
        return len;
    }

    uint32_t Playback::time() const
    {
        return get(NET_DVR_PLAYGETTIME);
    }

    uint32_t Playback::total_time() const
    {
        return get(NET_DVR_GETTOTALTIME);
    }


    void Playback::start()
    {
        cout << "    Playback::start ..." << endl;
        control(NET_DVR_PLAYSTART);

        // 初始化时间, 防止开始就超时
        Lock lock(m_audio_mutex);
        m_audio_update = cr::now();
    }

    void Playback::stop()
    {
        cr_ensure(this);
        cout << "    Playback::stop ..." << endl;
        //control(NET_DVR_PLAYSTOP); // 传输结束调用会出错
    }

    void Playback::set_speed(int speed)
    {
        speed = std::clamp(speed, 1, 16);
        if (speed > m_speed)
        {
            control(NET_DVR_PLAYFAST);
            m_speed *= 2;
        }

        if (speed < m_speed)
        {
            control(NET_DVR_PLAYSLOW);
            m_speed /= 2;
        }
    }


    void Playback::set_audio_path(string_view path)
    {
        Lock lock(m_audio_mutex);
        assert(!m_audio_file);
        m_audio_file = fopen(path.data(), "wb");
    }

    size_t Playback::audio_size() const
    {
        Lock lock(m_audio_mutex);
        return m_audio_total;
    }

    bool Playback::done() const
    {
        Lock lock(m_audio_mutex);

        auto d = cr::now() - m_audio_update;
        return d > Seconds(DATA_MAX_INTERVAL);
    }

    // 使用该这个时间
    void Playback::append_audio(DatetimeMember time, std::byte* buffer, size_t size)
    {
        Lock lock(m_audio_mutex);
        if (m_audio_file)
        {
            fwrite(buffer, size, 1, m_audio_file);
            m_audio_total += size;
            m_audio_update = cr::now();
            //cout << "A {} len:{}/{}", to_string(time), size, m_audio_total);
        }
    }

    void Playback::close_audio()
    {
        Lock lock(m_audio_mutex);
        if (m_audio_file)
        {
            fclose(m_audio_file);
            m_audio_file = nullptr;
        }
    }

    void Playback::control(unsigned code)
    {
        //NET_DVR_PlayBackControl_V40
        auto ok = NET_DVR_PlayBackControl(m_handle, code, 0, nullptr);
        hik_ensure(ok);
    }

    uint32_t Playback::get(unsigned code) const
    {
        uint32_t out = 0;
        cout << "    GET: {} ..." << code << endl;
        auto ok = NET_DVR_PlayBackControl(m_handle, code, 0, &out);
        if (!ok)
        {
            auto e = NET_DVR_GetLastError();
            assert(e == 0);
            //NET_DVR_NETWORK_RECV_TIMEOUT
        }
        //hik_ensure(r);
        return out;
    }

    uint32_t Playback::get_u64(unsigned code, uint64_t& value) const
    {
        uint32_t out = 0;
        cout << "    GET: {} ..." << code << endl;
        auto ok = NET_DVR_PlayBackControl(m_handle, code, 0, &out);
        if (!ok)
        {
            auto e = NET_DVR_GetLastError();
            assert(e == 0);
            //NET_DVR_NETWORK_RECV_TIMEOUT
        }
        //hik_ensure(r);
        return out;
    }


    int find_file(int lUserID)
    {
        cr_ensure(lUserID >= 0);

        //find file
        //  NET_DVR_TIME struStartTime, struStopTime;
        // struStartTime.dwYear	= 2010;
        //     struStartTime.dwMonth	= 6;
        //  struStartTime.dwDay		= 1;
        //  struStartTime.dwHour	= 0;
        //struStartTime.dwMinute	= 0;
        // struStartTime.dwSecond	=0;

        // struStopTime.dwYear		= 2010;
        // struStopTime.dwMonth	= 6;
        // struStopTime.dwDay		= 1;
        // struStopTime.dwHour		= 1;
        // struStopTime.dwMinute	= 0;
        // struStopTime.dwSecond	= 0;

        //int lFindHandle = NET_DVR_FindFile(lUserID, 1, 0xff, &struStartTime, &struStopTime);

        NET_DVR_FILECOND_V50 m_struFileCondV50 = {};

        m_struFileCondV50.struStreamID.dwChannel = 1;
        m_struFileCondV50.dwFileType = 0xff;
        m_struFileCondV50.dwFileType = 255;
        m_struFileCondV50.struStartTime.wYear = 2024;
        m_struFileCondV50.struStartTime.byMonth = 5;
        m_struFileCondV50.struStartTime.byDay = 16;
        m_struFileCondV50.struStartTime.byHour = 0;
        m_struFileCondV50.struStartTime.byMinute = 0;
        m_struFileCondV50.struStartTime.bySecond = 0;
        m_struFileCondV50.struStopTime.wYear = 2018;
        m_struFileCondV50.struStopTime.byMonth = 10;
        m_struFileCondV50.struStopTime.byDay = 22;
        m_struFileCondV50.struStopTime.byHour = 23;
        m_struFileCondV50.struStopTime.byMinute = 59;
        m_struFileCondV50.struStopTime.bySecond = 59;
        int lFindHandle = NET_DVR_FindFile_V50(lUserID, &m_struFileCondV50);

        if (lFindHandle < 0)
        {
            printf("find file fail,last error %d\n", NET_DVR_GetLastError());
            return 1;
        }
        NET_DVR_FINDDATA_V50 struFileData;

        while (true)
        {
            printf("NET_DVR_FindNextFile_V50\n");
            int result = NET_DVR_FindNextFile_V50(lFindHandle, &struFileData);
            if (result == NET_DVR_ISFINDING)
            {
                //nsleep(0, 20000000L); // sleep for 2/100 second;  printf("pyd---NET_DVR_RealPlay_V40  error, %d\n", NET_DVR_GetLastError());
                continue;
            }
            else if (result == NET_DVR_FILE_SUCCESS)
            {
                //char strFileName[256] = {0};
                //sprintf(strFileName, "./%s", struFileData.sFileName);
                printf("%s, %d, %d, %d-----%d,%d,%d.\n", struFileData.sFileName,
                       struFileData.struStartTime.wYear, struFileData.struStartTime.byMonth,
                       struFileData.struStartTime.byDay,
                       struFileData.struStopTime.wYear, struFileData.struStopTime.byMonth,
                       struFileData.struStopTime.byDay);
                //saveFile(lUserID, struFileData.sFileName,  strFileName);
                break;
            }
            else if (result == NET_DVR_FILE_NOFIND || result == NET_DVR_NOMOREFILE)
            {
                break;
            }
            else
            {
                printf("find file fail for illegal get file state\n");
                break;
            }
        }

        NET_DVR_FindClose_V30(lFindHandle);
        return 0;
    }
}
