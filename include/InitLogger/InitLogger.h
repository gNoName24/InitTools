#ifndef NONAME24_INIT_LOGGER_H
#define NONAME24_INIT_LOGGER_H

#include <memory>
#include <iomanip>

#include <spdlog/spdlog.h>
// #include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>

namespace InitLogger {
    extern std::shared_ptr<spdlog::logger> Logger;
    void initLogger();

    #define log_trace(fmt, ...)    Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::trace, fmt, ##__VA_ARGS__)
    #define log_debug(fmt, ...)    Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::debug, fmt, ##__VA_ARGS__)
    #define log_info(fmt, ...)     Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::info, fmt, ##__VA_ARGS__)
    #define log_warn(fmt, ...)     Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::warn, fmt, ##__VA_ARGS__)
    #define log_error(fmt, ...)    Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::err, fmt, ##__VA_ARGS__)
    #define log_critical(fmt, ...) Logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::critical, fmt, ##__VA_ARGS__)

    class LevelShortForm : public spdlog::custom_flag_formatter {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override {
            std::string level;
            switch(msg.level) {
                case spdlog::level::info:     level = "I"; break;
                case spdlog::level::err:      level = "E"; break;
                case spdlog::level::warn:     level = "W"; break;
                case spdlog::level::debug:    level = "D"; break;
                case spdlog::level::trace:    level = "T"; break;
                case spdlog::level::critical: level = "C"; break;
                default: level = "?";
            }
            dest.append(level.data(), level.data() + level.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return spdlog::details::make_unique<LevelShortForm>();
        }
    };

    class AlignedLocationFlag : public spdlog::custom_flag_formatter {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm& /*tm_time*/, spdlog::memory_buf_t& dest) override {
            const char* file = msg.source.filename ? msg.source.filename : "???";
            const char* func = msg.source.funcname ? msg.source.funcname : "???";
            int line = msg.source.line;

            std::ostringstream oss;

            const int total_width = 45;
            std::string file_line = fmt::format("{}:{}", file, line);

            auto pos = file_line.find_last_of("/\\");
            if(pos != std::string::npos)
                file_line = file_line.substr(pos + 1);

            int space_for_func = total_width - static_cast<int>(file_line.size());

            oss << file_line;
            if(space_for_func > 0)
                oss << std::setw(space_for_func) << std::right << func;

            fmt::format_to(std::back_inserter(dest), "{}", oss.str());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override {
            return spdlog::details::make_unique<AlignedLocationFlag>();
        }
    };
}

#endif //NONAME24_INIT_LOGGER_H