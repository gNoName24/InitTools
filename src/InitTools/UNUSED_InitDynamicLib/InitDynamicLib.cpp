/*
#include <InitTools/InitDynamicLib.h>

namespace InitDynamicLib {
    bool InitDynamicLibClass::load(const std::string& lib_path_dll, const std::string& lib_path_so) {
        #ifdef _WIN32
            path = lib_path_dll;
        #else
            path = lib_path_so;
        #endif
        #ifdef _WIN32
            lib = LoadLibraryA(path.c_str());
            if(!lib) {
                log_error("Не удалось загрузить динамическую библиотеку: {}", path);
                return false;
            }
            call_func = reinterpret_cast<void*(*)(const char*, void**, int)>(
                GetProcAddress(lib, "CallFunction"));
        #else
            lib = dlopen(path.c_str(), RTLD_NOW);
            if(!lib) {
                InitLogger::log_error("Не удалось загрузить .so: {}", path);
                return false;
            }
            call_func = reinterpret_cast<void*(*)(const char*, void**, int)>(
                dlsym(lib, "CallFunction"));
        #endif
        if(!call_func) {
            log_error("Функция CallFunction не найдена в динамической библиотеке: {}", path);
            return false;
        }

        LF_initialization();

        // Manifest
        manifest_parsing();
        log_info("Dynamic Library Manifest: {} / {}", manifest_uuid4, manifest_name);

        return true;
    }

    // Инициализация LF_*
    void InitDynamicLibClass::LF_initialization() {
        LF_ManifestGet = bind<LFT_GetManifest>("ManifestGet");
        LF_RegisterExternalFunction = bind<LFT_RegisterExternalFunction>("RegisterExternalFunction");
        LF_InitFunctions = bind<LFT_InitFunctions>("InitFunctions");
    }

    void InitDynamicLibClass::manifest_parsing() {
        manifest = *reinterpret_cast<std::unordered_map<std::string, std::variant<bool, std::string>>*>(LF_ManifestGet());
        manifest_uuid4 = std::get<std::string>(manifest["uuid4"]);
        manifest_name = std::get<std::string>(manifest["name"]);
    }

    void InitDynamicLibClass::load_StandardFunction() {
        LF_RegisterExternalFunction("InitDynamicLib_log_info", InitDynamicLib::Function::_log_info);
        LF_RegisterExternalFunction("InitDynamicLib_log_error", InitDynamicLib::Function::_log_error);
    }

    void InitDynamicLibClass::unload() {
        #ifdef _WIN32
            if(lib) FreeLibrary(lib);
        #else
            if(lib) dlclose(lib);
        #endif
        lib = nullptr;
        call_func = nullptr;
    }

    template<typename T>
    T InitDynamicLibClass::bind(const std::string& name) {
        if(!lib) return T(nullptr);
        #ifdef _WIN32
            return reinterpret_cast<T>(GetProcAddress(lib, name.c_str()));
        #else
            return reinterpret_cast<T>(dlsym(lib, name.c_str()));
        #endif
    }

    template<typename Ret, typename... Args>
    Ret InitDynamicLibClass::call(const std::string& func_name, Args&&... args) {
        if(!call_func) return Ret();
        void* arg_ptrs[] = { (void*)&args... };
        if constexpr (std::is_void_v<Ret>) {
            call_func(func_name.c_str(), arg_ptrs, sizeof...(Args));
        } else {
            void* result = call_func(func_name.c_str(), arg_ptrs, sizeof...(Args));
            return *reinterpret_cast<Ret*>(result);
        }
    }

    template<typename Ret>
    Ret InitDynamicLibClass::call_raw(const std::string& func_name, void* raw_ptr) {
        if(!call_func) return Ret();
        void* arg_ptrs[] = { raw_ptr };
        if constexpr (std::is_void_v<Ret>) {
            call_func(func_name.c_str(), arg_ptrs, 1);
            return;
        } else {
            void* result = call_func(func_name.c_str(), arg_ptrs, 1);
            return *reinterpret_cast<Ret*>(result);
        }
    }
}
*/
