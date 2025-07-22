#include "InitTools/InitLogger.h"
#include <iomanip>

std::shared_ptr<spdlog::logger> InitLogger::logger = spdlog::stdout_color_mt("console");

void InitLogger::initLogger() {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();

    formatter->add_flag<LevelShortFormat>('S');
    formatter->add_flag<AlignedLocationFlag>('L');

    formatter->set_pattern("[%^%S%$] [%T] [%L] %v");

    logger->set_formatter(std::move(formatter));
}

// LevelShort
void InitLogger::LevelShortFormat::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
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
std::unique_ptr<spdlog::custom_flag_formatter> InitLogger::LevelShortFormat::clone() const {
    return spdlog::details::make_unique<InitLogger::LevelShortFormat>();
}

// AlignedLocationFlag
void InitLogger::AlignedLocationFlag::format(const spdlog::details::log_msg& msg, const std::tm& /*tm_time*/, spdlog::memory_buf_t& dest) {
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
std::unique_ptr<spdlog::custom_flag_formatter> InitLogger::AlignedLocationFlag::clone() const {
    return spdlog::details::make_unique<InitLogger::AlignedLocationFlag>();
}