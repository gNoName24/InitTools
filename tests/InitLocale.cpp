#include <InitTools/InitTools.h>
#include <InitTools/InitConsole.h>

int main() {
    InitTools::starter();

    // Изменение fallback_locale на английский
    InitTools::global_locale_fallback = "en";
    InitTools::starter();
    log_info("InitTools testing get key: {}", InitTools::locale_managers.InitTools.locale_manager._("primary_locale"));

    return 0;
}
