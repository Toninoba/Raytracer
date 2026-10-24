//
// Created by tobi on 08.10.26.
//

#include "TestPattern.h"

Color TestPattern::localPatternAt(const Vec<float, 4> &point) const {
    return {point.x(), point.y(), point.z()};
}
