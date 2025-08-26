#ifndef NONAME24_INITTOOLS_INITLOCALE_H
#define NONAME24_INITTOOLS_INITLOCALE_H

// C++
#include <string>
#include <functional> // Для extern_function_*
#include <filesystem> // Для класса LocaleManager

// MoParser
#include <MoParser/MoParser.h>

namespace InitLocale {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // extern_function_log (Родитель - InitConsole)
    extern std::function<
    void(
        const std::string& msg, // Текст
         const std::string& level, // Уровень лога
         const std::string& file_name, // Название файла
         int line, // Строка файла
         const std::string& function_name // Название функции
    )
    > extern_function_log;
    #define INITLOCALE_log(msg, level) extern_function_log(msg, level, __FILE_NAME__, __LINE__, __FUNCTION__)

    // =================================================================

    std::string get_locale_current_system();
    std::string get_locale_language(std::string locale);
    std::string get_locale_territory(std::string locale);
    std::string get_locale_language_territory(std::string locale);
    std::string get_locale_codeset(std::string locale);

    class LocaleManager {
    public:
        std::filesystem::path root;
        std::string domain;
        std::string primary; // Основная локаль
        std::string fallback; // Второстепенная локаль

        // Парсить вместо файлов массив байтов. 0x00 первым значением означает пропускать эту переменную.
        std::vector<unsigned char> replacer_primary = {0x00};
        std::vector<unsigned char> replacer_fallback = {0x00};

        bool only_key = false; // Выводить только ключи

        void build();
        std::string gettext(const char* key) const;

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
};

#endif // NONAME24_INITTOOLS_INITLOCALE_H
