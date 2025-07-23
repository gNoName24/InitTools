#include <InitTools/InitWindow.h>

namespace InitWindow {
    int opengl_version_major = 3;
    int opengl_version_minor = 3;
    std::unordered_map<std::string, InitWindowClass> Windows = {};

    void initGLFW() {
        InitLogger::log_info("Инициализация GLFW");
        if (!::glfwInit()) {
            InitLogger::log_error("Неудачная инициализация GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void initGLAD() {
        InitLogger::log_info("Инициализация GLAD");
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            InitLogger::log_error("Неудачная инициализация GLAD");
        }
    }

    void newWindow(std::string name) {
        if(InitLogger::logger == nullptr) {
            InitLogger::initLogger();
            InitLogger::log_info("InitLogger не был инициализирован на момент создания нового окна, так что он был инициализирован");
        }
        Windows[name] = InitWindowClass();
        Windows[name].initWindow();
    }
};