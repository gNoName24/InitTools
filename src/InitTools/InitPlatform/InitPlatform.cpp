// InitPlatform
#include <InitTools/InitPlatform.h>

// InitPlatform
namespace InitPlatform {
    std::string get_OS() {
        #if defined(_WIN32) || defined(_WIN64)
            return "Windows";
        #elif defined(__linux__)
            return "Linux";
        #elif defined(__APPLE__) && defined(__MACH__)
            return "Apple";
        #elif defined(__unix__) || defined(__unix)
            return "Unix";
        #elif defined(_POSIX_VERSION)
            return "POSIX";
        #else
            return "Unknown";
        #endif
    }
};
