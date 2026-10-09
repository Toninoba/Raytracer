//
// Created by tobi on 06.10.26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Computations.h"
#include "GradientPattern.h"
#include "Intersection.h"
#include "Intersections.h"
#include "Material.h"
#include "MatrixTransformations.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "TestPattern.h"
#include "World.h"

using Vec4f = Vec<float, 4>;

TEST_CASE("Refraction material attribute") {
    Material m{};

    CHECK_EQ(m.transparency, 0.0f);
    CHECK_EQ(m.refractiveIndex, doctest::Approx(1.0f));
}

TEST_CASE("Glass sphere") {
    Sphere s = Sphere::glassSphere();

    CHECK_EQ(s.getTransform(), Matrix<float, 4, 4>::identity());
    CHECK_EQ(s.material().transparency, doctest::Approx(1.0f));
    CHECK_EQ(s.material().refractiveIndex, doctest::Approx(1.5f));
}

TEST_CASE("Finding n1 and n2") {
    auto A = std::make_unique<Sphere>(Sphere::glassSphere());
    A->setTransform(tfn::scaling(2,2,2));
    A->material().refractiveIndex = 1.5f;

    auto B = std::make_unique<Sphere>(Sphere::glassSphere());
    B->setTransform(tfn::translate(0, 0, -0.25));
    B->material().refractiveIndex = 2.0f;

    auto C = std::make_unique<Sphere>(Sphere::glassSphere());
    C->setTransform(tfn::translate(0, 0, 0.25));
    C->material().refractiveIndex = 2.5f;

    Ray r({0, 0, -4, 1}, {0, 0, 1, 0});

    Intersections xs(Intersection{2,A.get()}, Intersection{2.75,B.get()}, Intersection{3.25,C.get()}, Intersection{4.75,B.get()}, Intersection{5.25,C.get()}, Intersection{6,A.get()});

    static float nVals[][2] = {
        {1.0f, 1.5f},
        {1.5f, 2.0f},
        {2.0f, 2.5f},
        {2.5f, 2.5f},
        {2.5f, 1.5f},
        {1.5f, 1.0f}
    };

    for (int i = 0; i < 6; i++) {
        Computations comps = prepareComputations(xs[i], r, xs);

        CHECK_EQ(comps.n1, doctest::Approx(nVals[i][0]));
        CHECK_EQ(comps.n2, doctest::Approx(nVals[i][1]));
    }

}

TEST_CASE("Computing under point") {
    Ray r({0,0,-5,1},{0,0,1,0});
    Sphere shape = Sphere::glassSphere();
    shape.setTransform(tfn::translate(0,0,1));
    Intersection i(5, &shape);

    Intersections xs(i);

    Computations comps = prepareComputations(i, r, xs);

    CHECK_GT(comps.underPoint.z(), EPSILON/2);
    CHECK_LT(comps.point.z(), comps.underPoint.z());
}

TEST_CASE("Refracted Color of Opaque Object") {
    World w = World::defaultWorld();
    const Shape* shape = w.getObjects()[0].get();
    Ray r({0, 0, -5, 1}, {0,0,1,0});
    Intersections xs(Intersection(4, shape), Intersection(6,shape));
    Computations comps = prepareComputations(xs[0], r, xs);
    Color c = w.refractedColor(comps, 5);
    CHECK_EQ(c, Color(0,0,0));
}

TEST_CASE("Max recursion depth refracted color") {
    World w = World::defaultWorld();

    w.getObjects()[0]->material().transparency = 1.0f;
    w.getObjects()[0]->material().refractiveIndex = 1.5f;

    const Shape* shape = w.getObjects()[0].get();

    Ray r({0, 0, -5, 1}, {0,0,1,0});
    Intersections xs(Intersection(4, shape), Intersection(6,shape));
    Computations comps = prepareComputations(xs[0], r, xs);
    Color c = w.refractedColor(comps, 0);
    CHECK_EQ(c, Color(0,0,0));
}

TEST_CASE("Refracted Color under total internal refraction") {
    World w = World::defaultWorld();
    const Shape* shape = w.getObjects()[0].get();
    w.getObjects()[0]->material().transparency = 1.0f;
    w.getObjects()[0]->material().refractiveIndex = 1.5f;

    Ray r({0, 0, std::sqrt(2)/2, 1}, {0,1,0,0});

    Intersections xs(Intersection(-std::sqrtf(2)/2, shape), Intersection(std::sqrtf(2)/2,shape));
    Computations comps = prepareComputations(xs[1], r, xs);
    Color c = w.refractedColor(comps, 5);

    CHECK_EQ(c, Color(0,0,0));
}

