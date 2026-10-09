//
// Created by tobi on 06.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <thread>

#include "Computations.h"
#include "Intersection.h"
#include "../../build/_deps/doctest-src/doctest/doctest.h"
#include "Material.h"
#include "MatrixTransformations.h"
#include "Plane.h"
#include "Ray.h"
#include "World.h"
#include "Intersections.h"


TEST_CASE("Reflectivity of Standard Material") {
    Material m;

    CHECK_EQ(m.reflective, 0.0f);
}

TEST_CASE("Precompute reflection vector") {
    Plane shape;
    Ray r({0,1,-1,1}, {0, -std::sqrt(2)/2, std::sqrt(2)/2, 0});

    Intersection i(std::sqrt(2.0f), &shape);
    Computations comps = prepareComputations(i, r, Intersections(i));

    CHECK_EQ(comps.reflectv, Vec<float, 4>(0, std::sqrt(2)/2, std::sqrt(2)/2, 0));
}

TEST_CASE("Strike nonreflective Surface") {
    World w = World::defaultWorld();
    Ray r({0,0,0,1},{0,0,1,0});
    w.getObjects()[1].get()->material().ambient = 1.0f;

    Intersection i(1.0f, w.getObjects()[1].get());

    Computations comps = prepareComputations(i, r, Intersections(i));

    Color color = w.reflectedColor(comps);

    CHECK_EQ(color, Color(0,0,0));
}

TEST_CASE("Strike reflective Surface") {
    World w = World::defaultWorld();

    std::unique_ptr<Plane> shape = std::make_unique<Plane>();
    shape->material().reflective = 0.5f;
    shape->setTransform(tfn::translate(0, -1, 0));

    w.addObject(std::move(shape));

    Ray r({0, 0, -3, 1}, {0, -std::sqrt(2.0f)/2, std::sqrt(2.0f)/2, 0});
    Intersection i(std::sqrt(2.0f), w.getObjects()[2].get());
    Computations comps = prepareComputations(i, r, Intersections(i));

    Color color = w.reflectedColor(comps);

    CHECK_EQ(color, Color(0.19032, 0.2379, 0.14274));

    color = w.shadeHit(comps);

    CHECK_EQ(color, Color(0.87677, 0.92436, 0.82918));

}

TEST_CASE("Infinite reflections") {
    World w;

    w.addLight(std::move(std::make_unique<PointLight>(Vec<float,4>{0,0,0,1},Color{1,1,1})));

    auto lower = std::make_unique<Plane>();
    lower->material().reflective = 1.0f;
    lower->setTransform(tfn::translate(0, -1, 0));

    w.addObject(std::move(lower));

    auto upper = std::make_unique<Plane>();
    upper->material().reflective = 1.0f;
    upper->setTransform(tfn::translate(0, 1, 0));
    w.addObject(std::move(upper));

    Ray r ({0,0,0,1},{0,1,0,0});

    std::atomic<bool> finished = false;

    Color c;

    std::thread t([&] {
        c = w.colorAt(r);
        finished = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(34));

    CHECK(finished);

    if (t.joinable()) {
        t.detach();
    }

}

TEST_CASE("Color at max depth reflections") {
    World w = World::defaultWorld();

    std::unique_ptr<Plane> shape = std::make_unique<Plane>();
    shape->material().reflective = 0.5f;
    shape->setTransform(tfn::translate(0, -1, 0));

    w.addObject(std::move(shape));

    Ray r({0, 0, -3, 1}, {0, -std::sqrt(2.0f)/2, std::sqrt(2.0f)/2, 0});
    Intersection i(std::sqrt(2.0f), w.getObjects()[2].get());
    Computations comps = prepareComputations(i, r, Intersections(i));

    Color color = w.reflectedColor(comps, 0);

    CHECK_EQ(color, Color(0,0,0));




}