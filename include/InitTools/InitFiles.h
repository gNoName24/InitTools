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
     *      @brief Получение ошибки в виде ссылки
     *  @return true / false
     */
    bool& get_error();
    /**
     *  \~Russian
     *      @brief Получение сообщения ошибки
     *      @return Сообщение ошибки
     *      @details Выявляет сообщение ошибки на основе error_function и error_code.
     */
    std::string get_error_message();
    /**
     *  \~Russian
     *      @brief Очистка ошибки после его просмотра
     */
    void error_close();

    /**
     *  \~Russian
     *      @brief Получить std::filesystem::path из std::string
     */
    std::filesystem::path get_path_in_string(std::string path);
    /**
     *  \~Russian
     *      @brief Получить std::string из std::filesystem::file
     */
    std::string get_string_in_path(std::filesystem::path path);
    
    /**
     *  \~Russian
     *      @brief Получить путь текущей директории
     *      @return Путь откуда запустился исполняемый файл
     */
    std::filesystem::path get_current_directory();

    /**
     *  \~Russian
     *      @brief Проверка на присутствие папки или файла по пути
     */
    bool path_exists(std::filesystem::path path);
    
    // Папки
    /**
     *  \~Russian
     *      @brief Проверка пути на папку
     */
    bool is_directory(std::filesystem::path path);
    /**
     *  \~Russian
     *      @brief Создание папки
     *      @param[in] path Путь как новой папке
     */
    void directory_create(std::filesystem::path path);
    
    // Файлы
    /**
     *  \~Russian
     *      @brief Проверка пути на файл
     */
    bool is_file(std::filesystem::path path);
    
    /**
     *  \~Russian
     *      @brief Чтение и получение определенной строки с std::ifstream
     *      @param[in] file Открытый файл
     *      @param[in] line Строка, которую нужно прочитать (начинатся с 0)
     */
    std::string file_get_text_line(std::ifstream file, int line);

    /**
     *  \~Russian
     *      @brief Чтение и получение указанного диапазона строк с std::ifstream
     *      @param[in] file Открытый файл
     *      @param[in] start С какой строчки начинать
     *      @param[in] end На какой строке закончить
     */
    std::string file_get_text_for(std::ifstream file, int start, int end);

    std::vector<std::string> file_get_text_lines(std::istream& file);

    /**
     *  \~Russian
     *      @brief Чтение и получение всего текста с std::fstream
     *      @param[in] file Открытый файл
     */
    std::string file_get_text_full(std::ifstream file);

    /// @}
};

#endif // NONAME24_INITTOOLS_INITFILES_H
