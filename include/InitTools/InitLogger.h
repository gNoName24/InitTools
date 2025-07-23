#ifndef NONAME24_INITTOOLS_INIT_LOGGER_H
#define NONAME24_INITTOOLS_INIT_LOGGER_H

// Зависмости:
//      spdlog v1.15.3

#include <memory>
#include <unordered_map>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>

namespace InitLogger {
    extern std::shared_ptr<spdlog::logger> logger;
    extern std::string logger_name;
    extern int source_loc_width;
    extern std::unordered_map<std::string, std::string> levels;
    extern std::string pattern;

    void initLogger();

    #define log_trace(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::trace, fmt, ##__VA_ARGS__)
    #define log_debug(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::debug, fmt, ##__VA_ARGS__)
    #define log_info(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::info, fmt, ##__VA_ARGS__)
    #define log_warn(fmt, ...)     logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::warn, fmt, ##__VA_ARGS__)
    #define log_error(fmt, ...)    logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::err, fmt, ##__VA_ARGS__)
    #define log_critical(fmt, ...) logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::critical, fmt, ##__VA_ARGS__)

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
}

#endif //NONAME24_INITTOOLS_INIT_LOGGER_H