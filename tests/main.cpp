//#include <chrono>
#include <iostream>
#include <InitTools/InitConsole.h>
#include <InitTools/InitLocale.h>

// Логгер
InitConsole::Logger logger("test logger");

// Менеджер локали
InitLocale::LocaleManager locale_manager;

int main() {
    /*using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();*/

    //for(int i = 0; i < 1000000; i++) {
    //    logger.log_info("for " + std::to_string(i));
    //}

    /*auto end = clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    logger.log_info("Время выполнения: " + std::to_string(ms.count()) + " ms");*/

    logger.block_code_length = 32;

    InitLocale::extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {
        logger.log(msg, level, file_name, line, function_name);
    };

    logger.log_info("get_locale_current_system: " + InitLocale::get_locale_current_system());
    logger.log_info("get_locale_language: " + InitLocale::get_locale_language(InitLocale::get_locale_current_system()));
    logger.log_info("get_locale_territory: " + InitLocale::get_locale_territory(InitLocale::get_locale_current_system()));
    logger.log_info("get_locale_language_territory: " + InitLocale::get_locale_language_territory(InitLocale::get_locale_current_system()));
    logger.log_info("get_locale_codeset: " + InitLocale::get_locale_codeset(InitLocale::get_locale_current_system()));

    locale_manager.root = std::filesystem::current_path() / "resources" / "locale";
    locale_manager.domain = "test";
    locale_manager.primary = InitLocale::get_locale_language(InitLocale::get_locale_current_system());
    locale_manager.fallback = "en";
    locale_manager.build();
    logger.log_info(locale_manager.gettext("test.key"));

    return 0;
}
