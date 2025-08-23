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
        //glm::ivec2& window_position = window.window_position;
        //log_debug("window_size: [{}, {}]", window_size.x, window_size.y);
        //("window_position: [{}, {}]", window_position.x, window_position.y);
        glm::vec3 rgb = glm::vec3(glm::vec2(window_size) / 1000.0f, (window_size.x + window_size.y) / 2000.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(rgb.r, rgb.g, rgb.b, 1.0f);
    });
    window.while_start();
    window.render_thread_stop();

    return 0;
}
