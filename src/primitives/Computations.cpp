//
// Created by tobi on 04.10.26.
//

#include <vector>
#include "Computations.h"


#include "Intersection.h"
#include "Intersections.h"
#include "Ray.h"
#include "Shape.h"

Computations prepareComputations(const Intersection &intersection, const Ray &ray, const Intersections& xs) {

    Computations comps;

    std::vector<const Shape*> container;

    for (const auto& i : xs) {

        if (i == intersection) {
            if (container.empty()) {
                comps.n1 = 1.0f;
            } else {
                comps.n1 = (*(container.end() - 1))->material().refractiveIndex;
            }
        }

        auto it = std::ranges::find(container, i.object);

        if (it != container.end()) {
            container.erase(it);
        }
        else {
            container.push_back(i.object);
        }

        if (i == intersection) {
            if (container.empty()) {
                comps.n2 = 1.0f;
            }
            else {
                comps.n2 = (*(container.end() - 1))->material().refractiveIndex;
            }
        }

    }







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
    comps.underPoint = comps.point - comps.normalv * SHADOW_EPSILON;

    comps.reflectv = ray.getDirection().reflect(comps.normalv);

    return comps;
}

float schlick(const Computations &comps) {

    float cos = comps.eyev.dot(comps.normalv);

    if (comps.n1 > comps.n2) {
        const float n = comps.n1 / comps.n2;
        const float sin2T = n*n * (1.0f - cos * cos);
        if (sin2T > 1.0f) {
            return 1.0f;
        }

        const float cosT = std::sqrt(1.0f - sin2T);

        cos = cosT;
    }

    const float r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2)) * ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));

    return r0 + (1.0f - r0) * std::pow(1.0f - cos, 5.0f);
}


