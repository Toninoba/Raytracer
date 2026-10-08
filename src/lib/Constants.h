//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H
#include <cmath>


static constexpr float EPSILON = 1e-4f;
static constexpr float SHADOW_EPSILON = 1e-4f;

static constexpr float VACUUM = 1.0f;
static constexpr float AIR = 1.00029f;
static constexpr float WATER = 1.333f;
static constexpr float GLASS = 1.52f;
static constexpr float DIAMOND = 2.417f;

constexpr bool floats_equal(const float a, const float b) {
    return std::fabs(a - b) < EPSILON;
}


#endif //RAYTRACER_CONSTANTS_H
