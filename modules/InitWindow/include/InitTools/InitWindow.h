// Module InitWindow
#ifndef NONAME24_INITTOOLS_INITWINDOW_H
#define NONAME24_INITTOOLS_INITWINDOW_H

// C++
#include <functional> // Для extern_function_*
#include <string>
#include <cstdint>
#include <unordered_map>

#include <atomic> // Для класса WindowManager
#include <thread> // Для класса WindowManager

// Библиотеки
#include <glad/glad.h> // GLAD
#include <GLFW/glfw3.h> // GLFW
#include <glm/glm.hpp> // GLM

namespace InitWindow {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // extern_function_log (Родитель - InitConsole)
    extern std::function<
    void(
        const std::string& msg, // Текст
        const std::string& level, // Уровень лога
        const std::string& file_name, // Название файла
        int line, // Строка файла
        const std::string& function_name // Название функции
    )
    > extern_function_log;
    #define INITWINDOW_log(msg, level) extern_function_log(msg, level, __FILE_NAME__, __LINE__, __FUNCTION__)

    // =================================================================

    // Логгер внутри WindowManager
    #define INITWINDOW_log_wm(msg, level) extern_function_log("[" + id + "] " + msg, level, __FILE_NAME__, __LINE__, __FUNCTION__)

    extern uint8_t opengl_target_version_major;
    extern uint8_t opengl_target_version_minor;

    extern bool initialized_GLFW;
    extern bool initialized_GLAD;
    void initialization_GLFW();
    void initialization_GLAD();

    class WindowManager;
    extern std::unordered_map<std::string, WindowManager> windows;

    void window_new(const std::string& id);
    WindowManager& window_new(const std::string& id, bool need_return);

    class WindowManager {
    public:
        WindowManager(const std::string& id) {
            this->id = id;
        }
        void initialization();
        void terminate();

        void update_window_values();

        std::atomic<bool> render_thread_running = false;
        std::thread render_thread;
        void render_start(std::function<void()> render_callback);
        void render_stop();

        // Функции, которые выполняются в основных циклах
        void while_step();
        // Цикл, который останавливается на основе !glfwWindowShouldClose(window)
        void while_start();
        // Цикл, который останавливается на основе переменной остановки
        bool while_nostop = false;
        void while_nostop_start();
        void while_nostop_stop();

        // Segment Set-Get ----------------------

        // - Window

        // id
        const std::string& get_id() const;

        // title
        void set_title(const std::string& title);
        const std::string& get_title() const;

        // window_size
        void set_window_size(const glm::ivec2& window_size);
        const glm::ivec2& get_window_size() const;

        // window_position
        void set_window_position(const glm::ivec2& window_position);
        const glm::ivec2& get_window_position() const;

        // frame_count
        const uint32_t& get_frame_count() const;

        // time
        const float& get_time() const;

        // delta_time
        const float& get_delta_time() const;

        // fps_target
        const uint16_t& get_fps_target() const;

        // fps_target_ms
        const float& get_fps_target_ms() const;

        // fps
        const float& get_fps() const;

        // - Mouse

        // --------------------------------------

        // Segment Callbacks ---------------------------------------------------------------------------

        // При изменение размера окна
        std::function<void(int, int)> callback_FramebufferSize_custom = [](int width, int height) {};
        void callback_FramebufferSize(GLFWwindow* window, int width, int height);

        // При передвижении окна
        std::function<void(int, int)> callback_WindowPos_custom = [](int xpos, int ypos) {};
        void callback_WindowPos(GLFWwindow* window, int xpos, int ypos);

        // При передвижении курсора
        std::function<void(double, double)> callback_CursorPos_custom = [](double xpos, double ypos) {};
        void callback_CursorPos(GLFWwindow* window, double xpos, double ypos);

        // ---------------------------------------------------------------------------------------------

    private:
        GLFWwindow* window = nullptr;

        // Window
        std::string id;
        std::string title = "Window";

        glm::ivec2 window_size = glm::ivec2(800, 600);
        glm::ivec2 window_position;

        uint32_t frame_count;

        float time;
        float delta_time;

        uint16_t fps_target = 60;
        float fps_target_ms;
        float fps;

        // Mouse
        glm::ivec2 mouse_position;
    };
    // Segment Callbacks -------------------------------------------------------

    // Глобальные статические callback для обращения к классовым callback
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    // -------------------------------------------------------------------------
};

#endif // NONAME24_INITTOOLS_INITWINDOW_H
