//
// Created by tobi on 29.09.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Vec.h"
#include "MatrixTransformations.h"

// w=1 for points
using Vec4 = Vec<float, 4>;

TEST_CASE("Multiplying by a translation matrix") {
    auto transform = tfn::translate(5, -3, 2);
    Vec4 p(-3, 4, 5, 1);
    Vec4 v(-3, 4, 5, 0);


    CHECK(transform * p == Vec4(2,1,7,1));

    CHECK(transform.inverse() * p == Vec4(-8,7,3,1));
    CHECK(transform * v == v);
}

TEST_CASE("Scaling") {
    auto transform = tfn::scaling(2, 3, 4);
    Vec4 p(-4, 6, 8, 1);
    Vec4 v(-4, 6, 8, 0);

    CHECK(transform * p == Vec4(-8,18,32,1));
    CHECK(transform * v == Vec4(-8,18,32,0));

    CHECK(transform.inverse() * v == Vec4(-2,2,2,0));
}

TEST_CASE("Rotate around x axis") {
    Vec4 p(0, 1, 0, 1);

    auto hq = tfn::rotateX(M_PI / 4);
    auto fq = tfn::rotateX(M_PI / 2);

    CHECK(hq * p == Vec4(0, sqrt(2)/2, sqrt(2)/2, 1));
    CHECK(fq * p == Vec4(0,0,1,1));

    CHECK(hq.inverse() * p == Vec4(0, sqrt(2)/2, -sqrt(2)/2, 1));
}

TEST_CASE("Rotate around y axis") {
    Vec4 p(0, 0, 1, 1);

    auto hq = tfn::rotateY(M_PI / 4);
    auto fq = tfn::rotateY(M_PI / 2);

    CHECK(hq * p == Vec4(sqrt(2)/2, 0, sqrt(2)/2, 1));
    CHECK(fq * p == Vec4(1,0,0,1));
}

TEST_CASE("Rotate around z axis") {
    Vec4 p(0, 1, 0, 1);

    auto hq = tfn::rotateZ(M_PI / 4);
    auto fq = tfn::rotateZ(M_PI / 2);

    CHECK(hq * p == Vec4(-sqrt(2)/2, sqrt(2)/2, 0, 1));
    CHECK(fq * p == Vec4(-1,0,0,1));
}

TEST_CASE("Shearing") {
    Vec4 p(2, 3, 4, 1);

    auto transform = tfn::shearing(1, 0, 0, 0, 0, 0);

    CHECK(transform * p == Vec4(5,3,4,1));
}

TEST_CASE("View transformation") {
    Vec4 from(0, 0, 0, 1);
    Vec4 to(0, 0, -1, 1);
    Vec4 up(0, 1, 0, 0);

    Matrix<float, 4, 4> t = tfn::viewTransform(from, to, up);
    CHECK(t == Matrix<float, 4, 4>::identity());
}

TEST_CASE("View transformation in positive z") {
    Vec4 from(0, 0, 0, 1);
    Vec4 to(0, 0, 1, 1);
    Vec4 up(0, 1, 0, 0);

    Matrix<float, 4, 4> t = tfn::viewTransform(from, to, up);
    CHECK(t == tfn::scaling(-1,1,-1));
}

TEST_CASE("View transformation moves the world") {
    Vec4 from(0, 0, 8, 1);
    Vec4 to(0, 0, 0, 1);
    Vec4 up(0, 1, 0, 0);

    Matrix<float, 4, 4> t = tfn::viewTransform(from, to, up);
    CHECK(t == tfn::translate(0, 0, -8));
}

TEST_CASE("View transformation in arbitrary direction") {
    Vec4 from(1, 3, 2, 1);
    Vec4 to(4, -2, 8, 1);
    Vec4 up(1, 1, 0, 0);

    Matrix<float, 4, 4> t = tfn::viewTransform(from, to, up);
    CHECK(t == Matrix<float, 4, 4>(
              -0.50709 , 0.50709 , 0.67612 , -2.36643 ,
              0.76772 , 0.60609 , 0.12122 , -2.82843 ,
              -0.35857 , 0.59761 , -0.71714 , 0.00000 ,
              0.00000 , 0.00000 , 0.00000 , 1.00000
          ));
}
