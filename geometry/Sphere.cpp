//
// Created by tobi on 01.10.26.
//

#include "Sphere.h"

#include "../primitives/Ray.h"


std::vector<float> Sphere::intersect(const Ray &ray) const {
    std::vector<float> intersections;

    Vec4f sphereToRay = ray.getOrigin() - _origin;

    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2 * ray.getDirection().dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0) {
        return intersections;
    }

    intersections.emplace_back((-b - sqrtf(discriminant)) / (2 * a));
    intersections.emplace_back((-b + sqrtf(discriminant)) / (2 * a));

    return intersections;
}
