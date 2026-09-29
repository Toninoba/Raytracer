//
// Created by tobi on 29.09.26.
//

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int CANVAS_WIDTH = 30;
constexpr int CANVAS_HEIGHT = 20;

int main(int argc, char* argv[]) {

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

    // Pixel buffer
    std::vector<uint32_t> pixels(CANVAS_WIDTH * CANVAS_HEIGHT, 0xFF000000);

    bool running = true;
    SDL_Event event;

    int draw_x = 0;
    int draw_y = 0;

    while (running) {

        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // --- UPDATE PHASE ---
        // Wir zeichnen pro Frame 100 Pixel, um den Prozess sichtbar zu machen
        for (int i = 0; i < 100; ++i) {
            if (draw_y < CANVAS_HEIGHT) {
                // Index im 1D-Array berechnen (Y * Breite + X)
                int index = draw_y * CANVAS_WIDTH + draw_x;

                // Erzeuge einen Farbverlauf basierend auf X und Y Koordinaten (0xFF = Alpha)
                uint8_t red = (draw_x * 255) / CANVAS_WIDTH;
                uint8_t green = (draw_y * 255) / CANVAS_HEIGHT;
                uint8_t blue = 128;

                // Packe die Werte in einen 32-Bit Integer (ARGB)
                pixels[index] = (0xFF << 24) | (red << 16) | (green << 8) | blue;

                // Nächster Pixel
                draw_x++;
                if (draw_x >= CANVAS_WIDTH) {
                    draw_x = 0;
                    draw_y++;
                }
            }
        }

        // --- RENDER PHASE ---

        // Update texture
        SDL_UpdateTexture(canvas_texture, nullptr, pixels.data(), CANVAS_WIDTH * sizeof(uint32_t));

        // clear screen with black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw texture to screen
        SDL_RenderTexture(renderer, canvas_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);


    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}