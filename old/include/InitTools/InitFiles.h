// InitFiles
/** @defgroup InitFiles
 *  \~Russian
 *      @brief Модуль InitFiles
 *  \~English
 *      @brief Module InitFiles
 */
/**
 *  @file InitFiles.h
 *  \~Russian
 *      @brief Модуль InitFiles
 *  \~English
 *      @brief Module InitFiles
 */
///////////////////////////////
#ifndef NONAME24_INITTOOLS_INITFILES_H
#define NONAME24_INITTOOLS_INITFILES_H

// InitFiles:
    // C++ Зависимости
    #include <string>
    #include <vector>
    #include <filesystem>
    #include <fstream>

    // Библиотечные зависимости
    // #

    // Модульные зависимости
    // #include <InitTools/InitPlatform.h> <- в InitFiles.cpp

/////////////////////////////////////////////////////////////

/** @ingroup InitFiles
 * \~Russian
 *     @brief Модуль InitFiles
 * \~English
 *     @brief Module InitFiles
 */
namespace InitFiles {
    /** @addtogroup InitFiles
     *  @{
     */

    // Исключения
    class runtime_error : public std::runtime_error {
    public:
        explicit runtime_error(const std::string& msg) : std::runtime_error(msg) {}
    };
    // Файл есть
    class FileExists : public runtime_error {
    public:
        explicit FileExists(const std::string& path)
        : runtime_error("File exists: " + path) {}
    };
    // Файла нет
    class FileNoExists : public runtime_error {
    public:
        explicit FileNoExists(const std::string& path)
        : runtime_error("File no exists: " + path) {}
    };
    // Директория есть
    class DirectoryExists : public runtime_error {
    public:
        explicit DirectoryExists(const std::string& path)
        : runtime_error("Directory exists: " + path) {}
    };
    // Директории нет
    class DirectoryNoExists : public runtime_error {
    public:
        explicit DirectoryNoExists(const std::string& path)
        : runtime_error("Directory no exists: " + path) {}
    };
    // ifstream не открыт
    class IFStreamNoOpen : public runtime_error {
    public:
        explicit IFStreamNoOpen()
        : runtime_error("ifstream is_open() == false") {}
    };

    /**
     *  \~Russian
     *      @brief Получить std::filesystem::path из std::string
     *  \~English
     *      @brief Get std::filesystem::path from std::string
     */
    std::filesystem::path get_path_in_string(std::string path);
    /**
     *  \~Russian
     *      @brief Получить std::string из std::filesystem::file
     *  \~English
     *      @brief Get std::string from std::filesystem::file
     */
    std::string get_string_in_path(std::filesystem::path path);
    
    /**
     *  \~Russian
     *      @brief Получить путь текущей директории
     *      @return Путь, откуда запустился исполняемый файл
     *  \~English
     *      @brief Get the path of the current directory
     *      @details The path from which the executable file was launched
     */
    std::filesystem::path get_current_directory();

    /**
     *  \~Russian
     *      @brief Проверка на присутствие папки или файла по пути
     *  \~English
     *      @brief Checking for the exists of a folder or file along a path
     */
    bool path_exists(std::filesystem::path path);
    
    // Папки
    /**
     *  \~Russian
     *      @brief Проверка пути на папку
     *  \~English
     *      @brief Checking the path to the folder
     */
    bool is_directory(std::filesystem::path path);
    /**
     *  \~Russian
     *      @brief Создание папки
     *      @param[in] path Путь как новой папке
     *  \~English
     *      @brief Creating a folder
     *      @param[in] path Path as a new folder
     */
    void directory_create(std::filesystem::path path);
    
    // Файлы
    /**
     *  \~Russian
     *      @brief Проверка пути на файл
     *  \~English
     *      @brief Checking the path to the file
     */
    bool is_file(std::filesystem::path path);
    
    /**
     *  \~Russian
     *      @brief Чтение и получение определенной строки с std::ifstream
     *      @param[in] file Открытый файл
     *      @param[in] line Строка, которую нужно прочитать (начинатся с 0)
     *  \~English
     *      @brief Reading and retrieving a specific string from std::ifstream
     *      @param[in] file Opened file
     *      @param[in] line The line to read (starting from 0)
     */
    std::string file_get_text_line(std::ifstream file, int line);

    /**
     *  \~Russian
     *      @brief Чтение и получение указанного диапазона строк с std::ifstream
     *      @param[in] file Открытый файл
     *      @param[in] start С какой строчки начинать
     *      @param[in] end На какой строке закончить
     *  \~English
     *      @brief Reading and receiving the specified range of lines with std::ifstream
     *      @param[in] file Opened file
     *      @param[in] start Which line to start with
     *      @param[in] end On which line to end
     */
    std::string file_get_text_for(std::ifstream file, int start, int end);

    /**
     *  \~Russian
     *      @brief Чтение и получение всех строк в std::vector<std::string>
     *      @param[in] file Открытый файл
     *  \~English
     *      @brief Reading and retrieving all strings in std::vector<std::string>
     *      @param[in] file Opened file
     */
    std::vector<std::string> file_get_text_lines(std::istream& file);

    /**
     *  \~Russian
     *      @brief Чтение и получение всего текста с std::fstream
     *      @param[in] file Открытый файл
     *  \~English
     *      @brief Reading and receiving the entire text with std::fstream
     *      @param[in] file Opened file
     */
    std::string file_get_text_full(std::ifstream file);

    /// @}
};

#endif // NONAME24_INITTOOLS_INITFILES_H
