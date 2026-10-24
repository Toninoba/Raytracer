//
// Created by tobi on 06.10.26.
//



#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "CheckerPattern.h"
#include "Color.h"
#include "GradientPattern.h"
#include "../primitives/Material.h"
#include "MatrixTransformations.h"
#include "Sphere.h"
#include "StripedPattern.h"
#include "PointLight.h"
#include "RingPattern.h"

static Color black(0, 0, 0);
static Color white(1, 1, 1);
static Sphere placeholder{};

TEST_CASE("Creating Striped Pattern") {
    StripedPattern pattern(white, black);

    CHECK_EQ(pattern.a(), white);
    CHECK_EQ(pattern.b(), black);
}

TEST_CASE("Test stripes constant in y") {
    StripedPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,1,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,2,0,1}), white);
}

TEST_CASE("Test stripes constant in z") {
    StripedPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,0,1,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,0,2,1}), white);
}

TEST_CASE("Test stripes alternating in z") {
    StripedPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0.9,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({1,0,0,1}), black);
    CHECK_EQ(pattern.localPatternAt({-0.1,0,0,1}), black);
    CHECK_EQ(pattern.localPatternAt({-1,0,0,1}), black);
    CHECK_EQ(pattern.localPatternAt({-1.1,0,0,1}), white);
}

TEST_CASE("Lighting with a pattern applied") {
    Material m;

    m.pattern = std::make_shared<StripedPattern>(StripedPattern{white, black});
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    Vec<float, 4> eyev(0, 0, -1, 0);
    Vec<float, 4> normalv(0, 0, -1, 0);

    PointLight light({0, 0, -10, 1}, {1,1,1});

    m.pattern = std::make_shared<StripedPattern>(white, black);

    Color c1 = light.lighting(m, &placeholder, {0.9, 0, 0, 1}, eyev, normalv, false);
    Color c2 = light.lighting(m, &placeholder, {1.1, 0, 0, 1}, eyev, normalv, false);

    CHECK_EQ(c1, white);
    CHECK_EQ(c2, black);
}

TEST_CASE("Stripes with an object transformation") {
    Sphere s;

    s.setTransform(tfn::scaling(2,2,2));

    StripedPattern pattern(white, black);

    s.material().pattern = std::make_shared<StripedPattern>(pattern);

    Color c = pattern.patternAtShape(&s, {1.5, 0, 0, 1});

    CHECK_EQ(c, white);
}

TEST_CASE("Stripes with a pattern transformation") {
    Sphere s;

    StripedPattern pattern(white, black);

    pattern.setTransform(tfn::scaling(2,2,2));

    s.material().pattern = std::make_shared<StripedPattern>(pattern);

    Color c = pattern.patternAtShape(&s, {1.5, 0, 0, 1});

    CHECK_EQ(c, white);
}

TEST_CASE("Stripes with both an object and a pattern transformation") {
    Sphere s;

    s.setTransform(tfn::scaling(2,2,2));

    StripedPattern pattern(white, black);

    pattern.setTransform(tfn::translate(0.5, 0, 0));

    s.material().pattern = std::make_shared<StripedPattern>(pattern);

    Color c = pattern.patternAtShape(&s, {2.5, 0, 0, 1});

    CHECK_EQ(c, white);
}

TEST_CASE("Gradient Pattern") {

    GradientPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0.25,0,0,1}), Color(0.75, 0.75, 0.75));
    CHECK_EQ(pattern.localPatternAt({0.5,0,0,1}), Color(0.5, 0.5, 0.5));
    CHECK_EQ(pattern.localPatternAt({0.75,0,0,1}), Color(0.25, 0.25, 0.25));

}

TEST_CASE("Ring pattern") {

    RingPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({1,0,0,1}), black);
    CHECK_EQ(pattern.localPatternAt({0,0,1,1}), black);
    CHECK_EQ(pattern.localPatternAt({0.708,0,0.708,1}), black);

}

TEST_CASE("Checker Pattern") {
    CheckerPattern pattern(white, black);

    CHECK_EQ(pattern.localPatternAt({0,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0.99,0,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({1.01,0,0,1}), black);

    CHECK_EQ(pattern.localPatternAt({0,0.99,0,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,1.01,0,1}), black);

    CHECK_EQ(pattern.localPatternAt({0,0,0.99,1}), white);
    CHECK_EQ(pattern.localPatternAt({0,0,1.01,1}), black);

}