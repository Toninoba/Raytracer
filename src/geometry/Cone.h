//
// Created by tobi on 05.10.26.
//

#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H
#include "Shape.h"


class Cone : public Shape{

    float _minimum = -std::numeric_limits<float>::infinity();
    float _maximum = std::numeric_limits<float>::infinity();

    bool _closed = false;

    [[nodiscard]] Vec4f localNormalAt(const Vec4f &point) const override;
    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;

    static bool checkCaps(const Ray& ray, float t, float y) ;

    void intersectCaps(const Ray& ray, Intersections& xs) const;

public:

    [[nodiscard]] float getMinimum() const {
        return _minimum;
    }

    void setMinimum(const float minimum) {
        _minimum = minimum;
    }

    [[nodiscard]] float getMaximum() const {
        return _maximum;
    }

    void setMaximum(const float maximum) {
        _maximum = maximum;
    }

    [[nodiscard]] bool isClosed() const {
        return _closed;
    }

    void close() {
        _closed = true;
    }

    void open() {
        _closed = false;
    }


};


#endif //RAYTRACER_CONE_H
