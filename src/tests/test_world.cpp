//
// Created by tobi on 02.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Computations.h"
#include "Ray.h"
#include "World.h"
#include "Intersection.h"
#include "Intersections.h"
#include "MatrixTransformations.h"
#include "Sphere.h"

using Vec4f = Vec<float, 4>;

TEST_CASE("Creating a world") {
    World w;

    CHECK(w.getObjects().size() == 0);
    CHECK(w.getLights().size() == 0);

    PointLight light(Vec4f(-10, 10, -10, 1), Color(1,1,1));
    Sphere s1;
    Material m(Color(0.8, 1.0, 0.6), 0.1f, 0.7f, 0.2f, 200.0f);
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

TEST_CASE("Precomputing intersection") {
    Ray r(Vec4f(0,0,-5,1), Vec4f(0,0,1,0));
    Sphere s;
    Intersection i(4.0f, &s);

    Computations comps = prepareComputations(i, r);

    CHECK(comps.t == i.t);
    CHECK(comps.point == Vec4f(0,0,-1,1));
    CHECK(comps.eyev == Vec4f(0,0,-1,0));
    CHECK(comps.normalv == Vec4f(0,0,-1,0));
    CHECK(comps.inside == false);

    r = Ray(Vec4f(0,0,0,1), Vec4f(0,0,1,0));
    i = Intersection(1.0f, &s);

    comps = prepareComputations(i, r);
    CHECK(comps.point == Vec4f(0,0,1,1));
    CHECK(comps.eyev == Vec4f(0,0,-1,0));
    CHECK(comps.normalv == Vec4f(0,0,-1,0));
    CHECK(comps.inside == true);
}

TEST_CASE("Shading intersection") {
    World w = World::defaultWorld();
    Ray r(Vec4f(0,0,-5,1), Vec4f(0,0,1,0));
    const Shape* shape = w.getObjects()[0].get();

    Intersection i(4.0f, shape);
    Computations comps = prepareComputations(i, r);
    Color c = w.shadeHit(comps);

    CHECK(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading intersection from inside") {
    World w = World::defaultWorld();
    w.getLights()[0]->position = Vec4f(0,0.25,0,1);
    w.getLights()[0]->intensity = Color(1,1,1);

    Ray r(Vec4f(0,0,0,1), Vec4f(0,0,1,0));

    const Shape* shape = w.getObjects()[1].get();

    Intersection i(0.5f, shape);
    Computations comps = prepareComputations(i, r);
    Color c = w.shadeHit(comps);

    CHECK(c == Color(0.90498, 0.90498, 0.90498));

}

TEST_CASE("Color at") {
    World w = World::defaultWorld();

    Ray r(Vec4f(0, 0, -5, 1), Vec4f(0, 1, 0, 0));

    Color c = w.colorAt(r);
    CHECK(c == Color(0, 0, 0));

    r = Ray(Vec4f(0, 0, -5, 1), Vec4f(0, 0, 1, 0));

    c = w.colorAt(r);
    CHECK(c == Color(0.38066, 0.47583, 0.2855));

    Shape* outer = w.getObjects()[0].get();
    outer->material().ambient = 1.0f;

    Shape* inner = w.getObjects()[1].get();
    inner->material().ambient = 1.0f;

    r = Ray(Vec4f(0, 0, 0.75, 1), Vec4f(0, 0, -1, 0));
    c = w.colorAt(r);

    CHECK(c == inner->material().color);
}

TEST_CASE("Shadow detection") {
    World w = World::defaultWorld();

    Vec4f p(0, 10, 0, 1);

    CHECK_FALSE(w.isShadowed(p));

    p = Vec4f(10, -10, 10, 1);
    CHECK(w.isShadowed(p));

    p = Vec4f(-20, 20, -20, 1);
    CHECK_FALSE(w.isShadowed(p));

    p = Vec4f(-2, 2, -2, 1);
    CHECK_FALSE(w.isShadowed(p));
}


TEST_CASE("Shade hit with shadow") {

    World w;

    auto light = std::make_unique<PointLight>(Vec<float, 4>(0, 0, -10, 1), Color(1,1,1));
    auto sphere1 = std::make_unique<Sphere>();
    auto sphere2 = std::make_unique<Sphere>();
    sphere2.get()->setTransform(tfn::translate(0, 0, 10));

    w.addLight(std::move(light));
    w.addObject(std::move(sphere1));
    w.addObject(std::move(sphere2));

    Ray r({0,0,5,1},{0,0,1,0});
    Intersection i(4.0f, w.getObjects()[1].get());
    Computations comps = prepareComputations(i, r);
    Color c = w.shadeHit(comps);

    CHECK_EQ(c, Color(0.1,0.1,0.1));
}

TEST_CASE("Point offset") {
    Ray r({0,0,-5,1}, {0,0,1,0});
    Sphere s;
    s.setTransform(tfn::translate(0,0,1));

    Intersection i(5.0f, &s);
    Computations comps = prepareComputations(i, r);

    CHECK_LT(comps.overPoint.z(), -EPSILON/2);
    CHECK_GT(comps.point.z(), comps.overPoint.z());
}