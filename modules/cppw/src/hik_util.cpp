#include "hik_util.hpp"

namespace hen
{
    string version_string(U32 version)
    {
        const U32 parts[] = {
            version >> 24 & 0xFF,
            version >> 16 & 0xFF,
            version >> 8 & 0xFF,
            version & 0xFF,
        };
        char buff[32] = {};
        sprintf(buff, "%d.%d.%d.%d", parts[0], parts[1], parts[2], parts[3]);
        return buff;
    }

    DeviceInfo to_hen(const NET_DVR_DEVICEINFO_V40& device_info)
    {
        auto& d = device_info.struDeviceV30;
        DeviceInfo info = {
            .serial_number = string((const char*)d.sSerialNumber),
            .start_channel = d.byStartDChan,
            .disk_number = d.byDiskNum,
            .main_proto = d.byMainProto,
            .sub_proto = d.bySubProto,
        };

        // FIXME: Hik数值含义不一致
        // - IPC, 通道号从1开始, start_digit_channel 返回 0
        // - NVR, start_digit_channel 返回返回有效值
        if (info.start_channel == 0) // IPC 或者 DVR
        {
            info.start_channel = 1; // IPC 通道号从1开始
        }
        return info;
    }

    NET_DVR_USER_LOGIN_INFO to_hik(const CrEndpoint& endpoint, const CrAuthInfo& auth)
    {
        NET_DVR_USER_LOGIN_INFO login_info = {};
        login_info.bUseAsynLogin = false;
        login_info.wPort = endpoint.port;
        StrX(login_info.sDeviceAddress) = endpoint.host;
        StrX(login_info.sUserName) = auth.user;
        StrX(login_info.sPassword) = auth.password;
        return login_info;
    }

    DatetimeMember time_of(const NET_DVR_PACKET_INFO_EX& p)
    {
        DatetimeMember time = {
            static_cast<int>(p.dwYear),
            static_cast<int>(p.dwMonth),
            static_cast<int>(p.dwDay),
            static_cast<int>(p.dwHour),
            static_cast<int>(p.dwMinute),
            p.dwSecond + p.dwMillisecond / 1000.0,
            0
        };
        return time;
    }

    NET_DVR_VOD_PARA to_hik(const MediaSegInfo& info, U32 start_channel)
    {
        const auto audio = (info.media_type & 2) ? 1 : 0;

        NET_DVR_VOD_PARA param = {};
        param.struBeginTime = to_hik(info.time_range.start);
        param.struEndTime = to_hik(info.time_range.end);
        param.struIDInfo.dwChannel = info.channel + start_channel - 1;
        param.byStreamType = info.stream - 1; // FIXME: IPC中无影响
        param.byAudioFile = audio; // FIXME: IPC中无影响, 据说: 0-不回放音频文件，1-回放音频文件，需设备支持，启动音频回放后只回放音频文件

        return param;
    }

    NET_DVR_TIME to_hik(const CrTimePoint& time_point)
    {
        TimePoint t = get_time_point(time_point);
        auto dt = local_member(t);

        NET_DVR_TIME time = {};
        time.dwYear = dt.year;
        time.dwMonth = dt.month;
        time.dwDay = dt.day;
        time.dwHour = dt.hour;
        time.dwMinute = dt.minute;
        time.dwSecond = int(dt.second);
        return time;
    }

    string to_string(const NET_DVR_TIME& t)
    {
        char buffer[64];
        sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", t.dwYear, t.dwMonth, t.dwDay, t.dwHour, t.dwMinute,
                t.dwSecond);
        return buffer;
    }
}
