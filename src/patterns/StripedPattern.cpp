//
// Created by tobi on 06.10.26.
//

#include "StripedPattern.h"


Color StripedPattern::localPatternAt(const Vec<float, 4> &point) const {
    if (static_cast<int>(std::floor(point.x())) % 2 == 0) {
        return _a;
    }

    return _b;
}
