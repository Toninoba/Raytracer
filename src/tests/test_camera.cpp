//
// Created by tobi on 04.10.26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Camera.h"
#include "MatrixTransformations.h"
#include "Ray.h"

TEST_CASE("Camera creation") {

    unsigned int hsize = 160;
    unsigned int vsize = 120;
    float fov = PI_2;

    Camera c(hsize, vsize, fov);

    CHECK(c.hsize() == 160);
    CHECK(c.vsize() == 120);
    CHECK(c.fov() == doctest::Approx(PI_2));
    CHECK(c.getViewTransformation() == Matrix<float, 4, 4>::identity());
}

TEST_CASE("Camera pixel size") {
    Camera c(200, 125, PI_2);
    CHECK(c.pixelSize() == doctest::Approx(0.01));

    c = Camera(125, 200, PI_2);
    CHECK(c.pixelSize() == doctest::Approx(0.01));
}

TEST_CASE("Ray for pixel 1") {
    Camera c(201, 101, PI_2);
    Ray r = c.rayForPixel(100, 50);

    CHECK(r.getOrigin() == Vec<float, 4>(0,0,0,1));
    CHECK(r.getDirection() == Vec<float, 4>(0, 0, -1, 0));
}

TEST_CASE("Ray for pixel 2") {
    Camera c(201, 101, PI_2);
    Ray r = c.rayForPixel(0, 0);

    CHECK(r.getOrigin() == Vec<float, 4>(0,0,0,1));
    CHECK(r.getDirection() == Vec<float, 4>(0.66519, 0.33259, -0.66851, 0));
}

TEST_CASE("Ray for pixel 1") {
    Camera c(201, 101, PI_2);
    c.setViewTransformation(tfn::rotateY(PI_4) * tfn::translate(0, -2, 5));

    Ray r = c.rayForPixel(100, 50);

    CHECK(r.getOrigin() == Vec<float, 4>(0,2,-5,1));
    CHECK(r.getDirection() == Vec<float, 4>(sqrt(2.0f)/2, 0, -sqrt(2.0f)/2, 0));
}

TEST_CASE("Render image") {
    World w = World::defaultWorld();
    Camera c(11, 11, PI_2);
    Vec<float, 4> from(0, 0, -5, 1);
    Vec<float, 4> to(0, 0, 0, 1);
    Vec<float, 4> up(0, 1, 0, 0);

    c.setViewTransformation(tfn::viewTransform(from, to, up));

    Canvas image = c.render(w);

    CHECK(image.pixelAt(5, 5) == Color(0.38066, 0.47583, 0.2855));
}