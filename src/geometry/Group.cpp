//
// Created by tobi on 09.11.26.
//

#include "Group.h"

#include "Intersections.h"


Intersections Group::localIntersect(const Ray &ray) const {

    Intersections xs{};

    for (const auto& child : _children) {
        xs.add(child->intersect(ray));
    }

    // TODO Maybe unnecessary
    xs.sort();

    return xs;
}

Shape::Vec4f Group::localNormalAt(const Vec4f &point) const {
    return {};
}

void Group::addChild(std::unique_ptr<Shape> shape) {
    shape->setParent(this);
    _children.push_back(std::move(shape));
}
