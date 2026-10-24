//
// Created by tobi on 05.10.26.
//

#include "Cone.h"
#include "Ray.h"
#include "Intersections.h"

Intersections Cone::localIntersect(const Ray &ray) const {

    Intersections xs{};

    const float a = ray.getDirection().x() * ray.getDirection().x() -
                    ray.getDirection().y() * ray.getDirection().y() +
                    ray.getDirection().z() * ray.getDirection().z();

    const float b = 2 * ray.getOrigin().x() * ray.getDirection().x() -
                    2 * ray.getOrigin().y() * ray.getDirection().y() +
                    2 * ray.getOrigin().z() * ray.getDirection().z();

    const float c = ray.getOrigin().x() * ray.getOrigin().x() -
                    ray.getOrigin().y() * ray.getOrigin().y() +
                    ray.getOrigin().z() * ray.getOrigin().z();


    if (std::abs(a) < EPSILON) {

        if (std::abs(b) < EPSILON) {
            intersectCaps(ray, xs);
            return xs;
        }

        const float t = -c / b;

        xs.add(Intersection(t, this));
        intersectCaps(ray, xs);

        return xs;
    }

    float disc = b * b - 4.0f * a * c;

    if (disc < 0.0f) {
        if (std::abs(disc) < EPSILON) {
            disc = 0.0f;
        } else {
            return xs;
        }
    }


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

Shape::Vec4f Cone::localNormalAt(const Vec4f &point) const {

    const float dist = point.x() * point.x() + point.z() * point.z();

    float currentRadiusSq = point.y() * point.y();

    if (dist < currentRadiusSq && point.y() >= _maximum - EPSILON) {
        return {0, 1, 0, 0};
    }

    if (dist < currentRadiusSq && point.y() <= _minimum + EPSILON) {
        return {0, -1, 0, 0};
    }

    float y = std::sqrt(dist);
    if (point.y() > 0) {
        y = -y;
    }

    return {point.x(), y, point.z(), 0};
}

bool Cone::checkCaps(const Ray &ray, const float t, const float y) {
    const float x = ray.getOrigin().x() + t * ray.getDirection().x();
    const float z = ray.getOrigin().z() + t * ray.getDirection().z();

    return (x * x + z * z) <= (y * y + EPSILON);
}

void Cone::intersectCaps(const Ray &ray, Intersections &xs) const {
    if (!_closed || std::abs(ray.getDirection().y()) < EPSILON) return;

    const float t1 = (_minimum - ray.getOrigin().y()) / ray.getDirection().y();
    if (checkCaps(ray, t1, _minimum)) {
        xs.add({t1, this});
    }

    const float t2 = (_maximum - ray.getOrigin().y()) / ray.getDirection().y();
    if (checkCaps(ray, t2, _maximum)) {
        xs.add({t2, this});
    }
}