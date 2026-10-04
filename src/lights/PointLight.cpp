//
// Created by tobi on 02.10.26.
//

#include "PointLight.h"

Color PointLight::lighting(const Material &material, const Vec<float, 4> &point, const Vec<float, 4> &eyev, const Vec<float, 4> &normalv) {

    // combine surface color with lights color
    const Color effectiveColor = material.color * intensity;

    // find the direction to the light source
    const Vec<float, 4> lightv = (position - point).normalize();

    // compute ambient contribution
    const Color ambient = effectiveColor * material.ambient;
    Color diffuse = Color(0.0f, 0.0f, 0.0f);
    Color specular = Color(0.0f, 0.0f, 0.0f);

    const float lightDotNormal = lightv.dot(normalv);

    if (lightDotNormal >= 0) {
        // compute diffuse contribution
        diffuse = effectiveColor * material.diffuse * lightDotNormal;

        const Vec<float, 4> reflectv = -lightv.reflect(normalv);
        const float reflectDotEye = reflectv.dot(eyev);

        if (reflectDotEye > 0) {

            // compute specular contribution
            const float factor = powf(reflectDotEye, material.shininess);
            specular = intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;

}
