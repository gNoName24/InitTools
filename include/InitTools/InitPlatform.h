// InitPlatform
/** @defgroup InitPlatform InitPlatform
 *  \~Russian
 *      @brief Модуль InitPlatform
 *  \~English
 *      @brief Module InitPlatform
 */
/**
 *  @file InitPlatform.h
 *  \~Russian
 *      @brief Модуль InitPlatform
 *  \~English
 *      @brief Module InitPlatform
 */
///////////////////////////////////////
// InitPlatform -> Windows
/**
 *   @defgroup InitPlatform_Windows InitPlatform > Windows
 *   @ingroup InitPlatform
 *   \~Russian
 *       @brief Подмодуль InitPlatform > Windows
 *   \~English
 *       @brief Submodule InitPlatform > Windows
 */
//////////////////////////////////////////////////////////
#ifndef NONAME24_INITTOOLS_INITPLATFORM_H
#define NONAME24_INITTOOLS_INITPLATFORM_H

// Зависимости C++
#include <string>
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

// InitPlatform:
    // C++ Зависимости
    // #

    // Библиотечные зависимости
    // #

    // Модульные зависимости
    // #

///////////////////////////////
// InitPlatform -> Windows:
    // C++ Зависимости
    // #

    // Библиотечные зависимости
    // #

    // Модульные зависимости
    // #
///////////////////////////////

/** @ingroup InitPlatform
 *  \~Russian
 *      @brief Модуль InitPlatform
 *  \~English
 *      @brief Module InitPlatform
 */
namespace InitPlatform {
    /** @addtogroup InitPlatform
     *  @{
     */
    
    /** \~Russian
     *      @brief Получить ОС в виде std::string
     *      @return Windows, Linux, Apple, Unix, POSIX, Unknown
     */
    std::string get_OS(); 

    /** @ingroup InitPlatform_Windows
     *  \~Russian
     *      @brief Namespace подмодуля Windows в модуле InitPlatform
     */
    namespace Windows {
        /** @addtogroup InitPlatform_Windows
         *  @{
         */

        /**
         *  \~Russian
         *      @brief Получить строковое значение из реестра Windows
         *      @param[in] fullPath Путь к папке
         *      @param[in] valueName Название переменной
         *      @details Вернет NON если ОС не Windows.
         */
        std::string get_registry_string(const std::wstring& fullPath, const std::wstring& valueName);

        /**
         *  \~Russian
         *      @brief Получить разрядность Windows
         *      @return 32, 64
         *      @details Вернет NON если ОС не Windows.
         *  \~English
         *      @brief Get Windows architecture
         *      @return 32, 64
         */
        std::string get_architecture();

        /**
         *  \~Russian
         *      @brief Получить название Windows продукта
         *      @return Название продукта
         *      @details Берется из реестра по пути HKEY_LOCAL_MACHINE/SOFTWARE/Microsoft/Windows NT/CurrentVersion ~ ProductName\n
         *          Вернет NON если ОС не Windows.
         */
        std::string get_product_name();

        /**
         *  \~Russian
         *      @brief Получить числовую версию Windows
         *      @return XP, Vista, 7, 8, 8.1, 10, 11 и другие
         *      @details Берется название продукта через getProductName() и возвращается только второе слово.\n
         *          Вернет NON если ОС не Windows.
         */
        std::string get_version_number();

        /// @}
    };

    /// @} 
};

#endif // NONAME24_INITTOOLS_INITPLATFORM_H
