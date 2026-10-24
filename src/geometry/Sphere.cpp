//
// Created by tobi on 01.10.26.
//

#include "Sphere.h"
#include "Shape.h"

#include "Ray.h"
#include "Intersections.h"



Intersections Sphere::localIntersect(const Ray &ray) const {


    const Vec4f sphereToRay = ray.getOrigin() - _origin;

    const float a = ray.getDirection().dot(ray.getDirection());
    const float b = 2 * ray.getDirection().dot(sphereToRay);
    const float c = sphereToRay.dot(sphereToRay) - 1;

    const float discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0) {
        return {};
    }

    const float t1 = (-b - sqrtf(discriminant)) / (2 * a);
    const float t2 = (-b + sqrtf(discriminant)) / (2 * a);

    return Intersections{Intersection(t1, this), Intersection(t2, this)};
}


Shape::Vec4f Sphere::localNormalAt(const Vec4f &point) const {

    const Vec4f objectNormal = point - _origin;
    return objectNormal;
}
