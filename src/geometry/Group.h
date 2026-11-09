//
// Created by tobi on 09.11.26.
//

#ifndef RAYTRACER_GROUP_H
#define RAYTRACER_GROUP_H
#include "Shape.h"
#include <vector>


class Group : public Shape {
public:

    Group() = default;

    Intersections localIntersect(const Ray &ray) const override;
    Vec4f localNormalAt(const Vec4f &point) const override;

    void addChild(std::unique_ptr<Shape> shape);
    [[nodiscard]] const std::vector<std::unique_ptr<Shape>>& getChildren() const {
        return _children;
    };

private:

    std::vector<std::unique_ptr<Shape>> _children;



};


#endif //RAYTRACER_GROUP_H
