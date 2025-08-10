#include "InitTools/InitTools.h"
#include <InitTools/InitFiles.h>

// C++ Зависимости

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
    bool file_opened(std::filesystem::path path, bool need_file_exists) {
        std::filesystem::path directory = path.parent_path();
        std::filesystem::path file = path.filename();
        error_function = "file_opened";

        if(path_exists(directory)) { // Если директория для создания туда файла существует
            if(!need_file_exists) { // Если не нужно проверять наличие уже существующего файла
                if(!path_exists(path)) { // Если файл по пути еще не существует
                    return true;
                } else {
                    error = true;
                    error_code = "!path_exists(path)";
                    return false;
                }
            }
            return true;
        } else {
            error = true;
            error_code = "path_exists(directory)";
            return false;
        }
    }

    std::string file_get_text_full(std::fstream file) {
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};
