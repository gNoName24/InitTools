#include <InitTools/InitTools.h>

namespace InitTools {
    unsigned char VERSION_MAJOR = 2;
    unsigned char VERSION_MINOR = 0;
    unsigned char VERSION_PATCH = 0;

    const char* locale = "RU";
    namespace Localization {
        const u_langtable langtable = {
            {"RU", {
                    {"InitWindow", {
                        { "initGLFW_init", "Инициализация GLFW" },
                        { "initGLFW_init_fail", "Неудачная инициализация GLFW" },
                        { "initGLAD_init", "Инициализация GLAD" },
                        { "initGLAD_init_fail", "Неудачная инициализация GLAD" },
                        { "newWindow_InitLogger_nullptr", "InitLogger не был инициализирован на момент создания нового окна, так что он был инициализирован" }
                    }}
                }
            }
        };
        const std::string_view get(const char* locale, const char* module, const char* key) {
            static constexpr std::string_view unknown = "[unknown]";
            auto langIt = langtable.find(locale);
            if(langIt == langtable.end()) return unknown;
            auto modIt = langIt->second.find(module);
            if(modIt == langIt->second.end()) return unknown;
            auto keyIt = modIt->second.find(key);
            if(keyIt == modIt->second.end()) return unknown;
            return keyIt->second;
        }
        const std::string_view getSmart(const char* module, const char* key) {
            return get(locale, module, key);
        }
    };
};
