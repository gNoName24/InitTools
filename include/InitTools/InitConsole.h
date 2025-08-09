/**
 * @defgroup InitConsole InitConsole
 * \~Russian
 *     @brief Модуль InitConsole
 * \~English
 *     @brief Module InitConsole
 */
/**
 * @file InitConsole.h
 * \~Russian
 *     @brief Модуль InitConsole
 * \~English
 *     @brief Module InitConsole
 */
#ifndef NONAME24_INITTOOLS_INITCONSOLE_H
#define NONAME24_INITTOOLS_INITCONSOLE_H

// Подмодули
#include "InitConsole/InitConsole_Logger.h"

/** @ingroup InitConsole
 * \~Russian
 *     @brief Модуль InitConsole
 * \~English
 *     @brief Module InitConsole
 */
namespace InitConsole {
    namespace Logger = ::InitConsole_Logger;
    
    /** @addtogroup InitConsole
     *  @{
     */

    /**
     * \~Russian
     *     @brief Очистка консоли
     */ 
    void clear();
    
    /// @}
};

#endif // NONAME24_INITTOOLS_INITCONSOLE_H
