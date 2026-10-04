//
// Created by tobi on 29.09.26.
//
#include "windowRenderer.h"
#include "ThreadPool.h"
#include <future>


std::thread startBackgroundRendering(
    const Camera& c,
    const World& w,
    std::vector<uint32_t>& pixels,
    std::mutex& pixelMutex,
    std::atomic<bool>& renderFinished,
    unsigned int numThreads)
{
    return std::thread([&c, &w, &pixels, &pixelMutex, &renderFinished, numThreads]() {

        Canvas canvas(c.hsize(), c.vsize());
        auto chunks = splitToChunks(c);
        ThreadPool pool(numThreads);
        std::vector<std::future<void>> futures;

        for (const auto& chunk : chunks) {
            futures.push_back(pool.enqueue([&c, &w, chunk, &canvas, &pixels, &pixelMutex]() {

                for (std::size_t y = chunk.yStart; y <= chunk.yEnd; ++y) {
                    for (std::size_t x = chunk.xStart; x <= chunk.xEnd; ++x) {
                        Ray ray = c.rayForPixel(x, y);
                        Color color = w.colorAt(ray);

                        uint8_t r = std::clamp(static_cast<int>(color.red() * 255), 0, 255);
                        uint8_t g = std::clamp(static_cast<int>(color.green() * 255), 0, 255);
                        uint8_t b = std::clamp(static_cast<int>(color.blue() * 255), 0, 255);
                        uint32_t argb = (0xFF << 24) | (r << 16) | (g << 8) | b;

                        std::lock_guard<std::mutex> lock(pixelMutex);
                        pixels[y * c.hsize() + x] = argb;
                    }
                }
            }));
        }

        for (auto& f : futures) { f.get(); }

        renderFinished = true;
    });
}

std::vector<Chunk> splitToChunks(const Camera& camera) {
    std::vector<Chunk> imageChunks{};

    for (std::size_t y = 0; y < camera.vsize(); y+=16) {

        // clamp yEnd to edge of screen if screen is not divisible by 16
        unsigned int yStart = y;
        unsigned int yEnd = y + 15 < camera.vsize() - 1 ? y + 15 : camera.vsize() - 1;


        for (std::size_t x = 0; x < camera.hsize(); x+=16) {

            // clamp xEnd to edge of screen if screen is not divisible by 16
            unsigned int xStart = x;
            unsigned int xEnd = x + 15 < camera.hsize() - 1 ? x + 15 : camera.hsize() - 1;

            Chunk chunk;
            chunk.xStart = xStart;
            chunk.xEnd = xEnd;
            chunk.yStart = yStart;
            chunk.yEnd = yEnd;

            imageChunks.push_back(chunk);


        }
    }

    return imageChunks;
}