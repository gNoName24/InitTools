#include "InitTools/InitTools.h"
#include <InitTools/InitWindow.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>

// InitWindow
namespace InitWindow {
    void InitWindow_WindowClass::init_window() {
        log_debug(fmt::runtime(
            _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::init_window")),
            self_id
        );
        window = glfwCreateWindow(window_size.x, window_size.y, self_id.c_str(), nullptr, nullptr);
        if(window == nullptr) {
            glfwTerminate();
            log_error(fmt::runtime(
                _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::init_window.error.\"window == nullptr\"")),
                self_id
            );
            throw std::runtime_error(fmt::format(
                fmt::runtime(
                    _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::init_window.error.\"window == nullptr\"")),
                    self_id
                )
            );
        }
        glfwMakeContextCurrent(window);

        log_debug(fmt::runtime(
            _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::init_window.set_parameters")),
            self_id
        );
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, InitWindow::framebuffer_size_callback);
        glfwSetWindowPosCallback(window, InitWindow::window_pos_callback);
        glfwSetCursorPosCallback(window, InitWindow::cursor_position_callback);

        glfwMakeContextCurrent(nullptr);
    }
    void InitWindow_WindowClass::update() {
        frame_count++;
    }

    void InitWindow_WindowClass::while_glfwEvents() {
        glfwPollEvents();
    }

    void InitWindow_WindowClass::while_start() {
        log_debug(fmt::runtime(
            _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::while_start")),
            self_id
        );
        while(!glfwWindowShouldClose(window)) {
            while_glfwEvents();
        }
    }

    std::string InitWindow_WindowClass::get_title() {
        return glfwGetWindowTitle(window);
    }
    void InitWindow_WindowClass::set_title(std::string& title) {
        glfwSetWindowTitle(window, title.c_str());
    }
};
