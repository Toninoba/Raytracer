//
// Created by tobi on 02.10.26.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <memory>
#include <vector>

#include "Computations.h"
#include "MatrixTransformations.h"
#include "Sphere.h"
#include "PointLight.h"


class World {
public:

    World() = default;

    static World defaultWorld();

    [[nodiscard]] const std::vector<std::unique_ptr<Sphere>>& getObjects() const {
        return _objects;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<PointLight>>& getLights() const {
        return _lights;
    }

    void addObject(std::unique_ptr<Sphere> object) {
        _objects.push_back(std::move(object));
    }

    void addLight(std::unique_ptr<PointLight> light) {
        _lights.push_back(std::move(light));
    }

    [[nodiscard]] Intersections intersect(const Ray& ray) const;

    [[nodiscard]] Color shadeHit(const Computations& comps) const;

    [[nodiscard]] Color colorAt(const Ray& ray) const;

    [[nodiscard]] bool isShadowed(const Vec4f& point) const;

private:
    std::vector<std::unique_ptr<Sphere>> _objects;
    std::vector<std::unique_ptr<PointLight>> _lights;

    using Vec4f = Vec<float, 4>;


};


#endif //RAYTRACER_WORLD_H
