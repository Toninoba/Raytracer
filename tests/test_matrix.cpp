//
// Created by tobi on 23.08.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Matrix.h>


TEST_CASE("Matrix creation with single value") {
    Matrix<float, 2, 3> a(2.0f);

    CHECK(a.at(0, 0) == doctest::Approx(2.0f));
    CHECK(a.at(0, 1) == doctest::Approx(2.0f));
    CHECK(a.at(0, 2) == doctest::Approx(2.0f));

    CHECK(a.at(1, 0) == doctest::Approx(2.0f));
    CHECK(a.at(1, 1) == doctest::Approx(2.0f));
    CHECK(a.at(1, 2) == doctest::Approx(2.0f));
}


TEST_CASE("Matrix creation with values") {
    Matrix<float, 2, 3> a{
        1, 2, 3,
        4, 5, 6
    };

    CHECK(a.at(0, 0) == doctest::Approx(1.0f));
    CHECK(a.at(0, 1) == doctest::Approx(2.0f));
    CHECK(a.at(0, 2) == doctest::Approx(3.0f));

    CHECK(a.at(1, 0) == doctest::Approx(4.0f));
    CHECK(a.at(1, 1) == doctest::Approx(5.0f));
    CHECK(a.at(1, 2) == doctest::Approx(6.0f));
}


TEST_CASE("Matrix linear indexing") {
    Matrix<float, 2, 2> a{
        1, 2,
        3, 4
    };

    CHECK(a[0] == doctest::Approx(1.0f));
    CHECK(a[1] == doctest::Approx(2.0f));
    CHECK(a[2] == doctest::Approx(3.0f));
    CHECK(a[3] == doctest::Approx(4.0f));
}


TEST_CASE("Matrix element modification") {
    Matrix<float, 2, 2> a{};

    a.at(0, 0) = 5.0f;
    a.at(1, 1) = 10.0f;

    CHECK(a.at(0, 0) == doctest::Approx(5.0f));
    CHECK(a.at(0, 1) == doctest::Approx(0.0f));
    CHECK(a.at(1, 0) == doctest::Approx(0.0f));
    CHECK(a.at(1, 1) == doctest::Approx(10.0f));
}


TEST_CASE("Matrix addition") {
    Matrix<float, 2, 2> a{
        1, 2,
        3, 4
    };

    Matrix<float, 2, 2> b{
        5, 6,
        7, 8
    };

    auto c = a + b;

    CHECK(c.at(0, 0) == doctest::Approx(6.0f));
    CHECK(c.at(0, 1) == doctest::Approx(8.0f));
    CHECK(c.at(1, 0) == doctest::Approx(10.0f));
    CHECK(c.at(1, 1) == doctest::Approx(12.0f));
}


TEST_CASE("Matrix generic 2x2 multiplication") {
    Matrix<float, 2, 2> a{
        1, 2,
        3, 4
    };

    Matrix<float, 2, 2> b{
        5, 6,
        7, 8
    };

    auto c = a * b;

    /*
     * [1 2] [5 6]   [19 22]
     * [3 4] [7 8] = [43 50]
     */

    CHECK(c.at(0, 0) == doctest::Approx(19.0f));
    CHECK(c.at(0, 1) == doctest::Approx(22.0f));
    CHECK(c.at(1, 0) == doctest::Approx(43.0f));
    CHECK(c.at(1, 1) == doctest::Approx(50.0f));
}


TEST_CASE("Matrix non-square multiplication") {
    Matrix<float, 2, 3> a{
        1, 2, 3,
        4, 5, 6
    };

    Matrix<float, 3, 2> b{
         7,  8,
         9, 10,
        11, 12
    };

    auto c = a * b;

    /*
     * [1 2 3] [ 7  8]   [ 58  64]
     * [4 5 6] [ 9 10] = [139 154]
     *         [11 12]
     */

    CHECK(c.at(0, 0) == doctest::Approx(58.0f));
    CHECK(c.at(0, 1) == doctest::Approx(64.0f));
    CHECK(c.at(1, 0) == doctest::Approx(139.0f));
    CHECK(c.at(1, 1) == doctest::Approx(154.0f));
}


TEST_CASE("Matrix multiplication resulting in non-square matrix") {
    Matrix<float, 2, 2> a{
        1, 2,
        3, 4
    };

    Matrix<float, 2, 3> b{
        5,  6,  7,
        8,  9, 10
    };

    auto c = a * b;

    CHECK(c.at(0, 0) == doctest::Approx(21.0f));
    CHECK(c.at(0, 1) == doctest::Approx(24.0f));
    CHECK(c.at(0, 2) == doctest::Approx(27.0f));

    CHECK(c.at(1, 0) == doctest::Approx(47.0f));
    CHECK(c.at(1, 1) == doctest::Approx(54.0f));
    CHECK(c.at(1, 2) == doctest::Approx(61.0f));
}


