// InitLocale
/** @defgroup InitLocale InitLocale
 *  \~Russian
 *      @brief Модуль InitLocale
 *  \~English
 *      @brief Module InitLocale
 */
/**
 *  @file InitLocale.h
 *  \~Russian
 *      @brief Модуль InitLocale
 *  \~English
 *      @brief Module InitLocale
 */
/////////////////////////////////////////////////
#ifndef NONAME24_INITTOOLS_INITLOCALE_H
#define NONAME24_INITTOOLS_INITLOCALE_H

// InitLocale:
    // C++ Зависимости
    #include <string>
    #include <string.h>
    // #include <array>
    #include <vector>
    #include <unordered_map>
    #include <locale>

    // Библиотечные зависимости
    #include <MoParser/MoParser.h>

    // Модульные зависимости
    #include <InitTools/InitFiles.h>
    // #include <InitTools/InitConsole.h> <- в InitLocale_LocaleManager.cpp
///////////////////////////////

#include <iostream>

/** @ingroup InitLocale
 * \~Russian
 *     @brief Модуль InitLocale
 * \~English
 *     @brief Module InitLocale
 */
namespace InitLocale {
    /** @addtogroup InitLocale
     *  @{
     */

    /**
     *  \~Russian
     *      @brief Получение текущую системную локаль
     *  \~English
     *      @brief Obtaining the current system locale
     */
    std::string get_locale_current_system();

    class LocaleManager {
    public:
        /**
         *  \~Russian
         *      @brief Путь, откуда будут браться локали
         *  \~English
         *      @brief The path from which the locales will be loaded
         */
        std::filesystem::path root;
        /**
         *  \~Russian
         *      @brief Домен в локали
         *  \~English
         *      @brief The domain in the locale
         */
        std::string domain;
        /**
         *  \~Russian
         *      @brief Основная локаль
         *  \~English
         *      @brief Primary locale
         */
        std::string primary; // Основная локаль
        /**
         *  \~Russian
         *      @brief Второстепенная локаль
         *  \~English
         *      @brief Fallback locale
         */
        std::string fallback; // Второстепенная локаль

        // Замена загрузки с файла на загрузку из переменной
        /**
         *  \~Russian
         *      @brief Замена получения байтов .mo файла основной локали на std::vector<unsigned char> с байтами .mo файла
         *      @details Если [0] == 0x00, замена не действует.
         *  \~English
         *      @brief Replacing the retrieval of bytes from the primary locale’s .mo file with a std::vector<unsigned char> containing the .mo file bytes
         *      @details If [0] == 0x00, the replacement does not take effect.
         */
        std::vector<unsigned char> replacer_primary;
        /**
         *  \~Russian
         *      @brief Замена получения байтов .mo файла второстепенной локали на std::vector<unsigned char> с байтами .mo файла
         *      @details Если [0] == 0x00, замена не действует.
         *  \~English
         *      @brief Replacing the retrieval of bytes from the fallback locale’s .mo file with a std::vector<unsigned char> containing the .mo file bytes
         *      @details If [0] == 0x00, the replacement does not take effect.
         */
        std::vector<unsigned char> replacer_fallback;

        /**
         *  \~Russian
         *      @brief Возвращать только ключи
         *  \~English
         *      @brief Return only the keys
         */
        bool only_key = false; // Выводить только ключи

        /**
         *  \~Russian
         *      @brief Инициализация
         *  \~English
         *      @brief Initialization
         */
        void init();
        /**
         *  \~Russian
         *      @brief Получение текста по ключу
         *      @param[in] key Ключ
         *  \~English
         *      @brief Retrieving text by key
         *      @param[in] key Ключ
         */
        const char* gettext(const char* key) const;

    private:
        std::vector<char> buffer_primary;
        std::vector<char> buffer_fallback;
        std::unique_ptr<GettextMoParser> primary_parser;
        std::unique_ptr<GettextMoParser> fallback_parser;
    };

    struct LocaleStorage {
        std::string domain;
        LocaleManager locale_manager;
    };

    /// @}
};

#endif // NONAME24_INITTOOLS_INITLOCALE_H
