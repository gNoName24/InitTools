#include <InitTools/InitWindow.h>

// Модульные зависимости
#include <InitTools/InitTools.h>
#include <InitTools/InitConsole.h>

namespace InitWindow {
    void InitWindow_WindowClass::render_thread_start(std::function<void()> renderCallback) {
        render_thread = std::thread([this, renderCallback]() {
            glfwMakeContextCurrent(window);
            if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
                //log_error(InitTools::Localization::gets("InitWindow", "InitWindow_WindowClass::render_thread_start_GLAD_noload"));
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
        render_thread_running = false;
        if(render_thread.joinable()) {
            render_thread.join();
        }
    }
};