TEST_CASE("Finding Refracted Color") {
    World w = World::defaultWorld();
    w.getObjects()[0]->material().ambient = 1.0f;
    w.getObjects()[0]->material().pattern = std::make_shared<TestPattern>(TestPattern());

    w.getObjects()[1]->material().transparency = 1.0f;
    w.getObjects()[1]->material().refractiveIndex = 1.5f;

    const Shape* A = w.getObjects()[0].get();
    const Shape* B = w.getObjects()[1].get();

    Ray r({0, 0, 0.1, 1}, {0, 1, 0, 0});
    Intersections xs(Intersection(-0.9899, A), Intersection(-0.4899, B), Intersection(0.4899, B), Intersection(0.9899, A));
    Computations comps = prepareComputations(xs[2], r, xs);

    Color c = w.refractedColor(comps, 5);
    CHECK_EQ(c, Color(0, 0.99888, 0.04725));
}

TEST_CASE("Handling Refraction in Shade hit") {
    World w = World::defaultWorld();

    auto floor = std::make_unique<Plane>();
    floor->material().transparency = 0.5f;
    floor->material().refractiveIndex = 1.5f;
    floor->setTransform(tfn::translate(0, -1, 0));

    w.addObject(std::move(floor));

    auto ball = std::make_unique<Sphere>();

    ball->material().color = Color(1, 0, 0);
    ball->material().ambient = 0.5f;
    ball->setTransform(tfn::translate(0, -3.5, -0.5));

    w.addObject(std::move(ball));

    Ray r({0,0,-3,1},{0, -std::sqrt(2.0f)/2, std::sqrt(2.0f)/2,0});
    Intersections xs(Intersection(std::sqrt(2.0f), w.getObjects()[2].get()));
    Computations comps = prepareComputations(xs[0], r, xs);
    Color c = w.shadeHit(comps, 5);

    CHECK_EQ(c, Color(0.93642, 0.68642, 0.68642));

}

TEST_CASE("Reflectance under total internal reflection") {
    Sphere shape = Sphere::glassSphere();

    Ray r({0, 0, std::sqrt(2.0f)/2, 1}, {0,1,0,0});
    Intersections xs(Intersection(-std::sqrt(2.0f)/2, &shape), Intersection(std::sqrt(2.0f)/2, &shape));

    Computations comps = prepareComputations(xs[1],r , xs);
    float reflectance = schlick(comps);

    CHECK_EQ(reflectance, doctest::Approx(1.0f));
}

TEST_CASE("Reflectance of perpendicular ray") {
    Sphere shape = Sphere::glassSphere();

    Ray r({0,0,0,1}, {0,1,0,0});
    Intersections xs(Intersection(-1, &shape), Intersection(1, &shape));

    Computations comps = prepareComputations(xs[1], r, xs);
    float reflectance = schlick(comps);

    CHECK_EQ(reflectance, doctest::Approx(0.04f));
}

TEST_CASE("Reflectance when n2 > n1") {
    Sphere shape = Sphere::glassSphere();

    Ray r({0,0.99,-2,1}, {0,0,1,0});
    Intersections xs(Intersection(1.8589, &shape));

    Computations comps = prepareComputations(xs[0], r, xs);
    float reflectance = schlick(comps);

    CHECK_EQ(reflectance, doctest::Approx(0.48873f));
}

TEST_CASE("Reflectance in shade hit") {
    World w = World::defaultWorld();

    auto floor = std::make_unique<Plane>();
    floor->material().transparency = 0.5f;
    floor->material().refractiveIndex = 1.5f;
    floor->material().reflective = 0.5f;
    floor->setTransform(tfn::translate(0, -1, 0));

    w.addObject(std::move(floor));

    auto ball = std::make_unique<Sphere>();

    ball->material().color = Color(1, 0, 0);
    ball->material().ambient = 0.5f;
    ball->setTransform(tfn::translate(0, -3.5, -0.5));

    w.addObject(std::move(ball));

    Ray r({0,0,-3,1},{0, -std::sqrt(2.0f)/2, std::sqrt(2.0f)/2,0});
    Intersections xs(Intersection(std::sqrt(2.0f), w.getObjects()[2].get()));
    Computations comps = prepareComputations(xs[0], r, xs);
    Color c = w.shadeHit(comps, 5);

    CHECK_EQ(c, Color(0.93391, 0.69643, 0.69243));
}