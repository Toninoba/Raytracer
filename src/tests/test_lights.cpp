//
// Created by tobi on 01.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Color.h"
#include "Material.h"
#include "MatrixTransformations.h"
#include "PointLight.h"
#include "Sphere.h"

static Sphere placeholder{};
using Vec4f = Vec<float, 4>;

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

TEST_CASE("Test lights") {
    Color intensity(1,1,1);
    Vec4f position(0,0,0,1);

    PointLight light(position, intensity);

    CHECK(light.position == position);
    CHECK(light.intensity == intensity);

    Material m;

    CHECK(m.color == Color(1,1,1));
    CHECK(m.ambient == doctest::Approx(0.1f));
    CHECK(m.diffuse == doctest::Approx(0.9f));
    CHECK(m.specular == doctest::Approx(0.9f));
    CHECK(m.shininess == doctest::Approx(200.0f));

    Sphere s;

    CHECK(s.material() == m);
}

TEST_CASE("Phong lighting tests") {

    Material m;
    Vec4f position(0,0,0,1);

    Vec4f eyev(0, 0, -1, 0);
    Vec4f normalv(0, 0, -1, 0);
    PointLight light(Vec4f(0, 0, -10, 1), Color(1,1,1));

    Color result = light.lighting(m, &placeholder, position, eyev, normalv, false);
    CHECK(result == Color(1.9, 1.9, 1.9));

    eyev = Vec4f(0, sqrtf(2)/2, -sqrtf(2)/2, 0);


    result = light.lighting(m, &placeholder, position, eyev, normalv, false);
    CHECK(result == Color(1.0, 1.0, 1.0));


    eyev = Vec4f(0, 0, -1, 0);
    light = PointLight(Vec4f(0, 10, -10, 1), Color(1,1,1));

    result = light.lighting(m, &placeholder, position, eyev, normalv, false);
    CHECK(result == Color(0.7364, 0.7364, 0.7364));

    eyev = Vec4f(0, -sqrtf(2)/2, -sqrtf(2)/2, 0);

    result = light.lighting(m, &placeholder, position, eyev, normalv, false);
    CHECK(result == Color(1.6364, 1.6364, 1.6364));

    eyev = Vec4f(0, 0, -1, 0);
    light = PointLight(Vec4f(0, 0, 10, 1), Color(1,1,1));

    result = light.lighting(m, &placeholder, position, eyev, normalv, false);
    CHECK(result == Color(0.1, 0.1, 0.1));


}

TEST_CASE("Shadows") {
    Material m;
    Vec4f position(0,0,0,1);

    Vec4f eyev(0, 0, -1, 0);
    Vec4f normalv(0, 0, -1, 0);
    PointLight light(Vec4f(0, 0, -10, 1), {1,1,1});
    bool in_shadow = true;

    Color result = light.lighting(m, &placeholder, position, eyev, normalv, in_shadow);

    CHECK(result == Color{0.1, 0.1, 0.1});

}