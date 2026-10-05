//
// Created by tobi on 04.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


#include "Cube.h"
#include "MatrixTransformations.h"
#include "Plane.h"
#include "TestShape.h"

using Vec4f = Vec<float, 4>;

TEST_CASE("The default transformation") {

    TestShape s;

    CHECK_EQ(s.getTransform(), Matrix<float, 4, 4>::identity());

    s.setTransform(tfn::translate(2,3,4));

    CHECK_EQ(s.getTransform(), tfn::translate(2,3,4));

    CHECK_EQ(s.material(), Material());

    Material m;
    m.ambient = 1;
    s.setMaterial(m);
    CHECK_EQ(s.material(), m);

}

TEST_CASE("Plane normal test") {
    Plane p;
    auto n1 = p.normalAt({0,0,0,1});
    auto n2 = p.normalAt({10,0,-10,1});
    auto n3 = p.normalAt({-5,0,150,1});

    CHECK_EQ(n1, Vec<float, 4>(0,1,0,0));
    CHECK_EQ(n2, Vec<float, 4>(0,1,0,0));
    CHECK_EQ(n3, Vec<float, 4>(0,1,0,0));
}

TEST_CASE("Plane intersection") {
    Plane p;
    Ray r({0,10,0,1},{0,0,1,0});
    auto xs = p.intersect(r);

    CHECK_EQ(xs.count, 0);

    r = Ray({0,0,0,1},{0,0,1,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 0);

    r = Ray({0,1,0,1},{0,-1,0,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 1);
    CHECK_EQ(xs[0].t, doctest::Approx(1.0f));
    CHECK_EQ(xs[0].object, &p);

    r = Ray({0,-1,0,1},{0,1,0,0});
    xs = p.intersect(r);

    CHECK_EQ(xs.count, 1);
    CHECK_EQ(xs[0].t, doctest::Approx(1.0f));
    CHECK_EQ(xs[0].object, &p);
}



TEST_CASE("Cubes") {
    static Vec4f origins[] = {
        {5, 0.5, 0, 1},
        {-5, 0.5, 0, 1},
        {0.5,5,0,1},
        {0.5, -5, 0, 1},
        {0.5, 0, 5, 1},
        {0.5, 0, -5, 1},
        {0, 0.5, 0, 1}
    };

    static Vec4f directions[] = {
        {-1,0,0,0},
        {1,0,0,0},
        {0,-1,0,0},
        {0,1,0,0},
        {0,0,-1,0},
        {0,0,1,0},
        {0,0,1,0}
    };

    static float tvals[][2] = {
        {4, 6},
        {4, 6},
        {4, 6},
        {4, 6},
        {4, 6},
        {4, 6},
        {-1 ,1}
    };

    for (std::size_t i = 0; i < 7; ++i) {
        Cube c;
        Ray r(origins[i], directions[i]);

        auto xs = c.intersect(r);

        CHECK_EQ(xs.count, 2);
        CHECK_EQ(xs[0].t, doctest::Approx(tvals[i][0]));
        CHECK_EQ(xs[1].t, doctest::Approx(tvals[i][1]));
    }
}

TEST_CASE("Ray missing Cube") {
    static Vec4f origins[] = {
        {-2,0,0,1},
        {0,-2,0,1},
        {0,0,-2,1},
        {2,0,2,1},
        {0,2,2,1},
        {2,2,0,1}
    };

    static Vec4f directions[] = {
        {0.2673, 0.5345, 0.8018, 0},
        {0.8018, 0.2673, 0.5345, 0},
        {0.5345, 0.8018, 0.2673, 0},
        {0, 0, -1, 0},
        {0, -1, 0, 0},
        {-1, 0, 0, 0}
    };

    for (std::size_t i = 0; i < 6; ++i) {
        Cube c;
        Ray r(origins[i], directions[i]);

        auto xs = c.intersect(r);

        CHECK_EQ(xs.count, 0);
    }
}

TEST_CASE("Cube normal vector") {
    static Vec4f points[] = {
        {1, 0.5, -0.8, 1},
        {-1, -0.2, 0.9, 1},
        {-0.4, 1, -0.1, 1},
        {0.3, -1, -0.7, 1},
        {-0.6, 0.3, 1, 1},
        {0.4, 0.4, -1, 1},
        {1, 1, 1, 1},
        {-1, -1, -1, 1}
    };

    static Vec4f normals[] = {
        {1, 0, 0, 0},
        {-1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, -1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, -1, 0},
        {1, 0, 0, 0},
        {-1, 0, 0, 0}
    };

    for (std::size_t i = 0; i < 8; ++i) {
        Cube c;

        auto normal = c.normalAt(points[i]);

        CHECK_EQ(normal, normals[i]);
    }
}