// Модуль InitConsole -> Подмодуль Logger
/**
 *   @defgroup InitConsole_Logger InitConsole > Logger
 *   @ingroup InitConsole
 *   \~Russian
 *       @brief Подмодуль InitConsole > Logger
 *   \~English
 *       @brief Submodule InitConsole > Logger
 */

/** @file InitConsole/InitConsole_Logger.h
 *  \~Russian
 *      @brief Подмодуль InitConsole > Logger
 *  \~English
 *      @brief Submodule InitConsole > Logger
 */

#ifndef NONAME24_INITTOOLS_INITCONSOLE_LOGGER_H
#define NONAME24_INITTOOLS_INITCONSOLE_LOGGER_H

/** @brief Использовать namespace для log_*()
 */
#define INITTOOLS_INITCONSOLE_LOGGER_ENABLE_NAMESPACE false

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>

/** @ingroup InitConsole_Logger
 *  \~Russian
 *      @brief Namespace подмодуля Logger в модуле InitConsole
 */
namespace InitConsole_Logger {
    /** @addtogroup InitConsole_Logger
     *  @{
     */
    /** \~Russian
     *      @brief Главная переменная для логгера из библиотеки spdlog
     */
    extern std::shared_ptr<spdlog::logger> logger;
    /** \~Russian
     *      @brief Ширина третьего блока
     */
    extern int source_loc_width;
    /** \~Russian
     *      @brief Название logger
     */
    extern const char* logger_name;
    /** \~Russian
     *      @brief Паттер лога
     *      @details [%^%S%$] - Короткое название уровня лога\n
     *          [%T] - Время в формате HH:MM:SS\n
     *          [%L] - Данные о вызове лога в виде [файл:строка   название_функции]
     */
    extern const char* pattern;
    /** \~Russian
     *      @brief Короткие названия уровней лога
     */
    inline constexpr const char* level_short[] = {
        "T", // trace
        "D", // debug
        "I", // info
        "W", // warn
        "E", // err
        "C", // critical
        "?"  // default
    };

    /**
     * \~Russian
     *     @brief Инициализация логгера
     * \~English
     *     @brief Logger initialization
     */
    void init();

    #if INITTOOLS_INITCONSOLE_LOGGER_ENABLE_NAMESPACE
        #define log_trace(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::trace, fmt, ##__VA_ARGS__)
        #define log_debug(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::debug, fmt, ##__VA_ARGS__)
        #define log_info(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::info, fmt, ##__VA_ARGS__)
        #define log_warn(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::warn, fmt, ##__VA_ARGS__)
        #define log_error(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::err, fmt, ##__VA_ARGS__)
        #define log_critical(fmt, ...) logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::critical, fmt, ##__VA_ARGS__)
    #else
        #define LOG(level, ...) \
            if(InitConsole_Logger::logger) InitConsole_Logger::logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, level, __VA_ARGS__)
        #define log_info(...)     LOG(spdlog::level::info,     __VA_ARGS__)
        #define log_warn(...)     LOG(spdlog::level::warn,     __VA_ARGS__)
        #define log_error(...)    LOG(spdlog::level::err,      __VA_ARGS__)
        #define log_debug(...)    LOG(spdlog::level::debug,    __VA_ARGS__)
        #define log_trace(...)    LOG(spdlog::level::trace,    __VA_ARGS__)
        #define log_critical(...) LOG(spdlog::level::critical, __VA_ARGS__)
    #endif

    /// @cond
    class LevelShortFormat : public spdlog::custom_flag_formatter {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override;
        std::unique_ptr<custom_flag_formatter> clone() const override;
    };
    class AlignedLocationFlag : public spdlog::custom_flag_formatter {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm& /*tm_time*/, spdlog::memory_buf_t& dest) override;
        std::unique_ptr<custom_flag_formatter> clone() const override;
    };
    /// @endcond
    /// @}
}

#endif //NONAME24_INITTOOLS_INITCONSOLE_LOGGER_
