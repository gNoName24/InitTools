// InitTools
/** @defgroup InitTools
 *  \~Russian
 *      @brief Ядро библиотеки InitTools
 *  \~English
 *      @brief InitTools library core
 */
/**
 *  @file InitTools.h
 *  \~Russian
 *      @brief Ядро библиотеки InitTools
 *      @details К этому файлу могут адресоваться любые модули этой библиотеки, так что этот файл не в счет как зависимость модулей.
 *  \~English
 *      @brief InitTools library core
 *      @details Any modules in this library can address this file, so this file does not count as a module dependency.       
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NONAME24_INITTOOLS_INITTOOLS_H
#define NONAME24_INITTOOLS_INITTOOLS_H

// InitTools:
    // C++ Зависимости
    // #include <unordered_map> <- Уже есть в InitLocale.h
    // #include <string> <- Уже есть в InitLocale.h

    // Библиотечные зависимости
    // #

    // Модульные зависимости
    // #include <InitTools/InitConsole.h> <- в InitTools.cpp
    // #include <InitTools/InitFiles.h> <- в InitTools.cpp
    #include <InitTools/InitLocale.h>

////////////////////////////////////////////////////////////

/** @ingroup InitTools
 *  @brief Namespace InitTools
 *  \~Russian
 *      @details Ядро всех модулей библиотеки InitTools.
 *  \~English
 *      @details The core of all modules in the InitTools library.
 */
namespace InitTools {
    /** @addtogroup InitTools
     *  @{
     */

    /**
     *  \~Russian
     *      @brief Версия библиотеки (Мажор)
     *      @details
     *          Это мажорное число версии.\n
     *          Мажорная версия определяет глобальную версию, которая никак не гарантирует какую-либо совместимость с предыдущими версиями прошлого мажорного числа версии.
     *  \~English
     *      @brief Library version (Major)
     *      @details
     *          This is the major version number.\n
     *          The major version determines the global version, which does not guarantee any compatibility with previous versions of the previous major version number.
     */
    extern unsigned char VERSION_MAJOR;
    /**
     *  \~Russian
     *      @brief Версия библиотеки (Минор)
     *      @details
     *          Это минорное число версии.\n
     *          Минорное число версии определяет совместимость со старыми минорными версиями, когда новая минорная версия лишь добавляет новый функционал.
     *  \~English
     *      @brief Library version (Minor)
     *      @details
     *          This is a minor version number.\n
     *          The minor version number determines compatibility with older minor versions when the new minor version only adds new functionality.
     */
    extern unsigned char VERSION_MINOR;
    /**
     *  \~Russian
     *      @brief Версия библиотеки (Патч)
     *      @details Исправляет текущую минорную версию, не добавляя явный новый функционал.
     *  \~English
     *      @brief Library version (Patch)
     *      @details Fixes the current minor version without adding any explicit new functionality.
     */
    extern unsigned char VERSION_PATCH;

    // Хранилище локалей для каждого модуля. Наследует LocaleStorage
    struct LocaleStorageModules : InitLocale::LocaleStorage {
        std::vector<unsigned char> replacer_primary;
        std::vector<unsigned char> replacer_fallback;
        LocaleStorageModules(
            const std::string& domain_,
            const std::vector<unsigned char>& replacer_primary_ = {0x00},
            const std::vector<unsigned char>& replacer_fallback_ = {0x00}
        ) {
            domain = domain_;
            replacer_primary = replacer_primary_;
            replacer_fallback = replacer_fallback_;
        }
    };
    // Все .mo, конвертированные в массив байтов
    // [Локаль][Модуль][.mo]
    extern std::unordered_map<std::string,std::unordered_map<std::string, const std::vector<unsigned char>>> locale_MOs;

    /**
     *  \~Russian
     *      @brief Основная локаль библиотеки InitTools
     *      @details Ключ берется отсюда, если этот же ключ не найден в второстепенной локали.\n
     *          Доступные локали: ru, en.
     */
    extern std::string global_locale_primary; // Основная локаль, распространенная на все модули
    /**
     *  \~Russian
     *      @brief Второстепенная локаль библиотеки InitTools
     *      @details Сначала ключ берется отсюда, а если не найден, ищется в основной локали.\n
     *          Доступные локали: ru, en.
     */
    extern std::string global_locale_fallback; // Второстепенная локаль, распространенная на все модули

    // Список всех LocaleStorageModules каждого модуля
    struct LocaleManagers {
        LocaleStorageModules InitTools{"InitTools"};
        LocaleStorageModules InitWindow{"InitWindow"};
    };

    // Каждый модуль может обратиться к этой переменной
    extern LocaleManagers locale_managers;

    void locale_module_init(LocaleManagers& locale_module_manager);

    extern bool starter_hide_info;
    extern bool starter_hide_info_after_first_run; // true - спрятать log_info после первого запуска
    extern bool starter_first_run;

    /**
     *  \~Russian
     *      @brief Стартовое сообщение
     *  \~English
     *      @brief Starter message
     */
    void starter();

    /// @}
};

#endif // NONAME24_INITTOOLS_INITTOOLS_H
