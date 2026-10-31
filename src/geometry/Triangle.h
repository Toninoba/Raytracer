//
// Created by tobi on 28.10.26.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H
#include "Shape.h"


class Triangle : public Shape{

public:
    Triangle() = delete;
    Triangle(const Vec4f& p1, const Vec4f& p2, const Vec4f& p3) : _p1(p1), _p2(p2), _p3(p3) {
        _e1 = _p2 - _p1;
        _e2 = _p3 - _p1;

        const Vec4f n = _e2.cross(_e1);

        _normal = n.normalize();
    }

    Vec4f& p1() {
        return _p1;
    }

    Vec4f& p2() {
        return _p2;
    }

    Vec4f& p3() {
        return _p3;
    }

    Vec4f& normal() {
        return _normal;
    }

    Vec4f& e1() {
        return _e1;
    }

    Vec4f& e2() {
        return _e2;
    }

private:

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;

    Vec4f _normal;

    Vec4f _e1;
    Vec4f _e2;

    Vec4f _p1;
    Vec4f _p2;
    Vec4f _p3;

};


#endif //RAYTRACER_TRIANGLE_H
