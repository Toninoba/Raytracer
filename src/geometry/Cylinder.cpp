//
// Created by tobi on 05.10.26.
//

#include "Cylinder.h"
#include "Ray.h"
#include "Intersections.h"


Intersections Cylinder::localIntersect(const Ray &ray) const {

    Intersections xs{};

    const float a = ray.getDirection().x() * ray.getDirection().x() + ray.getDirection().z() * ray.getDirection().z();

    if (std::abs(a) < EPSILON) {
        intersectCaps(ray, xs);
        return xs;
    }

    const float b = 2 * ray.getOrigin().x() * ray.getDirection().x() +
        2 * ray.getOrigin().z() * ray.getDirection().z();

    const float c = ray.getOrigin().x() * ray.getOrigin().x() + ray.getOrigin().z() * ray.getOrigin().z() - 1;

    const float disc = b * b - 4 * a * c;

    if (disc < 0) return {};

    float t0 = (-b - std::sqrt(disc)) / (2 * a);
    float t1 = (-b + std::sqrt(disc)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);



    const float y0 = ray.getOrigin().y() + t0 * ray.getDirection().y();
    if (_minimum < y0 && y0 < _maximum) {
        xs.add({t0, this});
    }

    const float y1 = ray.getOrigin().y() + t1 * ray.getDirection().y();
    if (_minimum < y1 && y1 < _maximum) {
        xs.add({t1, this});
    }

    intersectCaps(ray, xs);

    return xs;
}

Shape::Vec4f Cylinder::localNormalAt(const Vec4f &point) const {

    const float dist = point.data[0] * point.data[0] + point.data[2] * point.data[2];

    if (dist < 1.0f && point.data[1] >= _maximum - EPSILON) {
        return {0, 1, 0, 0};
    }

    if (dist < 1.0f && point.data[1] <= _minimum + EPSILON) {
        return {0, -1, 0, 0};
    }

    return {point.data[0], 0, point.data[2], 0};
}

bool Cylinder::checkCaps(const Ray &ray, const float t) {
    const float x = ray.getOrigin().x() + t * ray.getDirection().x();
    const float z = ray.getOrigin().z() + t * ray.getDirection().z();

    return (1.0f - (x * x + z * z)) >= (0 - EPSILON);
}

void Cylinder::intersectCaps(const Ray &ray, Intersections &xs) const {
    if (!_closed || std::abs(ray.getDirection().y()) < EPSILON) return;

    const float t1 = (_minimum - ray.getOrigin().y()) / ray.getDirection().y();
    if (checkCaps(ray, t1)) {
        xs.add({t1, this});
    }

    const float t2 = (_maximum - ray.getOrigin().y()) / ray.getDirection().y();
    if (checkCaps(ray, t2)) {
        xs.add({t2, this});
    }
}
