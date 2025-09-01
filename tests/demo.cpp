#include <InitTools/InitConsole.hpp>
#include <InitTools/InitLocale.hpp>
#include <InitTools/InitWindow.hpp>

#include <sstream>

InitConsole::Logger logger("logger");

void update_color(uint8_t rgb[3]) {
    static int phase = 0;
    static int step  = 0;
    const int maxStep = 255;

    switch(phase) {
        case 0: rgb[1] = step; break;
        case 1: rgb[0] = 255 - step; break;
        case 2: rgb[2] = step; break;
        case 3: rgb[1] = 255 - step; break;
        case 4: rgb[0] = step; break;
        case 5: rgb[2] = 255 - step; break;
    }

    step++;
    if(step > maxStep) {
        step = 0;
        phase = (phase + 1) % 6;
    }
}

int main() {
    InitWindow::extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {
        logger.log(msg, level, file_name, line, function_name);
    };

    InitWindow::WindowManager* window = nullptr;
    InitWindow::window_new("window", &window);

    window->initialization();
    window->set_fps_target(60);

    int time_int_back = 0;

    uint8_t color[] = {255, 0, 0};
    window->render_start([&window, &time_int_back, &color]() {
        update_color(color);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color[0] / 256.0f, color[1] / 256.0f, color[2] / 256.0f, 1.0f);

        // FPS
        std::ostringstream title;
        title << "FPS: " << static_cast<int>(std::round(window->get_fps()))
              << " / color: {"
              << static_cast<int>(color[0]) << ", "
              << static_cast<int>(color[1]) << ", "
              << static_cast<int>(color[2]) << "}";
        window->set_title(title.str());
    });
    window->while_start();
    window->render_stop();

    window->terminate();
    return 0;
}
