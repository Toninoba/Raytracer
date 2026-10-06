//
// Created by tobi on 06.10.26.
//

#ifndef RAYTRACER_PATTERN_H
#define RAYTRACER_PATTERN_H

#include "Color.h"


class Shape;

class Pattern {
public:
    virtual ~Pattern() = default;

    Color& a() {
        return _a;
    }

    Color& b() {
        return _b;
    }

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

    [[nodiscard]] Color patternAtShape(const Shape* shape, const Vec<float, 4>& worldPoint) const;

    [[nodiscard]] virtual Color localPatternAt(const Vec<float, 4>& point) const = 0;

protected:

    Color _a{};
    Color _b{};

    Matrix<float, 4, 4> _transform = Matrix<float, 4, 4>::identity();
    Matrix<float, 4, 4> _inverseTransform = Matrix<float, 4, 4>::identity().inverse();

};


#endif //RAYTRACER_PATTERN_H
