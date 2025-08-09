#include "InitTools/InitTools.h"
#include <InitTools/InitWindow.h>

// Модульные зависимости
#include <InitTools/InitConsole.h>

namespace InitWindow {
    void InitWindow_WindowClass::initWindow() {
        log_info(InitTools::Localization::gets("InitWindow", "InitWindow_WindowClass::initWindow_start"));
        window = glfwCreateWindow(window_size.x, window_size.y, "Window", nullptr, nullptr);
        if(window == nullptr) {
            glfwTerminate();
            log_error(InitTools::Localization::gets("InitWindow", "InitWindow_WindowClass::initWindow_window_nullptr"));
        }
        glfwMakeContextCurrent(window);

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, InitWindow::framebuffer_size_callback);
        glfwSetWindowPosCallback(window, InitWindow::window_pos_callback);
        glfwSetCursorPosCallback(window, InitWindow::cursor_position_callback);

        glfwMakeContextCurrent(nullptr);
    }
    void InitWindow_WindowClass::update() {
        frame_count++;
    }

    void InitWindow_WindowClass::while_glfwPollEvents() {
        glfwPollEvents();
    }

    void InitWindow_WindowClass::while_start() {
        while(!glfwWindowShouldClose(window)) {
            while_glfwPollEvents();
        }
    }

    std::string InitWindow_WindowClass::getTitle() {
        return glfwGetWindowTitle(window);
    }
    void InitWindow_WindowClass::setTitle(std::string title) {
        glfwSetWindowTitle(window, title.c_str());
    }
};
