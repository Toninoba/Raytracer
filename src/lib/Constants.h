//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H
#include <numbers>


static constexpr float EPSILON = 1e-4f;
static constexpr float SHADOW_EPSILON = 1e-4f;

static constexpr float PI = std::numbers::pi_v<float>;
static constexpr float PI_2 = PI / 2.0f;
static constexpr float PI_4 = PI / 4.0f;

static constexpr float VACUUM = 1.0f;
static constexpr float AIR = 1.00029f;
static constexpr float WATER = 1.333f;
static constexpr float GLASS = 1.52f;
static constexpr float DIAMOND = 2.417f;

constexpr bool floats_equal(const float a, const float b) {
    const float diff = a - b;
    return (diff < 0.0f ? -diff : diff) < EPSILON;
}


#endif //RAYTRACER_CONSTANTS_H
