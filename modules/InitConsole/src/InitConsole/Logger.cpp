#include <InitTools/InitConsole.h>

// C++
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace InitConsole {
    void Logger::log(const std::string& msg, const std::string& level, const std::string& file_name, int file_line, const std::string& function_name) {
        std::string output_message;
        output_message.reserve(block_code_length + 16 + msg.size());
        Level& level_self = levels[level];

        // Короткий уровень с цветом
        output_message.append(1, block_left);
        output_message.append(level_self.color);
        output_message.append(level_self.short_name);
        output_message.append("\033[0m");
        output_message.append(1, block_right);
        output_message.append(1, ' ');

        // Время
        auto now = std::chrono::system_clock::now();

        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&t);

        std::ostringstream time_stream;
        time_stream << std::put_time(&local_tm, "%H:%M:%S");

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        output_message.append(1, block_left);
        output_message.append(time_stream.str());
        output_message.append(1, '.');
        output_message.append(std::to_string(ms.count()));
        output_message.append(1, block_right);
        output_message.append(1, ' ');

        // Название логгера
        if(show_block_name) {
            output_message.append(1, block_left);
            output_message.append(name);
            output_message.append(1, block_right);
            output_message.append(1, ' ');
        }

        // Название файла, строка файла и название функции
        output_message.append(1, block_left);
        output_message.append(Block::get_block(block_code_length, file_name + ":" + std::to_string(file_line), function_name));
        output_message.append(1, block_right);
        output_message.append(1, ' ');

        // Финальное добавление сообщения
        output_message.append(msg);
        output_message.append("\n");

        std::fwrite(output_message.data(), 1, output_message.size(), stdout);
    }
    void Logger::log_info_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name) {
        log(msg, "info", file_name, file_line, function_name);
    }
    void Logger::log_error_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name) {
        log(msg, "error", file_name, file_line, function_name);
    }
    void Logger::log_debug_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name) {
        if(std::string(BUILD_TYPE_STR) == "Debug") {
            log(msg, "debug", file_name, file_line, function_name);
        }
    }
};
