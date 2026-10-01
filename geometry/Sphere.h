//
// Created by tobi on 01.10.26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Intersections.h"
#include "Vec.h"



class Ray;

using Vec4f = Vec<float, 4>;

class Sphere {
public:

    explicit Sphere() = default;

    [[nodiscard]] float getRadius() const {
        return _radius;
    }

    [[nodiscard]] Vec<float, 4> getOrigin() const {
        return _origin;
    }

    [[nodiscard]] Intersections intersect(const Ray& ray) const;

private:

    float _radius = 1;
    Vec4f _origin = Vec4f(0, 0, 0, 1);
};


#endif //RAYTRACER_SPHERE_H
