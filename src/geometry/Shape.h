//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H


#include "Matrix.h"
#include "Vec.h"
#include "../primitives/Material.h"

class Ray;
class Intersections;

class Shape {
protected:
    using Mat4f = Matrix<float, 4, 4>;
    using Vec4f = Vec<float, 4>;

    Mat4f _transform = Mat4f::identity();
    Mat4f _inverseTransform = Mat4f::identity().inverse();

    Material _material = Material();

public:
    virtual ~Shape() = default;

    [[nodiscard]] const Matrix<float, 4, 4> &getTransform() const {
        return _transform;
    }

    [[nodiscard]] const Matrix<float, 4, 4>& getInverseTransform() const {
        return _inverseTransform;
    }

    void setTransform(const Matrix<float, 4, 4> &newTransform) {
        _transform = newTransform;
        _inverseTransform = newTransform.inverse();
    }

    [[nodiscard]] Material& material() {
        return _material;
    }

    [[nodiscard]] const Material& material() const {
        return _material;
    }

    void setMaterial(const Material &material) {
        _material = material;
    }


    [[nodiscard]] Vec4f normalAt(const Vec4f &point) const {
        // transform point into object space
        const Vec4f objectPoint = _inverseTransform * point;

        const Vec4f objectNormal = localNormalAt(objectPoint);

        // do not normalize zero vector
        if (objectNormal == Vec4f(0,0,0,0)) return objectNormal;

        // transform normal back into world space
        Vec4f worldNormal = _inverseTransform.transpose() * objectNormal;

        // explicitly set w to 0 if calculations changed it
        worldNormal[3] = 0;

        return worldNormal.normalize();

    }

    [[nodiscard]] Intersections intersect(const Ray &ray) const;

    bool operator==(const Shape& other) const {
        return typeid(*this) == typeid(other) &&
               _transform == other._transform &&
               _material == other._material;
    }

    bool operator!=(const Shape& other) const {
        return !(*this == other);
    }

private:

    [[nodiscard]] virtual Vec4f localNormalAt(const Vec4f &point) const = 0;
    [[nodiscard]] virtual Intersections localIntersect(const Ray& ray) const = 0;
};


#endif //RAYTRACER_SHAPE_H
