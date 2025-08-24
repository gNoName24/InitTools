// InitConsole
#include <InitTools/InitConsole.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitPlatform.h>

// InitConsole
namespace InitConsole {
    void clear() {
        if(InitPlatform::get_OS() == "Windows") {
            system("cls");
        } else
        if(InitPlatform::get_OS() == "Linux") {
            system("clear");
        } else {
            log_error(fmt::runtime(_("clear.error.unsupport_os")), InitPlatform::get_OS());
        }
    }
};
