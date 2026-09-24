#include <cstddef> // The NDI headers require NULL to be defined.
#include <Processing.NDI.Lib.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string_view>

// The finder remains alive while its selected source is used by the receiver.
int probe(const NDIlib_source_t& source)
{
    NDIlib_recv_create_v3_t settings;
    settings.source_to_connect_to = source;
    settings.color_format = NDIlib_recv_color_format_fastest;
    const auto receiver = NDIlib_recv_create_v3(&settings);
    if (!receiver) {
        std::cerr << "Failed to create the NDI receiver.\n";
        return 1;
    }

    std::cout << "Probing source: " << source.p_ndi_name << '\n'
              << "NDI runtime: " << NDIlib_version() << std::endl;
    int result = 1;
    bool finished = false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    // Both the deadline and call limit bound the wait, including status changes.
    for (int attempt = 0; attempt < 100; ++attempt) {
        const auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(
            deadline - std::chrono::steady_clock::now()).count();
        if (remaining <= 0) {
            break;
        }
        NDIlib_video_frame_v2_t frame;
        const auto type = NDIlib_recv_capture_v3(receiver, &frame, nullptr, nullptr,
            static_cast<std::uint32_t>(std::min<std::int64_t>(remaining, 250)));
        if (type == NDIlib_frame_type_video) {
            const bool valid = frame.p_data && frame.xres > 0 && frame.yres > 0
                && frame.frame_rate_N > 0 && frame.frame_rate_D > 0;
            if (valid) {
                const auto code = static_cast<std::uint32_t>(frame.FourCC);
                char fourcc[5] = {};
                for (int i = 0; i < 4; ++i) {
                    const auto c = (code >> (8 * i)) & 0xff;
                    fourcc[i] = c >= 32 && c <= 126 ? static_cast<char>(c) : '?';
                }
                std::cout << "Received one video frame\n"
                          << "Source: " << source.p_ndi_name << '\n'
                          << "Width: " << frame.xres << '\n'
                          << "Height: " << frame.yres << '\n'
                          << "Frame-rate numerator: " << frame.frame_rate_N << '\n'
                          << "Frame-rate denominator: " << frame.frame_rate_D << '\n'
                          << "Frame rate: " << static_cast<double>(frame.frame_rate_N)
                              / frame.frame_rate_D << " fps\n"
                          << "FourCC: " << fourcc << " (0x" << std::hex << code
                          << std::dec << ")\n"
                          << "Line stride: " << frame.line_stride_in_bytes << " bytes\n";
                result = 0;
            } else {
                std::cerr << "NDI returned an invalid video frame.\n";
            }
            NDIlib_recv_free_video_v2(receiver, &frame);
            std::cout << "Video frame freed.\n";
            finished = true;
            break;
        }
        if (type == NDIlib_frame_type_error) {
            std::cerr << "NDI reported a receive/connection error.\n";
            finished = true;
            break;
        }
    }
    if (!finished) {
        std::cerr << "No video frame received within the bounded receive test (maximum 10 seconds).\n"
                  << "Active connections: " << NDIlib_recv_get_no_connections(receiver) << '\n';
    }
    NDIlib_recv_destroy(receiver);
    std::cout << "Receiver destroyed.\n";
    return result;
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cout << "ndi2v4l2 " << NDI2V4L2_VERSION << '\n';
        return 0;
    }
    const bool list = argc == 2 && std::string_view(argv[1]) == "--list";
    const bool receive = argc == 3 && std::string_view(argv[1]) == "--probe"
        && argv[2][0] != '\0';
    if (!list && !receive) {
        std::cerr << "Usage: ndi2v4l2 [--list | --probe \"<source name>\"]\n";
        return 1;
    }

    if (!NDIlib_initialize()) {
        std::cerr << "Failed to initialize the NDI runtime.\n";
        return 1;
    }
    const auto finder = NDIlib_find_create_v2(nullptr);
    if (!finder) {
        std::cerr << "Failed to create the NDI source finder.\n";
        NDIlib_destroy();
        return 1;
    }

    // Allow time for discovery even when the first source appears immediately.
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    while (std::chrono::steady_clock::now() < deadline) {
        NDIlib_find_wait_for_sources(finder, 250);
    }

    std::uint32_t count = 0;
    const auto sources = NDIlib_find_get_current_sources(finder, &count);
    int result = 0;
    if (receive) {
        const NDIlib_source_t* selected = nullptr;
        for (std::uint32_t i = 0; i < count; ++i) {
            if (sources[i].p_ndi_name && std::string_view(sources[i].p_ndi_name) == argv[2]) {
                selected = &sources[i];
                break;
            }
        }
        if (selected) {
            result = probe(*selected);
        } else {
            std::cerr << "NDI source not found: " << argv[2] << '\n';
            result = 1;
        }
    } else if (count == 0) {
        std::cout << "No NDI sources found.\n";
    } else {
        std::cout << "Available NDI sources:\n";
        for (std::uint32_t i = 0; i < count; ++i) {
            std::cout << "  " << sources[i].p_ndi_name << '\n';
        }
    }

    NDIlib_find_destroy(finder);
    NDIlib_destroy();
    if (receive) {
        std::cout << "Finder destroyed; NDI shut down.\n";
    }
    return result;
}
