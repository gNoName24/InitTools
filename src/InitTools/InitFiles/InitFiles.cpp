#include "InitTools/InitTools.h"
#include <InitTools/InitFiles.h>

// C++ Зависимости
#include <fstream>

// Модульные зависимости
#include <InitTools/InitConsole.h>
#include <InitTools/InitPlatform.h>

namespace InitFiles {
    bool error = false;
    std::string error_function = "";
    std::string error_code = "";

    bool& get_error() {
        return error;
    }
    std::string get_error_message() {
        if(error) {
            std::string message = std::string(InitTools::Localization::gets("InitFiles", "error_" + error_function + "_" + error_code));
            return message;
        } else {
            return "NO ERROR";
        }
    }
    void error_close() {
        if(error) {
            error = false;
            error_function = "";
            error_code = "";
        }
    }

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

    bool path_exists(std::filesystem::path path) {
        return std::filesystem::exists(path);
    }
    
    // Папки
    bool is_directory(std::filesystem::path path) {
        return std::filesystem::is_directory(path);
    }
    void directory_create(std::filesystem::path path) {
        std::filesystem::create_directory(path);
    }

    // Файлы
    bool is_file(std::filesystem::path path) {
        return std::filesystem::is_regular_file(path);
    }
    bool file_opened(std::filesystem::path path) {
        if(path_exists(path)) {
            if(is_file(path)) {
                return true;
            } else {
                error = true;
                error_function = "file_open";
                error_code = "is_file(path)";
                return false;
            }
        } else {
            error = true;
            error_function = "file_open";
            error_code = "!path_exists(path)";
            return false;
        }
    }

    std::string file_get_text_full(std::ifstream file) {
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};