TEST_CASE("Matrix multiplication with identity matrix") {
    Matrix<float, 3, 3> a{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    Matrix<float, 3, 3> identity{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };

    auto c = a * identity;

    for (std::size_t i = 0; i < 9; ++i) {
        CHECK(c[i] == doctest::Approx(a[i]));
    }
}


TEST_CASE("Matrix multiplication with zero matrix") {
    Matrix<float, 3, 3> a{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    Matrix<float, 3, 3> zero{};

    auto c = a * zero;

    for (std::size_t i = 0; i < 9; ++i) {
        CHECK(c[i] == doctest::Approx(0.0f));
    }
}


TEST_CASE("Matrix 4x4 SIMD multiplication") {
    Matrix<float, 4, 4> a{
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };

    Matrix<float, 4, 4> b{
        17, 18, 19, 20,
        21, 22, 23, 24,
        25, 26, 27, 28,
        29, 30, 31, 32
    };

    auto c = a * b;

    CHECK(c.at(0, 0) == doctest::Approx(250.0f));
    CHECK(c.at(0, 1) == doctest::Approx(260.0f));
    CHECK(c.at(0, 2) == doctest::Approx(270.0f));
    CHECK(c.at(0, 3) == doctest::Approx(280.0f));

    CHECK(c.at(1, 0) == doctest::Approx(618.0f));
    CHECK(c.at(1, 1) == doctest::Approx(644.0f));
    CHECK(c.at(1, 2) == doctest::Approx(670.0f));
    CHECK(c.at(1, 3) == doctest::Approx(696.0f));

    CHECK(c.at(2, 0) == doctest::Approx(986.0f));
    CHECK(c.at(2, 1) == doctest::Approx(1028.0f));
    CHECK(c.at(2, 2) == doctest::Approx(1070.0f));
    CHECK(c.at(2, 3) == doctest::Approx(1112.0f));

    CHECK(c.at(3, 0) == doctest::Approx(1354.0f));
    CHECK(c.at(3, 1) == doctest::Approx(1412.0f));
    CHECK(c.at(3, 2) == doctest::Approx(1470.0f));
    CHECK(c.at(3, 3) == doctest::Approx(1528.0f));
}


TEST_CASE("Matrix 4x4 SIMD identity multiplication") {
    Matrix<float, 4, 4> a{
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };

    Matrix<float, 4, 4> identity{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    auto c = a * identity;

    for (std::size_t i = 0; i < 16; ++i) {
        CHECK(c[i] == doctest::Approx(a[i]));
    }
}


TEST_CASE("Matrix integer multiplication") {
    Matrix<int, 2, 2> a{
        1, 2,
        3, 4
    };

    Matrix<int, 2, 2> b{
        5, 6,
        7, 8
    };

    auto c = a * b;

    CHECK(c.at(0, 0) == 19);
    CHECK(c.at(0, 1) == 22);
    CHECK(c.at(1, 0) == 43);
    CHECK(c.at(1, 1) == 50);
}

TEST_CASE("Matrix multiplication return type") {
    Matrix<float, 2, 3> a{};
    Matrix<float, 3, 4> b{};

    auto c = a * b;

    static_assert(
        std::is_same_v<
            decltype(c),
            Matrix<float, 2, 4>
        >
    );
}

TEST_CASE("Identity Matrix creation") {
    auto i = Matrix<float, 4, 4>::identity();

    CHECK(i.at(0, 0) == doctest::Approx(1.0f));
    CHECK(i.at(1, 1) == doctest::Approx(1.0f));
    CHECK(i.at(2, 2) == doctest::Approx(1.0f));
    CHECK(i.at(3, 3) == doctest::Approx(1.0f));
    CHECK(i.at(0, 1) == doctest::Approx(0.0f));
}

TEST_CASE("Transpose Matrix") {

    auto i = Matrix<int, 2, 3>{ 1,2,3,4,5,6 };

    auto result = i.transpose();

    CHECK(result.at(0, 0) == 1);
    CHECK(result.at(0, 1) == 4);
    CHECK(result.at(1, 1) == 5);
    CHECK(result.at(2, 1) == 6);


}

TEST_CASE("Determinant 2x2") {
    auto i = Matrix<int, 2, 2>{ 1,2,3,4 };

    int result = i.determinant();

    CHECK(result == -2);

    auto t = Matrix<int, 3, 3>{ 1,2,3,0,1,4,5,6,0 };
    result = t.determinant();

    CHECK(result == 1);

    Matrix<float, 4, 4> m{
    1, 2, 3, 4,
    5, 6, 7, 8,
    2, 6, 4, 8,
    3, 1, 1, 2
    };
    result = m.determinant();

    CHECK(result == doctest::Approx(72.0f));
}

TEST_CASE("Sub matrix") {
    auto i = Matrix<int, 3, 4>{1,2,3,4,5,6,7,8,9,10,11,12};
    auto sub = i.submatrix(1, 2);

    CHECK(sub.at(0,0) == 1);
    CHECK(sub.at(0,1) == 2);
    CHECK(sub.at(0,2) == 4);
    CHECK(sub.at(1,0) == 9);
    CHECK(sub.at(1,1) == 10);
    CHECK(sub.at(1,2) == 12);


}

TEST_CASE("5x5 Matrix determinant") {
    auto i = Matrix<int, 5, 5>{
        1,  2,  3,  4,  5,
        6,  7,  8,  9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    };

    CHECK(i.determinant() == 0);

    auto m = Matrix<int, 7, 7>{
        2,  1,  3,  4,  5,  6,  7,
        0,  3,  2,  1,  4,  5,  6,
        0,  0,  4,  2,  3,  1,  5,
        0,  0,  0,  5,  1,  2,  3,
        0,  0,  0,  0,  6,  4,  2,
        0,  0,  0,  0,  0,  7,  1,
        0,  0,  0,  0,  0,  0,  8
    };

    CHECK(m.determinant() == 40320);
}