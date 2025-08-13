// InitTools
#include <InitTools/InitTools.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>

namespace InitTools {
    unsigned char VERSION_MAJOR = 2;
    unsigned char VERSION_MINOR = 0;
    unsigned char VERSION_PATCH = 0;

    void starter() {
        if(!InitConsole::Logger::initialized()) {
            InitConsole::Logger::init();
        }
        log_info("InitTools v{}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    }

    const char* locale = "RU";
    namespace Localization {
        const u_langtable langtable = {
            {"RU", {
                    {"InitWindow", {
                        { "initGLFW_init", "Инициализация GLFW" },
                        { "initGLFW_init_fail", "Неудачная инициализация GLFW" },
                        { "initGLAD_init", "Инициализация GLAD" },
                        { "initGLAD_init_fail", "Неудачная инициализация GLAD" },
                        { "newWindow_InitLogger_nullptr", "InitLogger не был инициализирован на момент создания нового окна, так что он был инициализирован" },
                        { "InitWindow_WindowClass::initWindow_start", "Инициализация GLFW окна" },
                        { "InitWindow_WindowClass::initWindow_window_nullptr", "GLFW окно не создалось, window == nullptr" },
                        { "InitWindow_WindowClass::render_thread_start_GLAD_noload", "GLAD не инициализирован в потоке рендера" },
                    }},
                    {"InitFiles", {
                        { "", "" }
                    }}
                }
            }
        };
        const std::string_view get(const std::string_view lang, const std::string_view module, const std::string_view key) {
            static constexpr std::string_view unknown = "[unknown]";
            auto langIt = langtable.find(locale);
            if(langIt == langtable.end()) return unknown;
            auto modIt = langIt->second.find(module);
            if(modIt == langIt->second.end()) return unknown;
            auto keyIt = modIt->second.find(key);
            if(keyIt == modIt->second.end()) return unknown;
            return keyIt->second;
        }
        const std::string_view gets(const std::string_view module, const std::string_view key) {
            return get(locale, module, key);
        }
    };
};
