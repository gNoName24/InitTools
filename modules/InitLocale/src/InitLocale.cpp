#include <InitTools/InitLocale.h>

namespace InitLocale {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // extern_function_log
    std::function<void(
        const std::string& msg,
        const std::string& level,
        const std::string& file_name,
        int line,
        const std::string& function_name
    )> extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {};

    // =================================================================

    std::string get_locale_current_system() {
        return setlocale(LC_ALL, ""); // xx_XX.UTF-8
    }
    std::string get_locale_language(std::string locale) {
        return locale.substr(0, 2); // xx
    }
    std::string get_locale_territory(std::string locale) {
        return locale.substr(3, 2); // XX
    }
    std::string get_locale_language_territory(std::string locale) {
        return locale.substr(0, 5); // xx_XX
    }
    std::string get_locale_codeset(std::string locale) {
        return locale.substr(6, locale.size()); // UTF-8
    }
};
