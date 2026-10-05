//
// Created by tobi on 05.10.26.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H
#include "Shape.h"


class Plane : public Shape{

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;

};


#endif //RAYTRACER_PLANE_H
