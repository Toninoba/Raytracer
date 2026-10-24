//
// Created by tobi on 01.10.26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "Vec.h"

class Ray;

class Sphere : public Shape{
public:

    explicit Sphere() = default;

    static Sphere glassSphere() {
        Sphere s{};

        s.material().transparency = 1.0f;
        s.material().refractiveIndex = 1.5f;

        return s;
    }

    [[nodiscard]] float getRadius() const {
        return _radius;
    }

    [[nodiscard]] Vec<float, 4> getOrigin() const {
        return _origin;
    }
private:

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;


    float _radius = 1;
    Vec4f _origin = Vec4f(0, 0, 0, 1);
};


#endif //RAYTRACER_SPHERE_H
