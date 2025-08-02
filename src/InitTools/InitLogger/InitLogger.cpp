#include "InitTools/InitLogger.h"
#include <iomanip>

namespace InitLogger {
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::string logger_name = "console";
    int source_loc_width = 32;
    std::unordered_map<std::string, std::string> levels = {
        {"info", "I"}, {"err", "E"}, {"warn", "W"},
        {"debug", "D"}, {"trace", "T"}, {"critical", "C"},
        {"default", "?"}
    };
    std::string pattern = "[%^%S%$] [%T] [%L] %v";

    void initLogger() {
        logger = spdlog::stdout_color_mt(logger_name);
        auto formatter = std::make_unique<spdlog::pattern_formatter>();

        formatter->add_flag<LevelShortFormat>('S');
        formatter->add_flag<AlignedLocationFlag>('L');

        formatter->set_pattern(pattern);

        logger->set_formatter(std::move(formatter));
    }

    // LevelShort
    void LevelShortFormat::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
        std::string level;
        switch(msg.level) {
            case spdlog::level::info:     level = levels["info"]; break;
            case spdlog::level::err:      level = levels["err"]; break;
            case spdlog::level::warn:     level = levels["warn"]; break;
            case spdlog::level::debug:    level = levels["debug"]; break;
            case spdlog::level::trace:    level = levels["trace"]; break;
            case spdlog::level::critical: level = levels["critical"]; break;
            default: level = levels["default"];
        }
        dest.append(level.data(), level.data() + level.size());
    }
    std::unique_ptr<spdlog::custom_flag_formatter> LevelShortFormat::clone() const {
        return spdlog::details::make_unique<LevelShortFormat>();
    }

    // AlignedLocationFlag
    void AlignedLocationFlag::format(const spdlog::details::log_msg& msg, const std::tm& /*tm_time*/, spdlog::memory_buf_t& dest) {
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
    }
    std::unique_ptr<spdlog::custom_flag_formatter> AlignedLocationFlag::clone() const {
        return spdlog::details::make_unique<InitLogger::AlignedLocationFlag>();
    }
}