//
// Created by tobi on 29.09.26.
//

#include <atomic>
#include <thread>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Camera.h"
#include "ThreadPool.h"
#include "windowRenderer.h"
#include "World.h"


constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int CANVAS_WIDTH = 1920;
constexpr int CANVAS_HEIGHT = 1080;

static unsigned int NUM_THREADS = std::thread::hardware_concurrency();

constexpr int TARGET_FPS = 30;
constexpr int FRAME_DELAY = 1000 / TARGET_FPS;

World setupTestWorld() {
    auto floor = std::make_unique<Sphere>();
    floor->setTransform(tfn::scaling(10.0f, 0.01f, 10.0f));
    floor->setMaterial(Material());
    floor->getMaterial().color = Color(1.0f, 0.9f, 0.9f);
    floor->getMaterial().specular = 0.0f;

    auto leftWall = std::make_unique<Sphere>();
    leftWall->setTransform(tfn::translate(0, 0, 5) * tfn::rotateY(-M_PI/4) * tfn::rotateX(M_PI/2) * tfn::scaling(10, 0.01, 10));
    leftWall->getMaterial() = floor->getMaterial();

    auto rightWall = std::make_unique<Sphere>();
    rightWall->setTransform(tfn::translate(0, 0, 5) * tfn::rotateY(M_PI/4) * tfn::rotateX(M_PI/2) * tfn::scaling(10, -0.01, 10));
    rightWall->getMaterial() = floor->getMaterial();

    auto middle = std::make_unique<Sphere>();
    middle->setTransform(tfn::translate(-0.5, 1, 0.5));
    middle->setMaterial(Material());
    middle->getMaterial().color = Color(0.1, 1, 0.5);
    middle->getMaterial().diffuse = 0.7f;
    middle->getMaterial().specular = 0.3f;

    auto right = std::make_unique<Sphere>();
    right->setTransform(tfn::translate(1.5f, 0.5f, -0.5f) * tfn::scaling(0.5f, 0.5f, 0.5f));
    right->setMaterial(Material());
    right->getMaterial().color = Color(0.5, 1, 0.1);
    right->getMaterial().diffuse = 0.7;
    right->getMaterial().specular = 0.3;

    auto left = std::make_unique<Sphere>();
    left->setTransform(tfn::translate(-1.5, 0.33, -0.75) * tfn::scaling(0.33, 0.33, 0.33));
    left->setMaterial(Material());
    left->getMaterial().color = Color(1, 0.8, 0.1);
    left->getMaterial().diffuse = 0.7;
    left->getMaterial().specular = 0.3;


    auto light = std::make_unique<PointLight>(Vec<float, 4>(-10, 10, -10, 1), Color(1,1,1));



    World w;

    w.addObject(std::move(floor));
    w.addObject(std::move(leftWall));
    w.addObject(std::move(rightWall));
    w.addObject(std::move(left));
    w.addObject(std::move(right));
    w.addObject(std::move(middle));

    w.addLight(std::move(light));

    return w;

}


int main(int argc, char* argv[]) {

    // Pixel buffer
    std::vector<uint32_t> pixels(CANVAS_WIDTH * CANVAS_HEIGHT, 0xFF000000);

    // Create world and camera
    Camera c(CANVAS_WIDTH, CANVAS_HEIGHT, M_PI/3);
    c.setViewTransformation(tfn::viewTransform(
        Vec<float, 4>(0, 1.5, -5, 1),
        Vec<float, 4>(0, 1, 0, 1),
        Vec<float, 4>(0, 1, 0, 0)
    ));

    World w = setupTestWorld();

    std::mutex pixelMutex;
    std::atomic<bool> renderFinished = false;

    std::thread raytracerThread = startBackgroundRendering(c, w, pixels, pixelMutex, renderFinished, NUM_THREADS);

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