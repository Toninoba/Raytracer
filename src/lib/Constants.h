//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H
#include <cmath>


static constexpr float EPSILON = 1e-4f;
static constexpr float SHADOW_EPSILON = 1e-4f;

constexpr bool floats_equal(const float a, const float b) {
    return std::fabs(a - b) < EPSILON;
}


#endif //RAYTRACER_CONSTANTS_H
