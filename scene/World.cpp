//
// Created by tobi on 02.10.26.
//

#include "World.h"


World World::defaultWorld() {
    World w;

    auto light = std::make_unique<PointLight>(Vec4f(-10, 10, -10, 1), Color(1, 1, 1));
    auto sphere1 = std::make_unique<Sphere>();

    Material m(Color(0.8, 1.0, 0.6), 0.9f, 0.7f, 0.2f, 200.0f);
    sphere1->setMaterial(m);

    auto sphere2 = std::make_unique<Sphere>();
    sphere2->setTransform(tfn::scaling(0.5, 0.5, 0.5));

    w.addObject(std::move(sphere1));
    w.addObject(std::move(sphere2));
    w.addLight(std::move(light));

    return w;
}

Intersections World::intersect(const Ray &ray) const {
    Intersections xs;

    for (const auto& object : _objects) {

        Intersections objectXs = object->intersect(ray);
        xs.add(objectXs);
    }

    return xs;
}
