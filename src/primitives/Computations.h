//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_COMPUTATIONS_H
#define RAYTRACER_COMPUTATIONS_H


#include "Vec.h"

class Intersections;
class Intersection;
class Ray;
class Shape;

struct Computations {
    float t = 0.0f;
    const Shape* object = nullptr;
    Vec<float, 4> point{};
    Vec<float, 4> overPoint{};
    Vec<float, 4> underPoint{};
    Vec<float, 4> eyev{};
    Vec<float, 4> normalv{};
    Vec<float, 4> reflectv{};
    bool inside = false;

    float n1 = 0.0f;
    float n2 = 0.0f;
};


Computations prepareComputations(const Intersection& intersection, const Ray& ray, const Intersections& xs);


#endif //RAYTRACER_COMPUTATIONS_H
