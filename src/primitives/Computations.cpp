//
// Created by tobi on 04.10.26.
//

#include "Computations.h"

#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"

Computations prepareComputations(const Intersection &intersection, const Ray &ray) {
    Computations comps;

    comps.t = intersection.t;
    comps.object = intersection.object;

    comps.point = ray.position(comps.t);
    comps.eyev = -ray.getDirection();
    comps.normalv = comps.object->normalAt(comps.point);

    if (comps.normalv.dot(comps.eyev) < 0.0f) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    }

    comps.overPoint = comps.point + comps.normalv * SHADOW_EPSILON;

    return comps;
}


