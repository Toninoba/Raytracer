//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "Vec.h"


class Ray {
public:

    Ray(const Vec<float, 4>& origin, const Vec<float, 4>& direction) : _origin(origin), _direction(direction){}

    [[nodiscard]] Vec<float, 4> getOrigin() const {
        return _origin;
    }

    [[nodiscard]] Vec<float, 4> getDirection() const {
        return _direction;
    }

    [[nodiscard]] constexpr Vec<float, 4> position(const float t) const {
        return _origin + _direction * t;
    }

private:
    Vec<float, 4> _origin;
    Vec<float, 4> _direction;
};


#endif //RAYTRACER_RAY_H
