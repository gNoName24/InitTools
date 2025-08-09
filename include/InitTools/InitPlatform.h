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

// Модульные зависимости
// #include <InitTools/InitTools.h> <- В .cpp

// Подмодули
#include "InitPlatform/InitPlatform_Windows.h"

/** @ingroup InitPlatform
 *  \~Russian
 *      @brief Модуль InitPlatform
 *  \~English
 *      @brief Module InitPlatform
 */
namespace InitPlatform {
    namespace Windows = ::InitPlatform_Windows;

    /** @addtogroup InitPlatform
     *  @{
     */
    
    /** \~Russian
     *      @brief Получить ОС в виде std::string
     *      @return Windows, Linux, Apple, Unix, POSIX, Unknown
     */
    std::string getOS(); 

    /// @}
};

#endif // NONAME24_INITTOOLS_INITPLATFORM_H
