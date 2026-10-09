//
// Created by tobi on 02.10.26.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <memory>

#include "Color.h"
#include "Pattern.h"


class Material {
public:
    Color color = Color(1, 1, 1);
    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;
    float reflective = 0.0f;
    float transparency = 0.0f;
    float refractiveIndex = 1.0f;

    std::shared_ptr<Pattern> pattern = nullptr;

    Material() = default;

    Material(const Color &color,
        const float ambient,
        const float diffuse,
        const float specular,
        const float shininess,
        const float reflective,
        const float transparency,
        const float refractiveIndex
        ) :
        color(color),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess),
        reflective(reflective),
        transparency(transparency),
        refractiveIndex(refractiveIndex){}

    bool operator==(const Material &other) const {
        return color == other.color
               && floats_equal(ambient, other.ambient)
               && floats_equal(diffuse, other.diffuse)
               && floats_equal(specular, other.specular)
               && floats_equal(shininess, other.shininess)
               && floats_equal(reflective, other.reflective)
               && floats_equal(transparency, other.transparency)
               && floats_equal(refractiveIndex, other.refractiveIndex);
    }
};


#endif //RAYTRACER_MATERIAL_H
