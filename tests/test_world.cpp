//
// Created by tobi on 02.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Ray.h"
#include "World.h"

TEST_CASE("Creating a world") {
    World w;

    CHECK(w.getObjects().size() == 0);
    CHECK(w.getLights().size() == 0);

    PointLight light(Vec4f(-10, 10, -10, 1), Color(1,1,1));
    Sphere s1;
    Material m(Color(0.8, 1.0, 0.6), 0.9f, 0.7f, 0.2f, 200.0f);
    s1.setMaterial(m);

    Sphere s2;
    s2.setTransform(tfn::scaling(0.5, 0.5, 0.5));

    World w2 = World::defaultWorld();

    CHECK(*w2.getLights()[0].get() == light);
    CHECK(*w2.getObjects()[0].get() == s1);

}

TEST_CASE("Ray world intersection") {
    World w = World::defaultWorld();

    Ray r(Vec4f(0, 0, -5, 1), Vec4f(0, 0, 1, 0));

    Intersections xs = w.intersect(r);
    xs.sort();

    CHECK(xs.count == 4);
    CHECK(xs[0].t == doctest::Approx(4.0f));
    CHECK(xs[1].t == doctest::Approx(4.5f));
    CHECK(xs[2].t == doctest::Approx(5.5f));
    CHECK(xs[3].t == doctest::Approx(6.0f));

}