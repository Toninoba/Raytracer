//
// Created by tobi on 28.10.26.
//

#include "Triangle.h"

#include "Intersections.h"
#include "Ray.h"

Intersections Triangle::localIntersect(const Ray &ray) const {
    Intersections xs{};

    const Vec4f dirCrossE2 = ray.getDirection().cross(_e2);
    const float determinant = _e1.dot(dirCrossE2);

    if (std::abs(determinant) < EPSILON) {
        return xs;
    }

    const float f = 1.0f / determinant;

    const Vec4f p1ToOrigin = ray.getOrigin() - _p1;
    const float u = f * p1ToOrigin.dot(dirCrossE2);

    if (u < 0.0f || u > 1.0f) {
        return xs;
    }

    const Vec4f originCrossE1 = p1ToOrigin.cross(_e1);
    const float v = f * ray.getDirection().dot(originCrossE1);

    if (v < 0.0f || (u + v) > 1) {
        return xs;
    }

    const float t = f * _e2.dot(originCrossE1);

    xs.add(Intersection(t, this));

    return xs;
}

Shape::Vec4f Triangle::localNormalAt(const Vec4f &point) const {
    return _normal;
}
