#include <InitTools/InitTools.h>
#include <InitTools/InitConsole.h>
#include <InitTools/InitLocale.h>

int main() {
    //InitTools::global_locale_fallback = "en";
    InitTools::starter();
    //InitConsole::clear();

    std::string system_locale = InitLocale::get_locale_current_system();
    log_info("{}", system_locale);

    log_info("get_locale_language: {}", InitLocale::get_locale_language(system_locale));
    log_info("get_locale_territory: {}", InitLocale::get_locale_territory(system_locale));
    log_info("get_locale_language_territory: {}", InitLocale::get_locale_language_territory(system_locale));
    log_info("get_locale_codeset: {}", InitLocale::get_locale_codeset(system_locale));

    return 0;
}
