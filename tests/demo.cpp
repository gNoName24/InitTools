#include <InitTools/InitConsole.h>
#include <InitTools/InitLocale.h>
#include <InitTools/InitWindow.h>

InitConsole::Logger logger("logger");

int main() {
    InitWindow::extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {
        logger.log(msg, level, file_name, line, function_name);
    };

    InitWindow::WindowManager* window = nullptr;
    InitWindow::window_new("window", &window);

    window->initialization();
    window->set_fps_target(60);

    int time_int_back = 0;
    window->render_start([&window, &time_int_back]() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // FPS
        int time_int = static_cast<int>(window->get_time());
        if(time_int != time_int_back) {
            window->set_title("FPS: " + std::to_string(
                static_cast<int>(std::round(window->get_fps()))
            ));
            time_int_back = time_int;
        }
    });
    window->while_start();
    window->render_stop();

    window->terminate();
    return 0;
}
