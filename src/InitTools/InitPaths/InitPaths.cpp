#include <InitTools/InitPaths.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif

#include <filesystem>

namespace InitPaths {
    std::string root;
    std::string root_data = "/Resources";
    #if INITTOOLS_INITPATHS_ENABLE_PATHS
        #if INITTOOLS_INITPATHS_USE_STRING_VIEW
            std::unordered_map<std::string_view, std::string_view> paths = {};
        #else
            std::unordered_map<std::string, std::string> paths = {};
        #endif
    #endif

    void init() {
        std::string path;
        #if defined(_WIN32)
            char buffer[MAX_PATH];
            DWORD length = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
            path = std::string(buffer, length);
        #elif defined(__linux__)
            char buffer[4096];
            ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
            if (length != -1) {
                buffer[length] = '\0';
                path = std::string(buffer);
            }
        #elif defined(__APPLE__)
            char buffer[4096];
            uint32_t size = sizeof(buffer);
            if (_NSGetExecutablePath(buffer, &size) == 0) {
                path = std::string(buffer);
            }
        #else
            static_assert(false, "Unsupported platform");
        #endif

        root = std::filesystem::path(path).parent_path().string();
        root_data = root + root_data;
    }
};