// InitTools
#include <InitTools/InitTools.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>
#include <InitTools/InitFiles.h>

namespace InitTools {
    unsigned char VERSION_MAJOR = 2;
    unsigned char VERSION_MINOR = 0;
    unsigned char VERSION_PATCH = 0;

    LocaleManagers locale_managers;
    std::string global_locale_primary = "ru";
    std::string global_locale_fallback = "ru";

    void locale_mos_init(LocaleManagers& locale_module_manager) {
        locale_module_manager.InitTools = LocaleStorageModules(
            "InitTools",
            locale_MOs[global_locale_primary]["InitTools"],
            locale_MOs[global_locale_fallback]["InitTools"]
        );
        locale_module_manager.InitWindow = LocaleStorageModules(
            "InitWindow",
            locale_MOs[global_locale_primary]["InitWindow"],
            locale_MOs[global_locale_fallback]["InitWindow"]
        );
        locale_module_manager.InitConsole = LocaleStorageModules(
            "InitConsole",
            locale_MOs[global_locale_primary]["InitConsole"],
            locale_MOs[global_locale_fallback]["InitConsole"]
        );
    }

    void locale_module_init(LocaleStorageModules& locale_module_manager) {
        InitLocale::LocaleManager& locallm = locale_module_manager.locale_manager; // Locale Manager

        locallm.root = InitFiles::get_current_directory() / "resources" / "locales";
        locallm.domain = locale_module_manager.domain;
        locallm.primary = global_locale_primary;
        locallm.fallback = global_locale_fallback;
        locallm.replacer_primary = locale_module_manager.replacer_primary;
        locallm.replacer_fallback = locale_module_manager.replacer_fallback;
        locallm.init();
    }

    bool starter_hide_info = false;
    bool starter_hide_info_after_first_run = true;
    bool starter_first_run = false;
    void starter() {
        locale_mos_init(locale_managers);
        locale_module_init(locale_managers.InitTools);
        locale_module_init(locale_managers.InitWindow);
        locale_module_init(locale_managers.InitConsole);
        InitLocale::LocaleManager& locallm = locale_managers.InitTools.locale_manager;

        if(starter_hide_info) return;
        if(starter_hide_info_after_first_run == true) {
            if(starter_first_run == true) return;
        }
        log_info("InitTools v{}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
        log_info("InitTools: {} - {}", locallm.gettext("primary_locale"), global_locale_primary);
        log_info("InitTools: {} - {}", locallm.gettext("fallback_locale"), global_locale_fallback);
        log_info("InitTools: {} - {}", locallm.gettext("current_directory"), InitFiles::get_current_directory().string());
        starter_first_run = true;
    }
};
