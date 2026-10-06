//
// Created by tobi on 02.10.26.
//

#include "World.h"

#include "MatrixTransformations.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersections.h"
#include "Computations.h"


World World::defaultWorld() {
    World w;

    auto light = std::make_unique<PointLight>(Vec4f(-10, 10, -10, 1), Color(1, 1, 1));
    auto sphere1 = std::make_unique<Sphere>();

    Material m(Color(0.8, 1.0, 0.6), 0.1f, 0.7f, 0.2f, 200.0f);
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

    for (const auto &object: _objects) {
        Intersections objectXs = object->intersect(ray);
        xs.add(objectXs);
    }

    return xs;
}

Color World::shadeHit(const Computations &comps) const {
    Color shade(0.0f, 0.0f, 0.0f);

    for (const auto &light: _lights) {
        shade += light->lighting(
            // TODO combine these two parameters
            comps.object->material(),
            comps.object,
            comps.point,
            comps.eyev,
            comps.normalv,
            isShadowed(comps.overPoint)
        );
    }

    return shade;
}

Color World::colorAt(const Ray &ray) const {

    Intersections xs = intersect(ray);

    const auto hit = xs.hit();

    if (!hit.has_value()) {
        return {0.0f, 0.0f, 0.0f};
    }

    const Computations comps = prepareComputations(hit.value(), ray);

    return shadeHit(comps);
}

bool World::isShadowed(const Vec4f &point) const {

    const Vec4f v = _lights[0].get()->position - point;
    const float distance = v.magnitude();
    const Vec4f direction = v.normalize();

    const Ray r(point, direction);

    Intersections intersections = intersect(r);

    if (const auto hit = intersections.hit(); hit.has_value() && hit.value().t < distance) {
        return true;
    }

    return false;
}
