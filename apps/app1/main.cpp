#include <iostream>
#include <fmt/format.h>
#include <hen/net/session.hpp>
#include <hen/net/playback.hpp>

using namespace hen;
using namespace std;


int main()
{
    NetSDK sdk;

    auto version = sdk.version();
    fmt::println("Version: {}", version_string(version));

    sdk.set_log(3, "/tmp/hen-app.log");

    Session session("10.1.0.21", 8000, "admin", "howell1409");
    auto d = session.device_info();
    fmt::println("Device serial: {}", d.serial_number);
    fmt::println("  disk number: {}", d.disk_num);

    const DatetimeMember start = {2024, 5, 16, 22, 0, 0};
    const DatetimeMember end = {2024, 5, 16, 22, 1, 0};
    const PlaybackInfo info = {1, 0, 1, start, end}; // stream 无影响
    Playback playback(session.id(), info);

    playback.start();

    std::cout << "按 ESC 结束..." << std::endl;

    for (auto key = 0; key != 17; key = std::cin.get())
    {
    }

    return 0;
}
