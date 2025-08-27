#ifndef NONAME24_INITTOOLS_INITCONSOLE_H
#define NONAME24_INITTOOLS_INITCONSOLE_H

// C++
#include <string>
#include <functional> // Для extern_function_*

#include <iostream>
#include <string_view> // Для класса Logger
#include <cstdio> // Для класса Logger
#include <unordered_map> // Для класса Logger
#include <vector> // Для класса Logger

namespace InitConsole {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // =================================================================

    // Билдер блоков
    namespace Block {
        std::string get_block(int length, const std::string& left, const std::string& right);
        std::string get_block(const char* start, const char* end, int length, const std::string& left, const std::string& right);
    }

    // Класс логгера
    class Logger {
    public:
        Logger(const std::string& name) {
            this->name = name;
        }

        // Сокращенные названия уровней лога и их цвета
        struct Level {
            const char* short_name;
            const char* color;
        };
        std::unordered_map<std::string, Logger::Level> levels = {
            {"info", {"I", "\033[1;37m"}},
            {"error", {"E", "\033[1;31m"}},
            {"debug", {"D", "\033[1;36m"}},
        };

        // Показывать название логгера во втором блоке
        bool show_block_name = false;

        // Длина второго/третьего блока (файл:строка функция)
        short block_code_length = 48;

        // Границы блоков
        char block_left = '[';
        char block_right = ']';

        // Доступные уровни:
        /*
         * info - Для обычных логов
         * error - Лог ошибки
         * debug - Лог, который выводится только в режиме сборке Debug
         */
        void log(const std::string& msg, const std::string& level, const std::string& file_name, int file_line, const std::string& function_name);

        // INFO
        void log_info_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name);
        #define log_info(msg) log_info_full(msg, __FILE_NAME__, __LINE__, __FUNCTION__)

        // ERROR
        void log_error_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name);
        #define log_error(msg) log_error_full(msg, __FILE_NAME__, __LINE__, __FUNCTION__)

        // DEBUG
        void log_debug_full(const std::string& msg, const std::string& file_name, int file_line, const std::string& function_name);
        #define log_debug(msg) log_debug_full(msg, __FILE_NAME__, __LINE__, __FUNCTION__)

    private:
        std::string name;
    };
};

#endif // NONAME24_INITTOOLS_INITCONSOLE_H
