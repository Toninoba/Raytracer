//
// Created by tobi on 06.10.26.
//

#include "CheckerPattern.h"


Color CheckerPattern::localPatternAt(const Vec<float, 4> &point) const {

    const int floorSum = static_cast<int>(std::floor(point.x()) + std::floor(point.y()) + std::floor(point.z()));

    if (floorSum % 2 == 0) {
        return _a;
    }

    return _b;

}
