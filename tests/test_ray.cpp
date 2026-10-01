//
// Created by tobi on 29.09.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Matrix.h>

#include "Intersection.h"
#include "Intersections.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec.h"

using Vec4 = Vec<float, 4>;

TEST_CASE("Creating a Ray") {

    Vec4 origin(1,2,3,1);
    Vec4 direction(4,5,6,0);

    Ray r(origin, direction);

    CHECK(r.getOrigin() == origin);
    CHECK(r. getDirection() == direction);
}

TEST_CASE("Ray position") {

    Ray r(Vec4(2,3,4,1), Vec4(1,0,0,0));

    CHECK(r.position(0) == Vec4(2,3,4,1));
    CHECK(r.position(1) == Vec4(3,3,4,1));
    CHECK(r.position(-1) == Vec4(1,3,4,1));
    CHECK(r.position(2.5) == Vec4(4.5,3,4,1));

}

TEST_CASE("Intersect Ray with Sphere") {

    Ray r(Vec4(0,0,-5,1), Vec4(0,0,1,0));

    Sphere s;

    auto xs = s.intersect(r);

    CHECK(xs.count == 2);
    CHECK(xs[0].t == doctest::Approx(4.0f));
    CHECK(xs[1].t == doctest::Approx(6.0f));
    CHECK(xs[0].object == &s);
    CHECK(xs[1].object == &s);

    r = Ray(Vec4(0,1,-5,1), Vec4(0,0,1,0));

    xs = s.intersect(r);

    CHECK(xs.count == 2);
    CHECK(xs[0].t == doctest::Approx(5.0f));
    CHECK(xs[1].t == doctest::Approx(5.0f));

    r = Ray(Vec4(0,2,-5,1), Vec4(0,0,1,0));

    xs = s.intersect(r);

    CHECK(xs.count == 0);

    r = Ray(Vec4(0,0,0,1), Vec4(0,0,1,0));

    xs = s.intersect(r);

    CHECK(xs.count == 2);
    CHECK(xs[0].t == doctest::Approx(-1.0f));
    CHECK(xs[1].t == doctest::Approx(1.0f));

    r = Ray(Vec4(0,0,5,1), Vec4(0,0,1,0));

    xs = s.intersect(r);

    CHECK(xs.count == 2);
    CHECK(xs[0].t == doctest::Approx(-6.0f));
    CHECK(xs[1].t == doctest::Approx(-4.0f));
}

TEST_CASE("Create intersection objects") {

    Sphere s;

    Intersection i(3.5, &s);

    CHECK(i.t == doctest::Approx(3.5f));

    Intersection i1(1, &s);
    Intersection i2(2, &s);

    Intersections xs(i1, i2);

    CHECK(xs.count == 2);
    CHECK(xs[0].t == 1);
    CHECK(xs[1].t == 2);
}

TEST_CASE("Test hits all positive t") {
    Sphere s;

    Intersection i1(1.0f, &s);
    Intersection i2(2.0f, &s);

    Intersections xs(i2,i1);

    auto i = xs.hit();
    CHECK(i.value() == i1);
}

TEST_CASE("Test hits some negative t") {
    Sphere s;

    Intersection i1(-1.0f, &s);
    Intersection i2(1.0f, &s);

    Intersections xs(i2,i1);

    auto i = xs.hit();
    CHECK(i.value() == i2);
}

TEST_CASE("Test hits all negative t") {
    Sphere s;

    Intersection i1(-1.0f, &s);
    Intersection i2(-2.0f, &s);

    Intersections xs(i2,i1);

    auto i = xs.hit();
    CHECK(i.has_value() == false);
}

TEST_CASE("Test hits beeing lowest nonnegative t") {
    Sphere s;

    Intersection i1(5.0f, &s);
    Intersection i2(7.0f, &s);
    Intersection i3(-3.0f, &s);
    Intersection i4(2.0f, &s);

    Intersections xs(i1,i2,i3,i4);

    auto i = xs.hit();
    CHECK(i.value() == i4);
}