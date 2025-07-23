#ifndef NONAME24_INITTOOLS_INIT_WINDOW_H
#define NONAME24_INITTOOLS_INIT_WINDOW_H

// Зависимости:
//      glfw 3.4
//      glad v0.1.36
//      glm 1.0.1

#include <InitTools/InitLogger.h>

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace InitWindow {
    class InitWindowClass {
    public:
        GLFWwindow* window;
        int width = 800;
        int height = 600;

        long frame_count = 0;

        void initWindow();

        // Вызывать при каждом кадре цикла
        void update() {
            frame_count++;
        }

        std::string getTitle();
        void setTitle(std::string title);
    };
    
    extern int opengl_version_major;
    extern int opengl_version_minor;
    extern std::unordered_map<std::string, InitWindowClass> Windows;

    void initGLFW();
    void initGLAD();
    void newWindow(std::string name);
};

#endif // NONAME24_INITTOOLS_INIT_WINDOW_H