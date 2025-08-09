#include <InitTools/InitConsole.h>

// Модульные зависимости
#include <InitTools/InitPlatform.h>

namespace InitConsole {
    void clear() {
        if(InitPlatform::getOS() == "Windows") {
            system("cls");
        } else
        if(InitPlatform::getOS() == "Linux") {
            system("clear");
        }
    }
};
