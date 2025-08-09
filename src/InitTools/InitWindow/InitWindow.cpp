#include <InitTools/InitWindow.h>

// Модульные зависимости
#include <InitTools/InitTools.h> // Ядро
#include <InitTools/InitConsole.h>

namespace InitWindow {
    int opengl_version_major = 3;
    int opengl_version_minor = 3;
    std::unordered_map<std::string, InitWindow_WindowClass> windows = {};

    void initGLFW() {
        log_info(InitTools::Localization::gets("InitWindow", "initGLFW_init"));
        if(!::glfwInit()) {
            log_error(InitTools::Localization::gets("InitWindow", "initGLFW_init_fail"));
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        //glfwWindowHint(GLFW_ALPHA_BITS, 8);
    }

    void initGLAD() {
        log_info(InitTools::Localization::gets("InitWindow", "initGLAD_init"));
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            log_error(InitTools::Localization::gets("InitWindow", "initGLAD_init_fail"));
        }
    }

    void newWindow(std::string id) {
        if(InitConsole::Logger::logger == nullptr) {
            InitConsole::Logger::init();
            log_info(InitTools::Localization::gets("InitWindow", "newWindow_InitLogger_nullptr"));
        }
        windows.try_emplace(id);
        windows[id].selfID = id;
        windows[id].initWindow();
    }
};
