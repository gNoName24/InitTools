#include <InitTools/InitWindow.h>

// C++ Зависимости
// #

// Библиотечные зависимости
// #

// Модульные зависимости
#include <InitTools/InitTools.h>
#include <InitTools/InitConsole.h>

// InitWindow
namespace InitWindow {
    void InitWindow_WindowClass::render_thread_start(std::function<void()> renderCallback) {
        log_debug(fmt::runtime(
            _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::render_thread_start")),
            self_id
        );
        render_thread = std::thread([this, renderCallback]() {
            glfwMakeContextCurrent(window);
            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                log_error(fmt::runtime(
                    _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::render_thread_start.error.\"!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)\"")),
                    self_id
                );
                throw std::runtime_error(fmt::format(
                    fmt::runtime(
                        _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::render_thread_start.error.\"!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)\"")),
                        self_id
                    )
                );
                return;
            }

            while(render_thread_running && !glfwWindowShouldClose(window)) {
                update();
                renderCallback();
                glfwSwapBuffers(window);
                std::this_thread::sleep_for(std::chrono::milliseconds(render_thread_sleep_milliseconds));
            }

            render_thread_running = false;
        });
    }
    void InitWindow_WindowClass::render_thread_stop() {
        log_debug(fmt::runtime(
            _("InitWindow_WindowClass.prefix") + " " + _("InitWindow_WindowClass::render_thread_stop")),
            self_id
        );
        render_thread_running = false;
        if(render_thread.joinable()) {
            render_thread.join();
        }
    }
};
