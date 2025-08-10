/**
 * @defgroup InitFiles
 * \~Russian
 *     @brief Модуль InitFiles
 * \~English
 *     @brief Module InitFiles
 */
/**
 * @file InitFiles.h
 * \~Russian
 *     @brief Модуль InitFiles
 * \~English
 *     @brief Module InitFiles
 */
#ifndef NONAME24_INITTOOLS_INITFILES_H
#define NONAME24_INITTOOLS_INITFILES_H

// C++ зависимости
#include <string>
#include <filesystem>
#include <fstream>

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
    extern bool error;
    extern std::string error_function;
    extern std::string error_code;

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
     *      @brief Проверка на валидность пути для безопасного открытия файла
     *      @details Ошибки вносяться во внутренние переменные. Ознакомьтесь с error_* функциями и переменными.
     */
    bool file_opened(std::filesystem::path path, bool need_file_exists);

    /**
     *  \~Russian
     *      @brief Чтение и получение всего текста с std::ifstream
     *      @param[in] file Открытый файл
     */
    std::string file_get_text_full(std::ifstream file);

    /// @}
};

#endif // NONAME24_INITTOOLS_INITFILES_H
