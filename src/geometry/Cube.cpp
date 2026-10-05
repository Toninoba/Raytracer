//
// Created by tobi on 05.10.26.
//

#include "Cube.h"

Intersections Cube::localIntersect(const Ray &ray) const {
    auto xt = checkAxis(ray.getOrigin().x(), ray.getDirection().x());
    auto yt = checkAxis(ray.getOrigin().y(), ray.getDirection().y());
    auto zt = checkAxis(ray.getOrigin().z(), ray.getDirection().z());

    const float tmin = std::max(xt.first, std::max(yt.first, zt.first));
    const float tmax = std::min(xt.second, std::min(yt.second, zt.second));

    if (tmin > tmax) return {};

    return {Intersection(tmin, this), Intersection(tmax, this)};
}

Shape::Vec4f Cube::localNormalAt(const Vec4f &point) const {

    const float maxc = std::max(std::abs(point.data[0]), std::max(std::abs(point.data[1]), std::abs(point.data[2])));

    if (maxc == abs(point.data[0])) {
        return {point.data[0], 0, 0, 0};
    }

    if (maxc == abs(point.data[1])) {
        return {0, point.data[1], 0, 0};
    }

    return {0, 0, point.data[2], 0};

}

std::pair<float, float> Cube::checkAxis(const float origin, const float direction) {

    const float tminNumerator = (-1.0f - origin);
    const float tmaxNumerator = (1.0f - origin);

    float tmin{};
    float tmax{};

    if (std::abs(direction) >= EPSILON) {
        tmin = tminNumerator / direction;
        tmax = tmaxNumerator / direction;
    }
    else {
        tmin = tminNumerator * std::numeric_limits<float>::infinity();
        tmax = tmaxNumerator * std::numeric_limits<float>::infinity();
    }

    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }

    return std::make_pair(tmin, tmax);
}
