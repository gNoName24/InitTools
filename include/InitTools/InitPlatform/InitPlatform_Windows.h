// Модуль InitPlatform -> Подмодуль Windows
/**
 *   @defgroup InitPlatform_Windows InitPlatform > Windows
 *   @ingroup InitPlatform
 *   \~Russian
 *       @brief Подмодуль InitPlatform > Windows
 *   \~English
 *       @brief Submodule InitPlatform > Windows
 */

/** @file InitPlatform/InitPlatform_Windows.h
 *  \~Russian
 *      @brief Подмодуль InitPlarform > Windows
 *  \~English
 *      @brief Submodule InitPlatform > Windows
 */

#ifndef NONAME24_INITTOOLS_INITPLATFORM_WINDOWS_H
#define NONAME24_INITTOOLS_INITPLATFORM_WINDOWS_H

// Зависимости C++
#include <string>

/** @ingroup InitPlatform_Windows
 *  \~Russian
 *      @brief Namespace подмодуля Windows в модуле InitPlatform
 */
namespace InitPlatform_Windows {
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
    std::string getRegistryString(const std::wstring& fullPath, const std::wstring& valueName);
   
    /**
     *  \~Russian
     *      @brief Получить разрядность Windows
     *      @return 32, 64
     *      @details Вернет NON если ОС не Windows.
     *  \~English
     *      @brief Get Windows architecture
     *      @return 32, 64
     */
    std::string getArchitecture();
    
    /**
     *  \~Russian
     *      @brief Получить название Windows продукта
     *      @return Название продукта
     *      @details Берется из реестра по пути HKEY_LOCAL_MACHINE/SOFTWARE/Microsoft/Windows NT/CurrentVersion ~ ProductName\n
     *          Вернет NON если ОС не Windows.
     */
    std::string getProductName();

    /**
     *  \~Russian
     *      @brief Получить числовую версию Windows
     *      @return XP, Vista, 7, 8, 8.1, 10, 11 и другие
     *      @details Берется название продукта через getProductName() и возвращается только второе слово.\n
     *          Вернет NON если ОС не Windows.
     */
    std::string getVersionNumber();

    /// @}
}

#endif // NONAME24_INITTOOLS_INITPLATFORM_WINDOWS_H

