// InitConsole
/**
 *  @defgroup InitConsole InitConsole
 *  \~Russian
 *      @brief Модуль InitConsole
 *  \~English
 *      @brief Module InitConsole
 */
/**
 *  @file InitConsole.h
 *  \~Russian
 *      @brief Модуль InitConsole
 *  \~English
 *      @brief Module InitConsole
 */
////////////////////////////////////
// InitConsole > Logger
/** @defgroup InitConsole_Logger InitConsole > Logger
 *  @ingroup InitConsole
 *  \~Russian
 *      @brief Подмодуль InitConsole > Logger
 *  \~English
 *      @brief Submodule InitConsole > Logger
 */
//////////////////////////////////////////////////////
#ifndef NONAME24_INITTOOLS_INITCONSOLE_H
#define NONAME24_INITTOOLS_INITCONSOLE_H

// InitConsole:
    // C++ Зависимости
    // #

    // Библиотечные зависимости
    // #

    // Модульные зависимости
    #include <InitTools/InitTools.h>
    // #include <InitTools/InitPlatform.h> <- в InitConsole.cpp

///////////////////////////////////////////////////////////////
// InitConsole -> Logger:
    // C++ Зависимости
    // #
    
    // Библиотечные зависимости
    #include <spdlog/spdlog.h>
    // #include <spdlog/sinks/stdout_color_sinks.h> <- В Logger.cpp
    #include <spdlog/pattern_formatter.h>

    // Модульные зависимости
    // #
    
///////////////////////////////////////////////////////////////////

// InitConsole -> Logger:
    /** 
     *  \~Russian
     *      @brief Использовать namespace для log_*()
     *  \~English
     *      @brief Use namespace for log_*()
     */
    #define INITTOOLS_INITCONSOLE_LOGGER_ENABLE_NAMESPACE false

/** @ingroup InitConsole
 *  \~Russian
 *      @brief Модуль InitConsole
 *  \~English
 *      @brief Module InitConsole
 */
namespace InitConsole {
    // InitTools LocaleManagers ~ InitConsole
    inline auto _ = [](const char* key) -> std::string {
        return InitTools::locale_managers.InitConsole.locale_manager.gettext(key);
    };

    /** @addtogroup InitConsole
     *  @{
     */

    /**
     *  \~Russian
     *      @brief Очистка консоли
     *  \~English
     *      @brief Clear console
     */ 
    void clear();

    /** @ingroup InitConsole_Logger
     *  \~Russian
     *      @brief Namespace подмодуля Logger в модуле InitConsole
     *  \~English
     *      @brief Namespace of the submodule Logger in the module InitConsole
     */
    namespace Logger {
        /** @addtogroup InitConsole_Logger
         *  @{
         */
        
        /** \~Russian
         *      @brief Главная переменная для логгера из библиотеки spdlog
         *  \~English
         *      @brief Main variable for logger from spdlog library
         */
        extern std::shared_ptr<spdlog::logger> logger;
        /**
         *  \~Russian
         *      @brief Ширина третьего блока
         *  \~English
         *      @brief Width of the third block
         */
        extern int source_loc_width;
        /**
         *  \~Russian
         *      @brief Название logger
         *  \~English
         *      @brief Logger name
         */
        extern const char* logger_name;
        /**
         *  \~Russian
         *      @brief Паттер лога
         *      @details [%^%S%$] - Короткое название уровня лога\n
         *          [%T] - Время в формате HH:MM:SS\n
         *          [%L] - Данные о вызове лога в виде [файл:строка   название_функции]
         *  \~English
         *      @brief Log pattern
         *      @details [%^%S%$] - Short name of the log level\n
         *          [%T] - Time in HH:MM:SS format\n
         *          [%L] - Log call data in the form [file:string   function_name]
         */
        extern const char* pattern;
        /**
         *  \~Russian
         *      @brief Короткие названия уровней лога
         *  \~English
         *      @brief Short names of log levels
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
         *  \~Russian
         *      @brief Инициализация логгера
         *  \~English
         *      @brief Logger initialization
         */
        void init();
       
        /**
         *  \~Russian
         *      @brief Инициализирован ли логгер
         *      @return Если logger == nullptr, то выдает false
         *  \~English
         *      @brief Is the logger initialized
         *      @details If logger == nullptr, then returns false
         */ 
        bool initialized();

        /**
         *  \~Russian
         *      @brief Проверка на инициализацию
         *      @details Если логгер не инициализирован, то вызывается инициализация.
         *  \~English
         *      @brief Initialization check
         *      @details If the logger is not initialized, initialization is called.
         */
        void init_check();

        #if INITTOOLS_INITCONSOLE_LOGGER_ENABLE_NAMESPACE
            #define log_trace(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::trace, fmt, ##__VA_ARGS__)
            #define log_debug(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::debug, fmt, ##__VA_ARGS__)
            #define log_info(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::info, fmt, ##__VA_ARGS__)
            #define log_warn(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::warn, fmt, ##__VA_ARGS__)
            #define log_error(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::err, fmt, ##__VA_ARGS__)
            #define log_critical(fmt, ...) logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::critical, fmt, ##__VA_ARGS__)
        #else
            #define LOG(level, ...) \
                InitConsole::Logger::init_check(); \
                InitConsole::Logger::logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, level, __VA_ARGS__);
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

    /// @}
};

#endif // NONAME24_INITTOOLS_INITCONSOLE_H
