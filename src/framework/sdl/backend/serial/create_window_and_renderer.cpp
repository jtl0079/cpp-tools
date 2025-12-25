
#include <cpptools/framework/sdl/backend/serial/create_window_and_renderer.h>
#include <cstdio>
#include <SDL3/SDL.h>

namespace cpptools::framework::sdl::backend::serial {

    WindowAndRenderer create_window_and_renderer() {
        WindowAndRenderer ctx{};

        ctx.window = SDL_CreateWindow(
            "[create_window_and_renderer]",
            800,
            800,
            0
        );

        if (!ctx.window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return {};
        }

        ctx.renderer = SDL_CreateRenderer(ctx.window, nullptr);
        if (!ctx.renderer) {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(ctx.window);
            return {};
        }

        return ctx;
    }

    void destroy_window_and_renderer(WindowAndRenderer& ctx) {
        if (ctx.renderer) {
            SDL_DestroyRenderer(ctx.renderer);
            ctx.renderer = nullptr;
        }

        if (ctx.window) {
            SDL_DestroyWindow(ctx.window);
            ctx.window = nullptr;
        }
    }

}