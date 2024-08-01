#pragma once

/// 引入核心类型, 常用于本模块头文件中

#include <string>
#include <cr/cdd/time.h>
#include <cr/system/time.hpp>
#include <hen/reader/types.h>

namespace hen {
    using std::string;
    using std::string_view;

    using cr::DatetimeMember;

    using MediaSegInfo = HenMediaSegInfo;

    /// 设备信息
    struct DeviceInfo
    {
        /// 序列号
        string serial_number;
        /// 起始通道号，1-IPC从1开始; N-DVR从一个较大的值开始
        U32 start_channel;

        /// 模拟报警输入个数
        int alarm_in_port_num;
        /// 模拟报警输出个数
        int alarm_out_port_num;
        ///硬盘个数
        int disk_number;
        /// 设备类型，详见下文列表
        int dvr_type;
        /// 设备模拟通道个数，数字（IP）通道最大个数为byIPChanNum + byHighDChanNum*256
        int chan_num;
        /// 模拟通道的起始通道号，从1开始。数字通道的起始通道号见下面参数byStartDChan
        int start_chan;
        /// 设备语音对讲通道数
        int audio_chan_num;
        /// 设备最大数字通道个数，低8位，高8位见byHighDChanNum。可以根据IP通道个数来判断是否调用NET_DVR_GetDVRConfig（配置命令NET_DVR_GET_IPPARACFG_V40）获取模拟和数字通道相关参数（NET_DVR_IPPARACFG_V40）。
        int ip_chan_num;
        /// 零通道编码个数
        int zero_chan_num;
        /// 主码流传输协议类型：0- private，1- rtsp，2- 同时支持私有协议和rtsp协议取流（默认采用私有协议取流）
        int main_proto;
        /// 子码流传输协议类型：0- private，1- rtsp，2- 同时支持私有协议和rtsp协议取流（默认采用私有协议取流）
        int sub_proto;


    };
}