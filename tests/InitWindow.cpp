#include <InitTools/InitTools.h>
#include <InitTools/InitWindow.h>

int main() {
    InitTools::global_locale_fallback = "en";
    InitTools::locale_managers.InitWindow.locale_manager.only_key = true;
    InitTools::starter();

    InitWindow::init_GLFW();
    InitWindow::new_window("test_window");

    InitWindow::InitWindow_WindowClass& window = InitWindow::windows["test_window"];
    window.render_thread_start([]() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
    });
    window.while_start();
    window.render_thread_stop();

    return 0;
}
