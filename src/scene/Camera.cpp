//
// Created by tobi on 04.10.26.
//

#include "Camera.h"

Ray Camera::rayForPixel(const unsigned int px, const unsigned int py) const {

    const float xOffset = (static_cast<float>(px) + 0.5f) * _pixelSize;
    const float yOffset = (static_cast<float>(py) + 0.5f) * _pixelSize;

    const float worldX = _halfWidth - xOffset;
    const float worldY = _halfHeight - yOffset;

    const Vec<float, 4> pixel = _inverseViewTransformation * Vec<float, 4>(worldX, worldY, -1, 1);
    const Vec<float, 4> origin = _inverseViewTransformation * Vec<float, 4>(0, 0, 0, 1);
    const Vec<float, 4> direction = (pixel - origin).normalize();

    return {origin, direction};
}

Canvas Camera::render(const World &world) const {
    Canvas image(hsize(), vsize());

    for (std::size_t y = 0; y < _vsize - 1; ++y) {
        for (std::size_t x = 0; x < _hsize - 1; ++x) {

            Ray ray = rayForPixel(x, y);
            Color color = world.colorAt(ray);
            image.writePixel(x, y, color);

        }
    }

    return image;
}
