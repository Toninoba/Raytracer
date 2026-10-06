//
// Created by tobi on 06.10.26.
//

#include "GradientPattern.h"

Color GradientPattern::localPatternAt(const Vec<float, 4> &point) const {
    return _a + (_b - _a) * (point.x() - std::floor(point.x()));
}
