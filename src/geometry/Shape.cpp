//
// Created by tobi on 06.10.26.
//

#include "Shape.h"
#include "Ray.h"
#include "Intersections.h"

Intersections Shape::intersect(const Ray &ray) const {
    // transform ray into object space
    Ray transformedRay = ray.transform(_inverseTransform);

    return localIntersect(transformedRay);
}
