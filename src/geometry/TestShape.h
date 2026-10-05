//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_TESTSHAPE_H
#define RAYTRACER_TESTSHAPE_H
#include "Shape.h"


class TestShape : public Shape {
public:



private:
    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;


};


#endif //RAYTRACER_TESTSHAPE_H
