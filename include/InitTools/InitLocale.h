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
    // #include <InitTools/InitConsole.h> <- в InitLocale_Locale.cpp
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
    //std::string get_locale_current_system();

    class LocaleManager {
    public:
        std::filesystem::path root;
        std::string domain;
        std::string primary; // Основная локаль
        std::string fallback; // Второстепенная локаль

        // Замена загрузки с файла на загрузку из переменной
        std::vector<unsigned char> replacer_primary;
        std::vector<unsigned char> replacer_fallback;
        bool use_replacer_primary = false;
        bool use_replacer_fallback = false;

        void init() {
            primary_parser = std::make_unique<GettextMoParser>();
            fallback_parser = std::make_unique<GettextMoParser>();

            std::filesystem::path primary_path = root / primary / "LC_MESSAGES" / (domain + ".mo");
            std::filesystem::path fallback_path = root / fallback / "LC_MESSAGES" / (domain + ".mo");

            if(use_replacer_primary == false) {
                primary_parser->parseFile(primary_path.string().c_str());
            } else {
                char* buf = new char[replacer_primary.size()];
                memcpy(buf, replacer_primary.data(), replacer_primary.size());
                primary_parser->parse(buf);
                std::cout << "replacer_primary on" << std::endl;
            }
            if(use_replacer_fallback == false) {
                fallback_parser->parseFile(fallback_path.string().c_str());
            } else {
                char* buf = new char[replacer_fallback.size()];
                memcpy(buf, replacer_fallback.data(), replacer_fallback.size());
                fallback_parser->parse(buf);
                std::cout << "replacer_fallback on" << std::endl;
            }

            if (primary_parser->ready())
                std::cout << "[Locale] Primary ready: " << primary_path << std::endl;
            else
                std::cout << "[Locale] Primary NOT ready: " << primary_path << std::endl;

            if (fallback_parser->ready())
                std::cout << "[Locale] Fallback ready: " << fallback_path << std::endl;
            else
                std::cout << "[Locale] Fallback NOT ready: " << fallback_path << std::endl;
        }

        const char* _(const char* key) const {
            GettextMessage* msg = nullptr;

            if(fallback_parser && fallback_parser->ready())
                msg = fallback_parser->getTranslation(key, static_cast<int>(strlen(key)));

            // Если не найдено в второстепенной локали, то берется из основной

            if(!msg && primary_parser && primary_parser->ready())
                msg = primary_parser->getTranslation(key, static_cast<int>(strlen(key)));

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
