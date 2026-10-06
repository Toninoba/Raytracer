//
// Created by tobi on 06.10.26.
//

#include "RingPattern.h"

Color RingPattern::localPatternAt(const Vec<float, 4> &point) const {

    const float distSq = point.x() * point.x() + point.z() * point.z();


    if (static_cast<int>(std::floor(std::sqrt(distSq))) % 2 == 0) {
        return _a;
    }

    return _b;

}
