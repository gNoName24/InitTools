// InitLocale -> Класс LocaleManager
#include <InitTools/InitLocale.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>

// InitLocale
namespace InitLocale {
    void LocaleManager::init() {
        primary_parser = std::make_unique<GettextMoParser>();
        fallback_parser = std::make_unique<GettextMoParser>();

        std::filesystem::path primary_path = root / primary / "LC_MESSAGES" / (domain + ".mo");
        std::filesystem::path fallback_path = root / fallback / "LC_MESSAGES" / (domain + ".mo");

        if(replacer_primary[0] == 0x00) {
            primary_parser->parseFile(primary_path.string().c_str());
        } else {
            char* buf = new char[replacer_primary.size()];
            memcpy(buf, replacer_primary.data(), replacer_primary.size());
            primary_parser->parse(buf);
        }
        if(replacer_fallback[0] == 0x00) {
            fallback_parser->parseFile(fallback_path.string().c_str());
        } else {
            char* buf = new char[replacer_fallback.size()];
            memcpy(buf, replacer_fallback.data(), replacer_fallback.size());
            fallback_parser->parse(buf);
        }
    }
};
