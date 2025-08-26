// InitFiles
#include <InitTools/InitFiles.h>

// C++ Зависимости
#if defined(__linux__)
#include <limits.h>
#include <unistd.h>
#endif

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitTools.h>
#include <InitTools/InitPlatform.h> 

// InitFiles
namespace InitFiles {
    std::filesystem::path getPathInString(std::string path) {
        return std::filesystem::path(path);
    }
    std::string getStringInPath(std::filesystem::path path) {
        return path.string();
    }

    std::filesystem::path get_current_directory() {
        #if defined(_WIN32) || defined(_WIN64)
            char buffer[MAX_PATH];
            GetModuleFileNameA(NULL, buffer, MAX_PATH);
            std::filesystem::path exePath(buffer);
            return exePath.parent_path();
        #elif defined(__linux__)
            return std::filesystem::canonical("/proc/self/exe").parent_path();
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
        if(path_exists(path)) { // Если директория уже есть
            throw DirectoryExists(path.string());
        }
        std::filesystem::create_directory(path);
    }

    // Файлы
    bool is_file(std::filesystem::path path) {
        return std::filesystem::is_regular_file(path);
    }

    std::string file_get_text_line(std::ifstream file, int line) {
        if(!file.is_open()) {
            throw IFStreamNoOpen();
        }
        std::string output;
        for(int i = 1; i <= line && std::getline(file, output); ++i) {
            if(i == line) return output;
        }
        return {};
    }

    std::string file_get_text_for(std::ifstream file, int start, int end) {
        if(!file.is_open()) {
            throw IFStreamNoOpen();
        }
        std::string output;
        for(int i = start; i <= end && std::getline(file, output); ++i) {}
        return output;
    }

    std::vector<std::string> file_get_text_lines(std::istream& file) {
        std::vector<std::string> output;
        for(std::string line; std::getline(file, line); ) {
            output.push_back(std::move(line));
        }
        return output;
    }

    std::string file_get_text_full(std::ifstream file) {
        if(!file.is_open()) {
            throw IFStreamNoOpen();
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};
