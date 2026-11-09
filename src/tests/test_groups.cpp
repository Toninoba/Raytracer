//
// Created by tobi on 09.11.26.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Group.h"
#include "Intersections.h"
#include "Matrix.h"
#include "MatrixTransformations.h"
#include "Ray.h"
#include "Sphere.h"

TEST_CASE("Creating a group") {
    Group g{};

    CHECK_EQ(g.getTransform(), Matrix<float,4 ,4>::identity());
}

TEST_CASE("Shape contains parent") {
    Sphere s;
    CHECK_EQ(s.getParent(), nullptr);
}

TEST_CASE("Adding a child to a group") {
    Group g{};

    auto s = std::make_unique<Sphere>();

    g.addChild(std::move(s));

    CHECK_FALSE(g.getChildren().empty());
    CHECK_EQ(g.getChildren()[0]->getParent(), &g);
}

TEST_CASE("Intersecting a ray with a empty group") {
    Group g{};

    Ray r(Vec<float, 4>(0,0,0,1), {0,0,1,0});

    auto xs = g.localIntersect(r);
    CHECK_EQ(xs.count, 0);

}

TEST_CASE("Intersecting a ray with a nonempty group") {
    Group g{};
    auto s1 = std::make_unique<Sphere>();
    auto s2 = std::make_unique<Sphere>();
    auto s3 = std::make_unique<Sphere>();

    s2->setTransform(tfn::translate(0, 0, -3));
    s3->setTransform(tfn::translate(5, 0, 0));

    g.addChild(std::move(s1));
    g.addChild(std::move(s2));
    g.addChild(std::move(s3));

    Ray r({0,0,-5, 1}, {0, 0, 1,0});

    auto xs = g.localIntersect(r);

    CHECK_EQ(xs.count, 4);
    CHECK_EQ(xs[0].object, g.getChildren()[1].get());
    CHECK_EQ(xs[1].object, g.getChildren()[1].get());
    CHECK_EQ(xs[2].object, g.getChildren()[0].get());
    CHECK_EQ(xs[3].object, g.getChildren()[0].get());

}

TEST_CASE("Intersecting a transformed group") {
    Group g{};
    g.setTransform(tfn::scaling(2,2,2));
    auto s = std::make_unique<Sphere>();
    s->setTransform(tfn::translate(5,0,0));
    g.addChild(std::move(s));
    Ray r({10, 0, -10, 1}, {0, 0, 1, 0});
    auto xs = g.intersect(r);
    CHECK_EQ(xs.count, 2);
}