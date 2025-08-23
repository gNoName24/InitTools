#include "InitTools/InitTools.h"
#include <InitTools/InitWindow.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitConsole.h>
#include <InitTools/InitPlatform.h>

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
        // Wayland на Linux не поддерживает это событие
        if(InitPlatform::get_OS() != "Linux" && InitPlatform::Linux::get_XDG_session_type() != "Wayland") {
            glfwSetWindowPosCallback(window, InitWindow::window_pos_callback);
        } else {
            log_debug(fmt::runtime(
                _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::init_window.wayland_in_linux")),
                self_id
            );
        }
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
