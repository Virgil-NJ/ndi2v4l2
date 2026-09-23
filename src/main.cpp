#include <cstddef> // The NDI headers require NULL to be defined.
#include <Processing.NDI.Lib.h>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <string_view>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cout << "ndi2v4l2 " << NDI2V4L2_VERSION << '\n';
        return 0;
    }
    if (argc != 2 || std::string_view(argv[1]) != "--list") {
        std::cerr << "Usage: ndi2v4l2 [--list]\n";
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
    if (count == 0) {
        std::cout << "No NDI sources found.\n";
    } else {
        std::cout << "Available NDI sources:\n";
        for (std::uint32_t i = 0; i < count; ++i) {
            std::cout << "  " << sources[i].p_ndi_name << '\n';
        }
    }

    NDIlib_find_destroy(finder);
    NDIlib_destroy();
    return 0;
}
