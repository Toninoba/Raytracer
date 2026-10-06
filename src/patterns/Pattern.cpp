//
// Created by tobi on 06.10.26.
//

#include "Pattern.h"
#include "Shape.h"

Color Pattern::patternAtShape(const Shape *shape, const Vec<float, 4> &worldPoint) const {
    const Vec<float, 4> objectPoint = shape->getInverseTransform() * worldPoint;
    const Vec<float, 4> patternPoint = _inverseTransform * objectPoint;

    return localPatternAt(patternPoint);
}
