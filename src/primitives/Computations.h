//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_COMPUTATIONS_H
#define RAYTRACER_COMPUTATIONS_H

#include "Sphere.h"
#include "Vec.h"

class Intersection;
class Ray;

struct Computations {
    float t = 0.0f;
    const Sphere* object = nullptr;
    Vec<float, 4> point{};
    Vec<float, 4> overPoint{};
    Vec<float, 4> eyev{};
    Vec<float, 4> normalv{};
    bool inside = false;
};


Computations prepareComputations(const Intersection& intersection, const Ray& ray);


#endif //RAYTRACER_COMPUTATIONS_H
