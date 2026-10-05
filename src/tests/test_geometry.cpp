//
// Created by tobi on 04.10.26.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
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

TEST_CASE("Cylinder intersection miss") {
    Cylinder c;

    static Vec4f origins[] = {
        {1, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, -5, 1}
    };

    static Vec4f directions[] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0}
    };

    for (std::size_t i = 0; i < 3; ++i) {

        auto dir = directions[i].normalize();
        Ray r (origins[i], dir);

        auto xs = c.intersect(r);

        CHECK_EQ(xs.count, 0);
    }

}

TEST_CASE("Cylinder intersection hit") {
    Cylinder c;

    static Vec4f origins[] = {
        {1, 0, -5, 1},
        {0, 0, -5, 1},
        {0.5, 0, -5, 1}
    };

    static Vec4f directions[] = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0.1, 1, 1, 0}
    };

    static float tvals[][2] = {
        {5, 5},
        {4, 6},
        {6.80798, 7.08872},

    };

    for (std::size_t i = 0; i < 3; ++i) {

        Ray r(origins[i], directions[i].normalize());

        auto xs = c.intersect(r);

        CHECK_EQ(xs.count, 2);
        CHECK_EQ(xs[0].t, doctest::Approx(tvals[i][0]));
        CHECK_EQ(xs[1].t, doctest::Approx(tvals[i][1]));
    }
}

TEST_CASE("Normals in Cylinder") {
    static Vec4f points[] = {
        {1, 0, 0, 1},
        {0, 5, -1, 1},
        {0, -2, 1, 1},
        {-1, 1, 0, 1},

    };

    static Vec4f normals[] = {
        {1, 0, 0, 0},
        {0, 0, -1, 0},
        {0, 0, 1, 0},
        {-1, 0, 0, 0},
    };

    for (std::size_t i = 0; i < 4; ++i) {
        Cylinder c;

        auto normal = c.normalAt(points[i]);

        CHECK_EQ(normal, normals[i]);
    }
}

TEST_CASE("Truncated Cylinder") {
    Cylinder c;

    CHECK_EQ(c.getMinimum(), -std::numeric_limits<float>::infinity());
    CHECK_EQ(c.getMaximum(), std::numeric_limits<float>::infinity());
}

TEST_CASE("Intersecting truncated Cylinder") {
    Cylinder cyl;
    cyl.setMinimum(1.0f);
    cyl.setMaximum(2.0f);

    static Vec4f origins[] = {
        {0, 1.5, 0, 1},
        {0, 3, -5, 1},
        {0, 0, -5, 1},
        {0, 2, -5, 1},
        {0, 1, -5, 1},
        {0, 1.5, -2, 1}
    };

    static Vec4f directions[] = {
        {0.1, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    };

    static int counts[] = {
        0, 0, 0, 0, 0, 2
    };

    for (int i = 0; i < 6; i++) {
        auto dir = directions[i].normalize();
        Ray r (origins[i], dir);
        auto xs = cyl.intersect(r);
        CHECK_EQ(xs.count, counts[i]);
    }
}

TEST_CASE("Closed cylinders") {
    Cylinder cyl;
    CHECK_FALSE(cyl.isClosed());
}

TEST_CASE("Closed cylinders intersection") {
    Cylinder cyl;
    cyl.setMinimum(1.0f);
    cyl.setMaximum(2.0f);
    cyl.close();

    static Vec4f origins[] = {
        {0, 3, 0, 1},
        {0, 3, -2, 1},
        {0, 4, -2, 1},
        {0, 0, -2, 1},
        {0, -1, -2, 1}
    };

    static Vec4f directions[] = {
        {0, -1, 0, 0},
        {0, -1, 2, 0},
        {0, -1, 1, 0},
        {0, 1, 2, 0},
        {0, 1, 1, 0}
    };

    for (int i = 0; i < 5; i++) {
        auto dir = directions[i].normalize();
        Ray r (origins[i], dir);
        auto xs = cyl.intersect(r);
        CHECK_EQ(xs.count, 2);
    }
}

TEST_CASE("Normal vectors of closed cylinders end caps") {
    Cylinder cyl;
    cyl.setMinimum(1);
    cyl.setMaximum(2);
    cyl.close();

    static Vec4f points[] = {
        {0, 1, 0, 1},
        {0.5, 1, 0, 1},
        {0, 1, 0.5, 1},
        {0, 2, 0, 1},
        {0.5, 2, 0, 1},
        {0, 2, 0.5, 1}
    };

    static Vec4f normals[] = {
        {0, -1, 0, 0},
        {0, -1, 0, 0},
        {0, -1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    };

    for (int i = 0; i < 6; i++) {
        auto n = cyl.normalAt(points[i]);
        CHECK_EQ(n, normals[i]);
    }
}

TEST_CASE("Cone intersection") {
    Cone cone;

    static Vec4f origins[] = {
        {0, 0, -5, 1},
        {0, 0, -5, 1},
        {1, 1, -5, 1}
    };

    static Vec4f directions[] = {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {-0.5, -1, 1, 0}
    };

    static float tvals[][2] = {
        {5, 5},
        {8.66025, 8.66025},
        {4.55006, 49.44994},

    };

    for (int i = 0; i < 3; i++) {
        auto dir = directions[i].normalize();
        Ray r(origins[i], dir);
        auto xs = cone.intersect(r);

        REQUIRE_EQ(xs.count, 2);
        CHECK_EQ(xs[0].t, doctest::Approx(tvals[i][0]));
        CHECK_EQ(xs[1].t, doctest::Approx(tvals[i][1]));
    }

    auto dir = Vec4f(0, 1, 1, 0).normalize();
    Ray r(Vec4f(0,0,-1,1), dir);
    auto xs = cone.intersect(r);
    CHECK_EQ(xs.count, 1);
    CHECK_EQ(xs[0].t, doctest::Approx(0.70711));
}

TEST_CASE("Cone end cap intersection") {
    Cone cone;
    cone.setMinimum(-0.5f);
    cone.setMaximum(0.5f);
    cone.close();

    static Vec4f origins[] = {
        {0, 0, -5, 1},
        {0, 0, -0.25, 1},
        {0, 0, -0.25, 1}
    };

    static Vec4f directions[] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0}
    };

    static float counts[] = {0, 2, 4};

    for (int i = 0; i < 3; i++) {
        auto dir = directions[i].normalize();
        Ray r(origins[i], dir);
        auto xs = cone.intersect(r);

        REQUIRE_EQ(xs.count, counts[i]);
    }
}

TEST_CASE("Cone normal vector") {
    Cone cone{};

    static Vec4f points[] = {
        {1,1,1,1},
        {-1,-1,0,1}
    };

    static Vec4f normals[] = {
        {1, -std::sqrt(2), 1, 0},
        {-1, 1, 0, 0}
    };

    for (int i = 0; i < 2; i++) {
        auto n = cone.normalAt(points[i]);
        CHECK_EQ(n, normals[i].normalize());
    }

}