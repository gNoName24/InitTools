#include <InitTools/InitDynamicLib.h>

namespace InitDynamicLib {
    namespace Function {
        void* _log_info(void** args, int argc, const ManifestUsing& manifest) {
            if(argc >= 1) {
                std::string* str = reinterpret_cast<std::string*>(args[0]);
                if(str) { log_info("[IDLIB {}] {}", std::get<std::string>(manifest.at("name")), *str); }
            }
            return nullptr;
        }
        void* _log_error(void** args, int argc, const ManifestUsing& manifest) {
            if(argc >= 1) {
                std::string* str = reinterpret_cast<std::string*>(args[0]);
                if(str) { log_error("[IDLIB {}] {}", std::get<std::string>(manifest.at("name")), *str); }
            }
            return nullptr;
        }
    }
}