#ifndef NONAME24_INITTOOLS_INITFILES_H
#define NONAME24_INITTOOLS_INITFILES_H

// C++ зависимости
#include <string>
#include <filesystem>

namespace InitFiles {
    std::filesystem::path get_path_in_string(std::string path);
    std::string get_string_in_path(std::filesystem::path path);
    
    std::filesystem::path get_current_directory();

    // Папки
    bool directory_exists(std::filesystem::path path);
    void directory_create(std::filesystem::path path);
    
    // Файлы

};

#endif // NONAME24_INITTOOLS_INITFILES_H
