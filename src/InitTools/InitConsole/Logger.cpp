// InitConsole -> Logger
#include <InitTools/InitConsole.h>

// C++ Зависимости
// #

// Библиотечные зависимости
#include <spdlog/sinks/stdout_color_sinks.h> 

// Модульные зависимости
// #

// InitConsole
namespace InitConsole {
    // Logger
    namespace Logger {
        std::shared_ptr<spdlog::logger> logger = nullptr;
        int source_loc_width = 48;
        const char* logger_name = "console";
        const char* pattern = "[%^%S%$] [%T] [%L] %v";

        void init() {
            logger = spdlog::stdout_color_mt(logger_name);
            auto formatter = std::make_unique<spdlog::pattern_formatter>();

            formatter->add_flag<LevelShortFormat>('S');
            formatter->add_flag<AlignedLocationFlag>('L');

            formatter->set_pattern(pattern);

            logger->set_formatter(std::move(formatter));

            #ifdef NDEBUG
                logger->set_level(spdlog::level::info);
            #else
                logger->set_level(spdlog::level::trace);
            #endif
        }

        bool initialized() {
            if(logger == nullptr) {
                return false;
            }
            return true;
        }

        void init_check() {
            if(!initialized()) {
                init();
            }
        }

        // LevelShort
        void LevelShortFormat::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
            auto index = static_cast<size_t>(msg.level);
            if(index >= SPDLOG_LEVEL_OFF)
                index = SPDLOG_LEVEL_OFF;
            const char* short_level = level_short[index];
            dest.append(short_level, short_level + std::strlen(short_level));
        }
        std::unique_ptr<spdlog::custom_flag_formatter> LevelShortFormat::clone() const {
            return spdlog::details::make_unique<LevelShortFormat>();
        }

        // AlignedLocationFlag
        void AlignedLocationFlag::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) {
            const char* file = msg.source.filename ? msg.source.filename : "???";
            const char* func = msg.source.funcname ? msg.source.funcname : "???";
            int line = msg.source.line;

            std::string file_line = fmt::format("{}:{}", file, line);
            auto pos = file_line.find_last_of("/\\");
            if(pos != std::string::npos)
                file_line = file_line.substr(pos + 1);

            int space_for_func = source_loc_width - static_cast<int>(file_line.size());
            space_for_func = std::max(0, space_for_func);

            fmt::format_to(std::back_inserter(dest), "{}{:>{}}", file_line, func, space_for_func);
        }
        std::unique_ptr<spdlog::custom_flag_formatter> AlignedLocationFlag::clone() const {
            return spdlog::details::make_unique<Logger::AlignedLocationFlag>();
        }
    };
};
