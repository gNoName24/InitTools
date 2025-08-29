#include <InitTools/InitLocale.hpp>

// C++
#include <cstring>

namespace InitLocale {
    void LocaleManager::build() {
        INITLOCALE_log(
            "Build locale [domain - " + domain +
            " / primary - " + primary +
            " / fallback - " + fallback + "]"
        , "debug");
        primary_parser = std::make_unique<GettextMoParser>();
        fallback_parser = std::make_unique<GettextMoParser>();

        std::filesystem::path primary_path = root / primary / "LC_MESSAGES" / (domain + ".mo");
        std::filesystem::path fallback_path = root / fallback / "LC_MESSAGES" / (domain + ".mo");

        if(replacer_primary[0] == 0x00) {
            primary_parser->parseFile(primary_path.string().c_str());
        } else {
            char* buf = new char[replacer_primary.size()];
            std::memcpy(buf, replacer_primary.data(), replacer_primary.size());
            primary_parser->parse(buf);
        }
        if(replacer_fallback[0] == 0x00) {
            fallback_parser->parseFile(fallback_path.string().c_str());
        } else {
            char* buf = new char[replacer_fallback.size()];
            std::memcpy(buf, replacer_fallback.data(), replacer_fallback.size());
            fallback_parser->parse(buf);
        }
    }

    std::string LocaleManager::gettext(const char* key) const {
        if(only_key) return key;
        GettextMessage* msg = nullptr;

        if(fallback_parser && fallback_parser->ready()) msg = fallback_parser->getTranslation(key, static_cast<int>(strlen(key)));

        // Если не найдено в второстепенной локали, то берется из основной
        if(!msg && primary_parser && primary_parser->ready()) msg = primary_parser->getTranslation(key, static_cast<int>(strlen(key)));

        return msg ? msg->string : key;
    }
};
