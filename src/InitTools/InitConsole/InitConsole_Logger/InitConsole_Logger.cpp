#include <InitTools/InitConsole/InitConsole_Logger.h>

namespace InitConsole_Logger {
    std::shared_ptr<spdlog::logger> logger = nullptr;
    int source_loc_width = 32;
    const char* logger_name = "console";
    const char* pattern = "[%^%S%$] [%T] [%L] %v";

    void init() {
        logger = spdlog::stdout_color_mt(logger_name);
        auto formatter = std::make_unique<spdlog::pattern_formatter>();

        formatter->add_flag<LevelShortFormat>('S');
        formatter->add_flag<AlignedLocationFlag>('L');

        formatter->set_pattern(pattern);

        logger->set_formatter(std::move(formatter));
    }

    // LevelShort
    void LevelShortFormat::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
        auto index = static_cast<size_t>(msg.level);
        if (index >= SPDLOG_LEVEL_OFF)
            index = SPDLOG_LEVEL_OFF;
        const char* short_level = level_short[index];
        dest.append(short_level, short_level + std::strlen(short_level));
        /*std::string level;
        switch(msg.level) {
            case spdlog::level::info:     level = levels["info"]; break;
            case spdlog::level::err:      level = levels["err"]; break;
            case spdlog::level::warn:     level = levels["warn"]; break;
            case spdlog::level::debug:    level = levels["debug"]; break;
            case spdlog::level::trace:    level = levels["trace"]; break;
            case spdlog::level::critical: level = levels["critical"]; break;
            default: level = levels["default"];
        }
        dest.append(level.data(), level.data() + level.size());*/
    }
    std::unique_ptr<spdlog::custom_flag_formatter> LevelShortFormat::clone() const {
        return spdlog::details::make_unique<LevelShortFormat>();
    }

    // AlignedLocationFlag
    /*void AlignedLocationFlag::format(const spdlog::details::log_msg& msg, const std::tm& / *tm_time* /, spdlog::memory_buf_t& dest) {
        const char* file = msg.source.filename ? msg.source.filename : "???";
        const char* func = msg.source.funcname ? msg.source.funcname : "???";
        int line = msg.source.line;
        std::ostringstream oss;

        std::string file_line = fmt::format("{}:{}", file, line);
        auto pos = file_line.find_last_of("/\\");
        if(pos != std::string::npos)
            file_line = file_line.substr(pos + 1);

        int space_for_func = source_loc_width - static_cast<int>(file_line.size());

        oss << file_line;
        if(space_for_func > 0)
            oss << std::setw(space_for_func) << std::right << func;

        fmt::format_to(std::back_inserter(dest), "{}", oss.str());
    }*/
    void AlignedLocationFlag::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
        const char* file = msg.source.filename ? msg.source.filename : "???";
        const char* func = msg.source.funcname ? msg.source.funcname : "???";
        int line = msg.source.line;

        std::string file_line = fmt::format("{}:{}", file, line);
        auto pos = file_line.find_last_of("/\\");
        if (pos != std::string::npos)
            file_line = file_line.substr(pos + 1);

        int space_for_func = source_loc_width - static_cast<int>(file_line.size());
        space_for_func = std::max(0, space_for_func);

        fmt::format_to(std::back_inserter(dest), "{}{:>{}}", file_line, func, space_for_func);
    }
    std::unique_ptr<spdlog::custom_flag_formatter> AlignedLocationFlag::clone() const {
        return spdlog::details::make_unique<InitConsole_Logger::AlignedLocationFlag>();
    }
}
