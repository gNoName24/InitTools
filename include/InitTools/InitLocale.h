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
     *      @brief Getting the current system locale
     */
    std::string get_locale_current_system();

    class LocaleManager {
    public:
        std::filesystem::path root;
        std::string domain;
        std::string primary; // Основная локаль
        std::string fallback; // Второстепенная локаль

        // Замена загрузки с файла на загрузку из переменной
        std::vector<unsigned char> replacer_primary;
        std::vector<unsigned char> replacer_fallback;

        void init();

        const char* _(const char* key) const {
            GettextMessage* msg = nullptr;

            if(fallback_parser && fallback_parser->ready()) {
                msg = fallback_parser->getTranslation(key, static_cast<int>(strlen(key)));
            }

            // Если не найдено в второстепенной локали, то берется из основной

            if(!msg && primary_parser && primary_parser->ready()) {
                msg = primary_parser->getTranslation(key, static_cast<int>(strlen(key)));
            }

            return msg ? msg->string : key;
        }

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
