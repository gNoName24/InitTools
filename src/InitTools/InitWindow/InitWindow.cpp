// InitWindow
#include <InitTools/InitWindow.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>

// InitWindow
namespace InitWindow {
    const int opengl_version_major = 3;
    const int opengl_version_minor = 3;
    std::unordered_map<std::string, InitWindow_WindowClass> windows = {};

    void init_GLFW() {
        log_debug(_("init_GLFW"));
        if(glfwInit() != GLFW_TRUE) {
            log_error(_("init_GLFW.error.\"glfwInit() != GLFW_TRUE\""));
            throw std::runtime_error(_("init_GLFW.error.\"glfwInit() != GLFW_TRUE\""));
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    }

    void init_GLAD() {
        log_debug(_("init_GLAD"));
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            log_error(_("init_GLAD.error.\"!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)\""));
            throw std::runtime_error(_("init_GLAD.error.\"!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)\""));
        }
    }

    void new_window(std::string id) {
        InitWindow_WindowClass& window = windows.try_emplace(id).first->second;
        window.self_id = id;
        window.init_window();
        log_debug(fmt::runtime(
            _("new_window.created")),
            id
        );
    }
};
