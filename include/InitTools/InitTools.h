/** @defgroup InitTools
 *  \~Russian
 *      @brief Ядро библиотеки InitTools
 *  \~English
 *      @brief InitTools library core
 */
/**
 * @file InitTools.h
 * \~Russian
 *     @brief Ядро библиотеки InitTools
 *     @details К этому файлу могут адресоваться любые модули этой библиотеки, так что этот файл не в счет как зависимость модулей.
 * \~English
 *     @brief InitTools library core
 *     @details Any modules in this library can address this file, so this file does not count as a module dependency.       
 */
#ifndef NONAME24_INITTOOLS_INITTOOLS_H
#define NONAME24_INITTOOLS_INITTOOLS_H

#include <unordered_map>
#include <string_view>

/// @ingroup InitTools
/// @brief Namespace InitTools
/**
 *  \~Russian
 *      @details Ядро всех модулей библиотеки InitTools.
 *  \~English
 *      @details The core of all modules in the InitTools library.
 */
namespace InitTools {
    /** @addtogroup InitTools
     *  @{
     */
    /**\~Russian
     * @brief Версия библиотеки (Мажор)
     * @details
     *     Это мажорное число версии.\n
     *     Мажорная версия определяет глобальную версию, которая никак не гарантирует какую-либо совместимость с предыдущими версиями прошлого мажорного числа версии.
     */
    /**\~English
     * @brief Library version (Major)
     * @details
     *     This is the major version number.\n
     *     The major version determines the global version, which does not guarantee any compatibility with previous versions of the previous major version number.
     */
    extern unsigned char VERSION_MAJOR;
    /**\~Russian
     * @brief Версия библиотеки (Минор)
     * @details
     *     Это минорное число версии.\n
     *     Минорное число версии определяет совместимость со старыми минорными версиями, когда новая минорная версия лишь добавляет новый функционал.
     */
    /**\~English
     * @brief Library version (Minor)
     * @details
     *     This is a minor version number.\n
     *     The minor version number determines compatibility with older minor versions when the new minor version only adds new functionality.
     */
    extern unsigned char VERSION_MINOR;
    /**\~Russian
     * @brief Версия библиотеки (Патч)
     * @details Исправляет текущую минорную версию, не добавляя явный новый функционал.
     */
    /**\~English
     * @brief Library version (Patch)
     * @details Fixes the current minor version without adding any explicit new functionality.
     */
    extern unsigned char VERSION_PATCH;

    /**\~Russian
     * @brief Язык библиотеки
     * @details Указанный язык используется во всех модулях этой библиотеки.\n
     *     Доступные языки: RU, EN
     */
    /**\~English
     * @brief Library language
     * @details The specified language is used in all modules of this library.\n
     *     Available languages: RU, EN
     */
    extern const char* locale;
    /// @ingroup InitTools
    /// @brief Namespace Localization
    namespace Localization {
        /** @addtogroup InitTools
         *  @{
         */
        using u_langtable = std::unordered_map<std::string_view, std::unordered_map<std::string_view, std::unordered_map<std::string_view, std::string_view>>>;
        /**\~Russian
         * @brief Хранилище локализации библиотеки
         * @details Тут хранится вся локализация данной библиотеки.\n
         *     Определение, какую локализацию использовать, определяется в переменной locale.
         */
        /**\~English
         * @brief Library localization storage
         * @details This is where all the localization for this library is stored.\n
         *     The locale to use is specified in the locale variable.
         */
        extern const u_langtable langtable;
        
        /**\~Russian
         * @brief Получение значения по указанному пути
         * @param[in] lang Ключ локали
         * @param[in] module Ключ модуля
         * @param[in] key Основной ключ
         * @return Значение из langtable
         */
        /**\~English
         * @brief Obtaining the value at the specified path
         * @param[in] lang Locale key
         * @param[in] module Module key
         * @param[in] key Main key
         * @return Value from langtable
         */
        extern const std::string_view get(const std::string_view lang, const std::string_view module, const std::string_view key);
        /**\~Russian
         * @brief Получение значения по указанному пути без необходимости указывать локаль
         * @param[in] module Ключ модуля
         * @param[in] key Основной ключ
         * @return Значение из langtable
         * @details Локаль получается из переменной locale.
         */
        /**\~English
         * @brief Obtaining a value from the specified path without having to specify the locale
         * @param[in] module Module key
         * @param[in] key Main key
         * @return Value from langtable
         * @details The locale is obtained from the locale variable.
         */
        extern const std::string_view gets(const std::string_view module, const std::string_view key);
        /// @}
    };
    /// @}
};

#endif // NONAME24_INITTOOLS_INITTOOLS_H
