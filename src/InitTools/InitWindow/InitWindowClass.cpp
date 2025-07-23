#include <InitTools/InitWindow.h>

namespace InitWindow {
    void InitWindowClass::initWindow() {
        #ifdef ENABLE_FUNCTION_INITLOGGER
        InitLogger::log_info("Инициализация GLFW окна");
        #endif
        window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
        if(window == nullptr) {
            glfwTerminate();
            #ifdef ENABLE_FUNCTION_INITLOGGER
            InitLogger::log_error("GLFW окно не создалось");
            #endif
        }
        glfwMakeContextCurrent(window);
    }
    std::string InitWindowClass::getTitle() {
        return glfwGetWindowTitle(window);
    }
    void InitWindowClass::setTitle(std::string title) {
        glfwSetWindowTitle(window, title.c_str());
    }
};