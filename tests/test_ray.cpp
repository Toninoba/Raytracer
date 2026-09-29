//
// Created by tobi on 29.09.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Matrix.h>

#include "Ray.h"
#include "Vec.h"

using Vec4 = Vec<float, 4>;

TEST_CASE("Creating a Ray") {

    Vec4 origin(1,2,3,1);
    Vec4 direction(4,5,6,0);

    Ray r(origin, direction);

    CHECK(r.getOrigin() == origin);
    CHECK(r. getDirection() == direction);
}

TEST_CASE("Ray position") {

    Ray r(Vec4(2,3,4,1), Vec4(1,0,0,0));

    CHECK(r.position(0) == Vec4(2,3,4,1));
    CHECK(r.position(1) == Vec4(3,3,4,1));
    CHECK(r.position(-1) == Vec4(1,3,4,1));
    CHECK(r.position(2.5) == Vec4(4.5,3,4,1));

}