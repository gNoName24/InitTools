#include <InitTools/InitTools.h>

int main() {
    InitTools::starter();

    // Изменение fallback_locale на английский
    /*log_info("Установка global_locale_fallback на en");
    InitTools::global_locale_fallback = "en";
    InitTools::starter();
    log_info("testing get key: {}", InitTools::locale_managers.InitTools.locale_manager._("primary_locale"));*/

    while(true) {}

    return 0;
}
