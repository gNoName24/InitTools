// Namespace InitWindow
#include <InitTools/InitWindow.h>

// C++
#include <stdexcept>

namespace InitWindow {
    // Вспомогательные функции, опционально реализуемые в другие модулях

    // extern_function_log
    std::function<void(
        const std::string& msg,
        const std::string& level,
        const std::string& file_name,
        int line,
        const std::string& function_name
    )> extern_function_log = [](const std::string& msg, const std::string& level, const std::string& file_name, int line, const std::string& function_name) {};

    // =================================================================

    uint8_t opengl_target_version_major = 3;
    uint8_t opengl_target_version_minor = 3;

    bool initialized_GLFW = false;
    void initialization_GLFW() {
        INITWINDOW_log("GLFW initialization", "debug");
        if(!glfwInit()) {
            INITWINDOW_log("Failed to initialize GLFW", "error");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_target_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_target_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        INITWINDOW_log("GLFW initialization success", "debug");
        initialized_GLFW = true;
    }

    bool initialized_GLAD = false;
    void initialization_GLAD() {
        INITWINDOW_log("GLAD initialization", "debug");
        if(!gladLoadGL()) {
            INITWINDOW_log("Failed to initialize GLAD", "error");
            throw std::runtime_error("Failed to initialize GLAD");
        }
        INITWINDOW_log("GLAD initialization success", "debug");
        initialized_GLAD = true;
    }

    std::unordered_map<std::string, WindowManager> windows;

    void window_new(const std::string& id) {
        INITWINDOW_log("Create new window / ID: " + id, "debug");
        auto result = windows.emplace(id, id);
        if(result.second) {
            INITWINDOW_log("The window " + id + " created successfully", "debug");
        } else {
            INITWINDOW_log("The window " + id + " already exists", "error");
        }
    }
    WindowManager& window_new(const std::string& id, bool need_return) {
        window_new(id);
        return windows.at(id);
    }
};
