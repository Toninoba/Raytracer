//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "Color.h"


class Canvas {
public:

    const std::size_t WIDTH;
    const std::size_t HEIGHT;

    std::vector<Color> pixels;

    Canvas(const std::size_t width, const std::size_t height) : WIDTH(width), HEIGHT(height) {
        pixels = std::vector(WIDTH * HEIGHT, Color(0,0,0));
    }

    void writePixel(const std::size_t x, const size_t y, const Color& color) {

        const std::size_t pixelCoordinate = y * WIDTH + x;

        pixels.at(pixelCoordinate) = color;

    }

    Color pixelAt(const std::size_t x, const size_t y) const {

        const std::size_t pixelCoordinate = y * WIDTH + x;

        return pixels.at(pixelCoordinate);
    }






private:



};


#endif //RAYTRACER_CANVAS_H
