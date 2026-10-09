//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_WINDOWRENDERER_H
#define RAYTRACER_WINDOWRENDERER_H
#include <thread>
#include <mutex>

#include "Camera.h"
#include "Canvas.h"

struct Chunk {
    unsigned int xStart;
    unsigned int xEnd;
    unsigned int yStart;
    unsigned int yEnd;
};

std::thread startBackgroundRendering(const Camera &camera, const World &world, std::vector<uint32_t> &pixels,
                                std::mutex &pixelMutex, std::atomic<bool> &renderFinished, unsigned int numThreads);

std::vector<Chunk> splitToChunks(const Camera &camera);

#endif //RAYTRACER_WINDOWRENDERER_H
