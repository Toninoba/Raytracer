//
// Created by tobi on 02.10.26.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"
#include "../patterns/StripedPattern.h"


class Material {
public:
    Color color = Color(1, 1, 1);
    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;

    std::optional<StripedPattern> pattern = std::nullopt;

    Material() = default;

    Material(const Color &color, float ambient, float diffuse, float specular, float shininess) : color(color),
        ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {
    }

    bool operator==(const Material &other) const {
        return color == other.color
               && floats_equal(ambient, other.ambient)
               && floats_equal(diffuse, other.diffuse)
               && floats_equal(specular, other.specular)
               && floats_equal(shininess, other.shininess);
    }
};


#endif //RAYTRACER_MATERIAL_H
