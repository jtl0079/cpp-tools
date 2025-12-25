#pragma once

#include <SDL3/SDL.h>


namespace cpptools::framework::sdl::backend::serial {


    struct WindowAndRenderer {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    };

    // 创建（成功返回有效指针，失败返回 {nullptr, nullptr}）
    WindowAndRenderer create_window_and_renderer();

    // 显式销毁（由上层调用）
    void destroy_window_and_renderer(WindowAndRenderer& ctx);

}