//
// Created by tobi on 22.08.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Vec.h>

TEST_CASE("Vec creation") {
    Vec<float, 4> a(2.0);

    CHECK(a[0] == doctest::Approx(2.0f));
    CHECK(a[1] == doctest::Approx(2.0f));
    CHECK(a[2] == doctest::Approx(2.0f));
    CHECK(a[3] == doctest::Approx(2.0f));
}

TEST_CASE("Vec addition") {
    Vec<float, 4> a{1, 2, 3, 4};
    Vec<float, 4> b{5, 6, 7, 8};

    auto c = a + b;

    CHECK(c[0] == doctest::Approx(6.0f));
    CHECK(c[1] == doctest::Approx(8.0f));
    CHECK(c[2] == doctest::Approx(10.0f));
    CHECK(c[3] == doctest::Approx(12.0f));
}

TEST_CASE("Vec subtraction") {
    Vec<float, 4> a{1, 2, 3, 4};
    Vec<float, 4> b{5, 6, 7, 8};

    auto c = a - b;

    CHECK(c[0] == doctest::Approx(-4.0f));
    CHECK(c[1] == doctest::Approx(-4.0f));
    CHECK(c[2] == doctest::Approx(-4.0f));
    CHECK(c[3] == doctest::Approx(-4.0f));
}

TEST_CASE("Vec scalar multiplication") {
    Vec<float, 4> a{1, 2, 3, 4};
    float b = 5.0f;

    auto c = a * b;

    CHECK(c[0] == doctest::Approx(5.0f));
    CHECK(c[1] == doctest::Approx(10.0f));
    CHECK(c[2] == doctest::Approx(15.0f));
    CHECK(c[3] == doctest::Approx(20.0f));
}

TEST_CASE("Vec dot product") {
    Vec<float, 4> a{1, 2, 3, 4};
    Vec<float, 4> b{5, 6, 7, 8};

    auto c = a.dot(b);

    CHECK(c == doctest::Approx(70.0f));
}

TEST_CASE("Matrix Vector multiplication") {
    Matrix<float, 4, 4> A{
        1,2,3,4,
        2,4,4,2,
        8,6,4,1,
        0,0,0,1
    };

    Vec<float, 4> b{1,2,3,1};

    CHECK(A * b == Vec<float, 4>{18,24,33,1});
}