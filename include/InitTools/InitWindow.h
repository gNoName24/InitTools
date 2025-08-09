/**
 * @defgroup InitWindow
 * \~Russian
 *     @brief Модуль InitWindow
 * \~English
 *     @brief Module InitWindow
 */
/**
 * @file InitWindow.h
 * \~Russian
 *     @brief Модуль InitWindow
 * \~English
 *     @brief Module InitWindow
 */
#ifndef NONAME24_INITTOOLS_INITWINDOW_H
#define NONAME24_INITTOOLS_INITWINDOW_H

// C++ зависимости
#include <string>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <functional>

// Библиотечные зависимости
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Модульные зависимости
// #include <InitTools/InitTools.h> <- В .cpp

/** @ingroup InitWindow
 * \~Russian
 *     @brief Модуль InitWindow
 * \~English
 *     @brief Module InitWindow
 */
namespace InitWindow {
    /** @addtogroup InitWindow
     *  @{
     */
    
    /**
     * \~Russian
     *     @brief Класс окна
     * \~English
     *     @brief Window class
     */ 
    class InitWindow_WindowClass {
    public:
        GLFWwindow* window;
        std::string selfID;
        
        // Window
        /**
         *  \~Russian
         *      @brief Размер окна
         *      @details Обновляется в framebuffer_size_callback.
         */
        glm::ivec2 window_size = glm::ivec2(800, 600);
        /**
         *  \~Russian
         *      @brief Позиция окна на экране
         *      @details Обновляется в window_pos_callback.
         */
        glm::ivec2 window_position = glm::ivec2(0, 0);

        // Mouse
        /**
         *  \~Russian
         *      @brief Позиция курсора в окне
         *      @details Обновляется в cursor_position_callback.
         */
        glm::ivec2 mouse_position = glm::ivec2(0, 0);

        // Frame
        /**
         *  \~Russian
         *      @brief Общее количество кадров в процессе отрисовки окна
         */
        long frame_count = 0;

        /**
         *  \~Russian
         *      @brief Инициализация окна
         *      @details Вызывается автоматически при newWindow().
         */
        void initWindow();

        /**
         *  \~Russian
         *      @brief Обновление классовых переменных
         *      @details Вызывается автоматически в потоке рендера.
         */
        void update(); // Вызывать при каждом кадре цикла

        // render_thread
        /**
         *  \~Russian
         *      @brief Запущен ли поток рендера
         */
        std::atomic<bool> render_thread_running = true;
        /**
         *  \~Russian
         *      
         */
        std::atomic<int> render_thread_sleep_milliseconds = 8;
        /**
         *  \~Russian
         *      @brief Поток рендера
         */
        std::thread render_thread;

        /**
         *  \~Russian
         *      @brief Запуск рендера в отдельном потоке
         *      @param[in] renderCallback Основной код рендера, который будет вызываться каждый кадр окна
         */
        void render_thread_start(std::function<void()> renderCallback);
        /**
         *  \~Russian
         *      @brief Остановка потока рендера
         */
        void render_thread_stop();

        /**
         *  \~Russian
         *      @brief Запуск бесконечного цикла для обновления событий
         *      @details Нужен для того, чтобы потоку рендера отправлялись события.
         */
        void startWhile();

        /**
         *  \~Russian
         *      @brief Получение название окна
         *      @return Название окна
         */
        std::string getTitle();
        /**
         *  \~Russian
         *      @brief Установка названия окна
         *      @param[in] title Новое название окна
         */
        void setTitle(std::string title);

        // Callbacks

        // При изменение размера окна
        std::function<void(int, int)> callback_FramebufferSize_custom = [](int width, int height) {};
        /**
         *  \~Russian
         *      @brief Обработчик вызова framebuffer_size
         *      @details Вызывается при изменении размера окна.
         *  \~English
         *      @brief framebuffer_size callback
         *      @details Called when the window size changes.
         */
        void callback_FramebufferSize(GLFWwindow* window, int width, int height);

        // При передвижении окна
        std::function<void(int, int)> callback_WindowPos_custom = [](int xpos, int ypos) {};
        /**
         *  \~Russian
         *      @brief Обработчик вызова window_pos
         *      @details Вызывается при изменении позиции окна на экране.
         */
        void callback_WindowPos(GLFWwindow* window, int xpos, int ypos);

        // При передвижении курсора
        std::function<void(double, double)> callback_CursorPos_custom = [](double xpos, double ypos) {};
        /**
         *  \~Russian
         *      @brief Обработчик вызова cursor_pos
         *      @details Вызывается при изменении позиции курсора.
         */
        void callback_CursorPos(GLFWwindow* window, double xpos, double ypos);
    };

    // Статические события GLFW для использования windowEvent в классе
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    
    /**
     *  \~Russian
     *      @brief Версия OpenGL (Мажор)
     *  \~English
     *      @brief OpenGL version (Major)
     */
    extern int opengl_version_major;
    /**
     *  \~Russian
     *      @brief Версия OpenGL (Минор)
     *  \~English
     *      @brief OpenGL version (Minor)
     */
    extern int opengl_version_minor;

    /**
     *  \~Russian
     *      @brief Карта зарегистрированных окон
     *  \~English
     *      @brief Registered windows map
     */
    extern std::unordered_map<std::string, InitWindow_WindowClass> windows;

    /**
     *  \~Russian
     *      @brief Инициализация GLFW
     *  \~English
     *      @brief GLFW initialization
     */
    void initGLFW();
    /**
     *  \~Russian
     *      @brief Инициализация GLAD
     *      @details При создании окна через newWindow() инициализировать GLAD не обязательно.
     *  \~English
     *      @brief GLAD initialization
     *      @details When creating a window using newWindow(), it is not necessary to initialize GLAD.
     */
    void initGLAD();
    /**
     *  \~Russian
     *      @brief Создание нового окна
     *      @param[in] id Идентификатор окна в windows
     *  \~English
     *      @brief Creating a new window
     *      @param[in] id Window identifier in windows
     */
    void newWindow(std::string id);
    /// @}
 };

#endif // NONAME24_INITTOOLS_INITWINDOW_H
