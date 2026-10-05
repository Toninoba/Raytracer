//
// Created by tobi on 04.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


#include "MatrixTransformations.h"
#include "Plane.h"
#include "TestShape.h"

using Vec4f = Vec<float, 4>;

TEST_CASE("The default transformation") {

    TestShape s;

    CHECK_EQ(s.getTransform(), Matrix<float, 4, 4>::identity());

    s.setTransform(tfn::translate(2,3,4));

    CHECK_EQ(s.getTransform(), tfn::translate(2,3,4));

    CHECK_EQ(s.material(), Material());

    Material m;
    m.ambient = 1;
    s.setMaterial(m);
    CHECK_EQ(s.material(), m);

}

TEST_CASE("Plane normal test") {
    Plane p;
    auto n1 = p.normalAt({0,0,0,1});
    auto n2 = p.normalAt({10,0,-10,1});
    auto n3 = p.normalAt({-5,0,150,1});

    CHECK_EQ(n1, Vec<float, 4>(0,1,0,0));
    CHECK_EQ(n2, Vec<float, 4>(0,1,0,0));
    CHECK_EQ(n3, Vec<float, 4>(0,1,0,0));
}

TEST_CASE("Plane intersection") {
    Plane p;
    Ray r({0,10,0,1},{0,0,1,0});
    auto xs = p.intersect(r);

    CHECK_EQ(xs.count, 0);

    r = Ray({0,0,0,1},{0,0,1,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 0);

    r = Ray({0,1,0,1},{0,-1,0,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 1);
    CHECK_EQ(xs[0].t, doctest::Approx(1.0f));
    CHECK_EQ(xs[0].object, &p);

    r = Ray({0,-1,0,1},{0,1,0,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 1);
    CHECK_EQ(xs[0].t, doctest::Approx(1.0f));
    CHECK_EQ(xs[0].object, &p);
}