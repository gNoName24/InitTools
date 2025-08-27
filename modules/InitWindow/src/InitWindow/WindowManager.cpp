// Namespace InitWindow -> Class WindowManager
#include <InitTools/InitWindow.h>

// C++
#include <stdexcept>

namespace InitWindow {
    void WindowManager::initialization() {
        INITWINDOW_log_wm("Initialization window", "debug");
        if(!initialized_GLFW) {
            initialization_GLFW();
        }
        if(window != nullptr) {
            glfwDestroyWindow(window);
            window = nullptr;
        }
        window = glfwCreateWindow(window_size.x, window_size.y, title.c_str(), nullptr, nullptr);
        if(!window) {
            INITWINDOW_log_wm("Failed to create GLFW window", "error");
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        if(!initialized_GLAD) {
            initialization_GLAD();
        }

        glfwSwapInterval(1);

        // Установка параметров
        INITWINDOW_log_wm("Setting window parameters", "debug");
        glfwSetWindowUserPointer(window, this);

            // framebuffer_size_callback
            glfwSetFramebufferSizeCallback(window, InitWindow::framebuffer_size_callback);

            // window_pos_callback
            glfwSetWindowPosCallback(window, InitWindow::window_pos_callback);
            #if defined(__linux__) // Wayland на Linux не поддерживает это событие
            const char* XDG_session_type = std::getenv("XDG_SESSION_TYPE");
            if(std::string(XDG_session_type) != "Wayland") {
                INITWINDOW_log_wm("Wayland is used, which does not support callback window_pos_callback :(", "debug");
                glfwSetWindowPosCallback(window, nullptr);
            }
            #endif

            // cursor_position_callback
            glfwSetCursorPosCallback(window, InitWindow::cursor_position_callback);

        glfwMakeContextCurrent(nullptr);
    }
    void WindowManager::terminate() {
        glfwTerminate();
    }

    void WindowManager::update_window_values() {
        // frame_count
        frame_count++;

        // delta_time
        float current_time = (float) glfwGetTime();
        delta_time = current_time - time;
        time = current_time;

        // FPS
        fps = 1.f / delta_time;
    }

    void WindowManager::render_start(std::function<void()> render_callback) {
        INITWINDOW_log_wm("Starting the render thread", "debug");
        time = (float)glfwGetTime();
        render_thread = std::thread([this, render_callback]() {
            glfwMakeContextCurrent(window);

            if(!initialized_GLAD) {
                initialization_GLAD();
            }

            //fps_target_ms = 1.0f / fps_target;
            fps_target_ms = 1000.0f / fps_target;

            render_thread_running = true;

            while(render_thread_running && !glfwWindowShouldClose(window)) {
                update_window_values();
                render_callback();
                glfwSwapBuffers(window);

                // sleep_time = fps_target_ms - delta_time;
                INITWINDOW_log_wm("delta_time: " + std::to_string(delta_time) + " / fps_target_ms: " + std::to_string(fps_target_ms), "debug");
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fps_target_ms)));
                /*if(sleep_time > 0.0f) {
                    std::this_thread::sleep_for(std::chrono::duration<float>(sleep_time));
                }*/
            }

            render_thread_running = false;

            glfwMakeContextCurrent(nullptr);
        });
    }
    void WindowManager::render_stop() {
        render_thread_running = false;
        if(render_thread.joinable()) {
            render_thread.join();
        }
    }

    void WindowManager::while_step() {
        glfwPollEvents();
        glfwWaitEventsTimeout(0.001);
    }
    void WindowManager::while_start() {
        INITWINDOW_log_wm("While start", "debug");
        while(!glfwWindowShouldClose(window)) {
            while_step();
        }
    }
    void WindowManager::while_nostop_start() {
        INITWINDOW_log_wm("While nostop start", "debug");
        while(!while_nostop) {
            while_step();
        }
        while_nostop = false;
    }
    void WindowManager::while_nostop_stop() {
        INITWINDOW_log_wm("While nostop stop", "debug");
        while_nostop = true;
    }
};
