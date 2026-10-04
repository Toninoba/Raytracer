//
// Created by tobi on 01.10.26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Intersections.h"
#include "Material.h"
#include "Vec.h"


class Ray;

using Vec4f = Vec<float, 4>;

class Sphere {
public:
    explicit Sphere() = default;

    [[nodiscard]] float getRadius() const {
        return _radius;
    }

    [[nodiscard]] Vec<float, 4> getOrigin() const {
        return _origin;
    }

    [[nodiscard]] const Matrix<float, 4, 4> &getTransform() const {
        return _transform;
    }

    [[nodiscard]] Material& getMaterial() {
        return _material;
    }

    [[nodiscard]] const Material& getMaterial() const {
        return _material;
    }

    void setMaterial(const Material &material) {
        _material = material;
    }

    void setTransform(const Matrix<float, 4, 4> &newTransform) {
        _transform = newTransform;
        _inverseTransform = newTransform.inverse();
    }

    [[nodiscard]] Vec4f normalAt(const Vec4f &point) const;

    [[nodiscard]] Intersections intersect(const Ray &ray) const;

    bool operator==(const Sphere &other) const {
        return _transform == other._transform
               && _radius == other._radius
               && _origin == other._origin
               && _material == other._material;
    }

private:
    float _radius = 1;
    Matrix<float, 4, 4> _transform = Matrix<float, 4, 4>::identity();
    Matrix<float, 4, 4> _inverseTransform = Matrix<float, 4, 4>::identity();

    Vec4f _origin = Vec4f(0, 0, 0, 1);

    Material _material;
};


#endif //RAYTRACER_SPHERE_H
