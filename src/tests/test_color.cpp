//
// Created by tobi on 29.09.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Color.h>

TEST_CASE("Color creation") {

    Color c(-0.5, 0.4, 1.7);

    CHECK(c.red() == doctest::Approx(-0.5));
    CHECK(c.green() == doctest::Approx(0.4));
    CHECK(c.blue() == doctest::Approx(1.7));
}

TEST_CASE("Color addition") {

    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);

    Color c3 = c1 + c2;

    CHECK(c3 == Color(1.6, 0.7, 1.0));

}

TEST_CASE("Color subtraction") {
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);

    Color c3 = c1 - c2;

    CHECK(c3 == Color(0.2, 0.5, 0.5));
}
TEST_CASE("Color scalar multiplication") {
    Color c(0.2, 0.3, 0.4);
    Color c2 = c * 2;

    CHECK(c2 == Color(0.4, 0.6, 0.8));
}

TEST_CASE("Color multiplication") {
    Color c1(1, 0.2, 0.4);
    Color c2(0.9, 1, 0.1);

    CHECK(c1 * c2 == Color(0.9, 0.2, 0.04));
}