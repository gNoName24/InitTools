#include <InitTools/InitWindow.h>

// Модульные зависимости
#include <InitTools/InitConsole.h>

namespace InitWindow {
    void InitWindowClass::render_thread_start(std::function<void()> renderCallback) {
        render_thread = std::thread([this, renderCallback]() {
            glfwMakeContextCurrent(window);
            if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
                log_error("GLAD не инициализирован в потоке рендера");
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
    void InitWindowClass::render_thread_stop() {
        render_thread_running = false;
        if(render_thread.joinable()) {
            render_thread.join();
        }
    }
};
