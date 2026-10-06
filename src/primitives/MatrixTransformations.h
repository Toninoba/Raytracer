//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_MATRIX_TRANSFORMATIONS_H
#define RAYTRACER_MATRIX_TRANSFORMATIONS_H

#include "Matrix.h"
#include "Vec.h"

namespace tfn {

    Matrix<float, 4, 4> translate (float x, float y, float z);
    Matrix<float, 4, 4> scaling(float x, float y, float z);
    Matrix<float, 4, 4> rotateX(float r);
    Matrix<float, 4, 4> rotateY(float r);
    Matrix<float, 4, 4> rotateZ(float r);
    Matrix<float, 4, 4> shearing(float xy, float xz, float yx, float yz, float zx, float zy);
    Matrix<float, 4, 4> viewTransform(const Vec<float, 4>& from, const Vec<float, 4>& to, const Vec<float, 4>& up);



}

#endif //RAYTRACER_MATRIX_TRANSFORMATIONS_H
