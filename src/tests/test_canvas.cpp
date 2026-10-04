//
// Created by tobi on 29.09.26.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Canvas.h"


TEST_CASE("Canvas creation") {

    Canvas c(10, 20);

    CHECK(c.WIDTH == 10);
    CHECK(c.HEIGHT == 20);

    for (int i = 0; i < c.WIDTH; i++) {
        for (int j = 0; j < c.HEIGHT; j++) {
            CHECK(c.pixelAt(i, j) == Color(0,0,0));
        }
    }

}

TEST_CASE("Writing to canvas") {

    Canvas c(10, 20);

    Color red(1,0,0);

    c.writePixel(2,3,red);

    CHECK(c.pixelAt(2,3) == red);
}