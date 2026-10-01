//
// Created by tobi on 01.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "MatrixTransformations.h"
#include "Sphere.h"

TEST_CASE("Normals on a sphare") {
    Sphere s;

    CHECK(s.normalAt(Vec4f(1, 0, 0, 1)) == Vec4f(1, 0, 0, 0));
    CHECK(s.normalAt(Vec4f(0, 1, 0, 1)) == Vec4f(0, 1, 0, 0));
    CHECK(s.normalAt(Vec4f(0, 0, 1, 1)) == Vec4f(0, 0, 1, 0));
    CHECK(s.normalAt(Vec4f(1, 0, 0, 1)) == s.normalAt(Vec4f(1, 0, 0, 1)).normalize());

    s.setTransform(tfn::translate(0,1,0));

    auto n = s.normalAt(Vec4f(0, 1.70711, -0.70711,1));

    CHECK(n == Vec4f(0, 0.70711, -0.70711,0));

    auto m = tfn::scaling(1, 0.5, 1) * tfn::rotateZ(M_PI/5);
    s.setTransform(m);

    n = s.normalAt(Vec4f(0, sqrtf(2)/2, -sqrtf(2)/2, 1));
    CHECK(n == Vec4f(0, 0.97014, -0.24254,0));

}

TEST_CASE("Reflect vectors") {
    Vec4f v(1, -1, 0, 0);
    Vec4f n(0, 1, 0, 0);

    Vec4f r = v.reflect(n);

    CHECK(r == Vec4f(1, 1, 0, 0));

    v = Vec4f(0, -1, 0, 0);
    n = Vec4f(sqrtf(2)/2, sqrtf(2)/2, 0, 0);
    r = v.reflect(n);

    CHECK(r == Vec4f(1, 0, 0, 0));
}