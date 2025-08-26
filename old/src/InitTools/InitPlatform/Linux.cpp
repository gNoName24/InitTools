// InitPlatform -> Linux
#include <InitTools/InitPlatform.h>

// C++ Зависимости
#if defined(__linux__)
    #include <unistd.h>
    #include <cstdlib>
#endif

// Библиотечные зависимости
// #

// Модульные зависимости
// #

// InitPlatform
namespace InitPlatform {
    // Linux
    namespace Linux {
        std::string get_XDG_session_type() {
            if(get_OS() == "Linux") {
                const char* XDG_session_type = std::getenv("XDG_SESSION_TYPE");
                return XDG_session_type;
            }
            return "NON";
        }
    };
};
