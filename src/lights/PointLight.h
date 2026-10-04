//
// Created by tobi on 02.10.26.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H
#include "Color.h"
#include "Material.h"

#include "Vec.h"


class PointLight {
public:
    Vec<float, 4> position;
    Color intensity;

    PointLight(const Vec<float, 4>& position, const Color& intensity) : position(position), intensity(intensity) {}

    Color lighting(const Material& material, const Vec<float, 4>& point, const Vec<float, 4>& eyev, const Vec<float, 4>& normalv);

    bool operator==(const PointLight &other) const {
        return position == other.position && intensity == other.intensity;
    }
};


#endif //RAYTRACER_POINTLIGHT_H
