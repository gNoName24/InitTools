// InitLocale
#include <InitTools/InitLocale.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
// #

// InitLocale
namespace InitLocale {
    std::string get_locale_current_system() {
        return setlocale(LC_ALL, "");
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
