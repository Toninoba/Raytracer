//
// Created by tobi on 29.09.26.
//

#include "Ray.h"


Ray Ray::transform(const Matrix<float, 4, 4> &transformation) const {

    Vec<float, 4> transformedOrigin = transformation * _origin;
    Vec<float, 4> transformedDirection = transformation * _direction;

    return {transformedOrigin, transformedDirection};
}
