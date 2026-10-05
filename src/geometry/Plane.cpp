//
// Created by tobi on 05.10.26.
//

#include "Plane.h"

Intersections Plane::localIntersect(const Ray &ray) const {
    if (std::abs(ray.getDirection().y()) < EPSILON) {
        return {};
    }

    const float t = -ray.getOrigin().y() / ray.getDirection().y();

    return {Intersection(t, this)};
}

Shape::Vec4f Plane::localNormalAt(const Vec4f &point) const {
    return {0, 1, 0, 0};
}
