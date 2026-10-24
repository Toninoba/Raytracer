//
// Created by tobi on 05.10.26.
//

#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H
#include "Shape.h"
#include <utility>


class Cube : public Shape{


    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;
    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;

    static std::pair<float, float> checkAxis(float origin, float direction) ;
};


#endif //RAYTRACER_CUBE_H
