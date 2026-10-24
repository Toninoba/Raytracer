//
// Created by tobi on 29.09.26.
//

#include <atomic>
#include <thread>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <filesystem>

#include "Camera.h"
#include "MatrixTransformations.h"
#include "Sphere.h"
#include "ThreadPool.h"
#include "windowRenderer.h"
#include "World.h"
#include "Constants.h"
#include "WorldBuilder.h"

namespace fs = std::filesystem;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int CANVAS_WIDTH = 1920;
constexpr int CANVAS_HEIGHT = 1080;

static unsigned int NUM_THREADS = std::thread::hardware_concurrency();

constexpr int TARGET_FPS = 30;
constexpr int FRAME_DELAY = 1000 / TARGET_FPS;


int main(int argc, char* argv[]) {

    // Pixel buffer
    std::vector<uint32_t> pixels(CANVAS_WIDTH * CANVAS_HEIGHT, 0xFF000000);

    // Create world and camera through json
    const fs::path scenePath{argv[1]};

    if (!fs::exists(scenePath) || !fs::is_regular_file(scenePath)) {
        std::cerr << "Invalid scene file: " << scenePath << '\n';
        return 1;
    }

    WorldWithCamera wc = WorldBuilder::buildWorld(scenePath);

    std::mutex pixelMutex;
    std::atomic<bool> renderFinished = false;

    std::thread raytracerThread = startBackgroundRendering(wc.camera, wc.world, pixels, pixelMutex, renderFinished, NUM_THREADS);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error when initialising SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Raytracer", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Error while creating window and renderer: %s", SDL_GetError());
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, CANVAS_WIDTH, CANVAS_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_Texture* canvas_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        CANVAS_WIDTH,
        CANVAS_HEIGHT);

    SDL_SetTextureScaleMode(canvas_texture, SDL_SCALEMODE_NEAREST);



    bool running = true;
    SDL_Event event;

    while (running) {
        uint64_t frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }


        {
            std::lock_guard<std::mutex> lock(pixelMutex);
            SDL_UpdateTexture(canvas_texture, nullptr, pixels.data(), CANVAS_WIDTH * sizeof(uint32_t));
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, canvas_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        uint64_t frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) SDL_Delay(FRAME_DELAY - frameTime);
    }


    raytracerThread.join();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}