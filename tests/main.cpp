#include <InitTools/InitConsole.hpp>
#include <InitTools/InitWindow.hpp>
#include <InitTools/InitGraphics.hpp>

// Логгер
InitConsole::Logger logger("logger");

// Окно
InitWindow::WindowManager* window = nullptr;

// InitGraphics
InitGraphics::BaseCVVE CVVE;

int main() {
    InitWindow::extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {
        logger.log(msg, level, file_name, line, function_name);
    };
    InitWindow::window_new("window", &window);
    window->initialization();
    window->set_fps_target(60);

    CVVE.initialization();

    window->render_start(
    []() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });

    window->while_start();

    window->render_stop();
    CVVE.terminate();
    window->terminate();
    return 0;
}
