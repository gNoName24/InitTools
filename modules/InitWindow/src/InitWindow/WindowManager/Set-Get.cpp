// Namespace InitWindow -> Segment Set-Get
#include <InitTools/InitWindow.hpp>

namespace InitWindow {
    // - Window

    // id
    const std::string& WindowManager::get_id() const {
        return id;
    }

    // title
    void WindowManager::set_title(const std::string& title) {
        this->title = title;
        glfwSetWindowTitle(window, this->title.c_str());
    }
    const std::string& WindowManager::get_title() const {
        return title;
    }

    // window_size
    void WindowManager::set_window_size(const glm::ivec2& window_size) {
        this->window_size = window_size;
    };
    const glm::ivec2& WindowManager::get_window_size() const {
        return window_size;
    };

    // window_position
    void WindowManager::set_window_position(const glm::ivec2& window_position) {
        this->window_position = window_position;
    };
    const glm::ivec2& WindowManager::get_window_position() const {
        return window_position;
    };

    // frame_count
    const uint32_t& WindowManager::get_frame_count() const {
        return frame_count;
    }

    // time
    const float& WindowManager::get_time() const {
        return time;
    }

    // delta_time
    const float& WindowManager::get_delta_time() const {
        return delta_time;
    }

    // fps_target
    void WindowManager::set_fps_target(const uint16_t& fps_target) {
        this->fps_target = fps_target;
    }
    const uint16_t& WindowManager::get_fps_target() const {
        return fps_target;
    }

    // fps_target_ms
    const float& WindowManager::get_fps_target_ms() const {
        return fps_target_ms;
    }

    // fps
    const float& WindowManager::get_fps() const {
        return fps;
    }

    // - Mouse

    // mouse_position
    void WindowManager::set_mouse_position(const glm::ivec2& mouse_position) {
        this->mouse_position = mouse_position;
    }
    const glm::ivec2& WindowManager::get_mouse_position() const {
        return mouse_position;
    }

};
