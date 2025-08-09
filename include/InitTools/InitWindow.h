#ifndef NONAME24_INITTOOLS_INITWINDOW_H
#define NONAME24_INITTOOLS_INITWINDOW_H

// Модуль InitTools версии v1.1.0

// Зависимости:
//      glfw 3.4
//      glad v0.1.36
//      glm 1.0.1

// Внутренние зависимости:
//      InitLogger

// Зависимости C++
#include <string>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <functional>

// Зависимости 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Модульные зависимости
// #include <InitTools/InitTools.h> <- в .cpp

namespace InitWindow {
    class InitWindowClass {
    public:
        GLFWwindow* window;
        std::string selfID;
        glm::ivec2 window_size = glm::ivec2(800, 600);
        glm::ivec2 window_position = glm::ivec2(0, 0);

        glm::ivec2 mouse_position = glm::ivec2(0, 0);

        long frame_count = 0;

        void initWindow();

        void update(); // Вызывать при каждом кадре цикла

        // render_thread
        std::atomic<bool> render_thread_running = true;
        std::atomic<int> render_thread_sleep_milliseconds = 8;
        std::thread render_thread;

        void render_thread_start(std::function<void()> renderCallback);
        void render_thread_stop();

        std::string getTitle();
        void setTitle(std::string title);

        // Callbacks

        // При изменение размера окна
        std::function<void(int, int)> callback_FramebufferSize_custom = [](int width, int height) {};
        void callback_FramebufferSize(GLFWwindow* window, int width, int height);

        // При передвижении окна
        std::function<void(int, int)> callback_WindowPos_custom = [](int xpos, int ypos) {};
        void callback_WindowPos(GLFWwindow* window, int xpos, int ypos);

        // При передвижении курсора
        std::function<void(double, double)> callback_CursorPos_custom = [](double xpos, double ypos) {};
        void callback_CursorPos(GLFWwindow* window, double xpos, double ypos);
    };

    // Статические события GLFW для использования windowEvent в классе
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    
    extern int opengl_version_major;
    extern int opengl_version_minor;
    extern std::unordered_map<std::string, InitWindowClass> Windows;

    void initGLFW();
    void initGLAD();
    void newWindow(std::string name);
};

#endif // NONAME24_INITTOOLS_INITWINDOW_H
