#include <InitTools/InitFiles.h>

// C++ Зависимости
#include <fstream>

// Модульные зависимости
#include <InitTools/InitConsole.h>
#include <InitTools/InitPlatform.h>

namespace InitFiles {
    std::filesystem::path getPathInString(std::string path) {
        return std::filesystem::path(path);
    }
    std::string getStringInPath(std::filesystem::path path) {
        return path.string();
    }

    std::filesystem::path get_current_directory() {
        #if defined(_WIN32)
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::filesystem::path exePath(buffer);
        return exePath.parent_path();
#elif defined(__linux__)
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if(count == -1) {
            throw std::runtime_error("Cannot read /proc/self/exe");
        }
        std::filesystem::path exePath(std::string(result, count));
        return exePath.parent_path();
#else
        #error "Unsupported OS";
#endif
    }

    // Папки
    bool directory_exists(std::filesystem::path path) {
        return std::filesystem::exists(path);
    }
    void directory_create(std::filesystem::path path) {
        std::filesystem::create_directory(path);
    }
};
