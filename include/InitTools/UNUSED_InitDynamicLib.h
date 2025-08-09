/*
#ifndef NONAME24_INITTOOLS_INIT_DYNAMICLIB_H
#define NONAME24_INITTOOLS_INIT_DYNAMICLIB_H

#include <InitTools/InitLogger.h>

#include <string>
#include <functional>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace InitDynamicLib {
    using ManifestUsing = std::unordered_map<std::string, std::variant<bool, std::string>>;
    namespace Function {
        void* _log_info(void** args, int argc, const ManifestUsing& manifest);
        void* _log_error(void** args, int argc, const ManifestUsing& manifest);
    }

    using LFT_GetManifest = void* (*)();
    using LFT_RegisterExternalFunction = void(*)(const char*, std::function<void*(void**, int, ManifestUsing)>);
    using LFT_InitFunctions = void (*)();

    class InitDynamicLibClass {
    public:
        ~InitDynamicLibClass() {
            unload();
        }

        #ifdef _WIN32
            HMODULE lib = nullptr;
        #else
            void* lib = nullptr;
        #endif
        std::function<void*(const char*, void**, int)> call_func = nullptr;
        std::string path;

        // Manifest
        std::unordered_map<std::string, std::variant<bool, std::string>> manifest;
        std::string manifest_uuid4;
        std::string manifest_name;
        void manifest_parsing();

        // Функции, определенные в главном extern "C" (LF / LFT - Library Functions / Library Functions Type)
        LFT_GetManifest LF_ManifestGet;
        LFT_RegisterExternalFunction LF_RegisterExternalFunction;
        LFT_InitFunctions LF_InitFunctions;
        void LF_initialization();

        bool load(const std::string& lib_path_dll, const std::string& lib_path_so);
        void load_StandardFunction();

        void unload();

        template<typename T>
        T bind(const std::string& name);

        template<typename Ret, typename... Args>
        Ret call(const std::string& func_name, Args&&... args);

        template<typename Ret>
        Ret call_raw(const std::string& func_name, void* raw_ptr);
    };
}

#endif // NONAME24_INITTOOLS_INIT_DYNAMICLIB_H
*/
