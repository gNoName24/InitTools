#include <InitTools/InitWindow.h>

// Модульные зависимости
#include <InitTools/InitConsole.h>

namespace InitWindow {
    void InitWindowClass::initWindow() {
        log_info("Инициализация GLFW окна");
        window = glfwCreateWindow(window_size.x, window_size.y, "Window", nullptr, nullptr);
        if(window == nullptr) {
            glfwTerminate();
            log_error("GLFW окно не создалось");
        }
        glfwMakeContextCurrent(window);

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, InitWindow::framebuffer_size_callback);
        glfwSetWindowPosCallback(window, InitWindow::window_pos_callback);
        glfwSetCursorPosCallback(window, InitWindow::cursor_position_callback);

        glfwMakeContextCurrent(nullptr);
    }
    void InitWindowClass::update() {
        frame_count++;
    }

    std::string InitWindowClass::getTitle() {
        return glfwGetWindowTitle(window);
    }
    void InitWindowClass::setTitle(std::string title) {
        glfwSetWindowTitle(window, title.c_str());
    }
};
