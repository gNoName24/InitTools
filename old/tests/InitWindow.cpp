#include <InitTools/InitTools.h>
#include <InitTools/InitWindow.h>
#include <InitTools/InitConsole.h>

// #include <random>

int main() {
    InitTools::starter();

    InitWindow::init_GLFW();
    InitWindow::new_window("test_window");

    InitWindow::InitWindow_WindowClass& window = InitWindow::windows["test_window"];
    window.render_thread_start([&window]() {
        glm::ivec2& window_size = window.window_size;
        glm::vec3 rgb = glm::vec3(glm::vec2(window_size) / 1000.0f, (window_size.x + window_size.y) / 2000.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(rgb.r, rgb.g, rgb.b, 1.0f);
        //if(static_cast<int>(window.frame_count) % static_cast<int>(window.FPS) == 0) {
            window.set_title(
                "delta_time: " + std::to_string(window.delta_time) +
                " / FPS: " + std::to_string(window.FPS) +
                " / frame_count: " + std::to_string(window.frame_count) +
                " / time: " + std::to_string(window.time)
            );
        //}
    });
    window.while_start();
    window.render_thread_stop();

    return 0;
}
