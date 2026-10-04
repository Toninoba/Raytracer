//
// Created by tobi on 29.09.26.
//


#include <MatrixTransformations.h>


Matrix<float, 4, 4> tfn::translate(const float x, const float y, const float z) {
    return Matrix<float, 4, 4>{
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::scaling(const float x, const float y, const float z) {
    return Matrix<float, 4, 4>{
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::rotateX(const float r) {
    return Matrix<float, 4, 4>{
        1, 0, 0, 0,
        0, cosf(r), -sinf(r), 0,
        0, sinf(r), cosf(r), 0,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::rotateY(const float r) {
    return Matrix<float, 4, 4>{
        cosf(r), 0, sinf(r), 0,
        0, 1, 0, 0,
        -sinf(r), 0, cosf(r), 0,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::rotateZ(const float r) {
    return Matrix<float, 4, 4>{
        cosf(r), -sinf(r), 0, 0,
        sinf(r), cosf(r), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy) {
    return Matrix<float, 4, 4>{
        1, xy, xz, 0,
        yx, 1, yz, 0,
        zx, zy, 1, 0,
        0, 0, 0, 1
    };
}

Matrix<float, 4, 4> tfn::viewTransform(const Vec<float, 4>& from, const Vec<float, 4>& to, const Vec<float, 4>& up) {

    const Vec<float, 4> forward = (to - from).normalize();
    const Vec<float, 4> left = forward.cross(up.normalize());

    const Vec<float, 4> trueUp = left.cross(forward);

    const Matrix<float, 4, 4> orientation(
        left[0], left[1], left[2], 0,
        trueUp[0], trueUp[1], trueUp[2], 0,
        -forward[0], -forward[1], -forward[2], 0,
        0, 0, 0, 1
    );

    return orientation * translate(-from[0], -from[1], -from[2]);
}