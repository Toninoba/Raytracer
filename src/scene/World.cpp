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

    const Material m(Color(0.8, 1.0, 0.6), 0.1f, 0.7f, 0.2f, 200.0f, 0.0f, 0.0f, 1.0f);
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

Color World::shadeHit(const Computations &comps , const std::size_t remaining) const {

    Color surface = Color(0.0f, 0.0f, 0.0f);

    for (const auto &light: _lights) {
        surface += light->lighting(
            // TODO combine these two parameters
            comps.object->material(),
            comps.object,
            comps.overPoint,
            comps.eyev,
            comps.normalv,
            isShadowed(comps.overPoint)
        );
    }

    const Color reflected = reflectedColor(comps, remaining);
    const Color refracted = refractedColor(comps, remaining);

    return surface + reflected + refracted;
}

Color World::colorAt(const Ray &ray , const std::size_t remaining) const {

    Intersections xs = intersect(ray);

    const auto hit = xs.hit();

    if (!hit.has_value()) {
        return {0.0f, 0.0f, 0.0f};
    }

    const Computations comps = prepareComputations(hit.value(), ray, xs);

    return shadeHit(comps, remaining);
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

Color World::reflectedColor(const Computations &comps, const std::size_t remaining) const {

    if (remaining == 0) {
        return {0.0f,0.0f,0.0f};
    }

    if (comps.object->material().reflective == 0.0f) {
        return {0, 0, 0};
    }

    Ray reflectedRay(comps.overPoint, comps.reflectv);

    return colorAt(reflectedRay, remaining - 1) * comps.object->material().reflective;

}

Color World::refractedColor(const Computations &comps, std::size_t remaining) const {

    if (remaining == 0 || comps.object->material().transparency == 0.0f) {
        return {0.0f,0.0f,0.0f};
    }

    const float nRatio = comps.n1 / comps.n2;

    const float cosI = comps.eyev.dot(comps.normalv);

    const float sin2T = nRatio * nRatio * (1 - cosI * cosI);

    if (sin2T > 1.0f) {
        return {0.0f, 0.0f, 0.0f};
    }

    const float cosT = std::sqrt(1.0f - sin2T);

    const Vec4f direction = comps.normalv * (nRatio * cosI - cosT) - comps.eyev * nRatio;

    Ray refractedRay(comps.underPoint, direction);

    return colorAt(refractedRay, remaining - 1) * comps.object->material().transparency;

}
