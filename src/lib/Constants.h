//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H
#include <numbers>


static constexpr float EPSILON = 1e-4f;
static constexpr float SHADOW_EPSILON = 0.09f;
static constexpr float PI = std::numbers::pi_v<float>;
static constexpr float PI_2 = PI / 2.0f;
static constexpr float PI_4 = PI / 4.0f;

constexpr bool floats_equal(const float a, const float b) {
    const float diff = a - b;
    return (diff < 0.0f ? -diff : diff) < EPSILON;
}


#endif //RAYTRACER_CONSTANTS_H
