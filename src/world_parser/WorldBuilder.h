//
// Created by tobi on 19.10.26.
//

#ifndef RAYTRACER_WORLDPARSER_H
#define RAYTRACER_WORLDPARSER_H

#include <memory>
#include <string>

#include "Matrix.h"

class Material;
class PointLight;
class JsonValue;
class Shape;
class World;

class WorldBuilder {

public:

    static World buildWorld(const std::string& filepath);

    static std::unique_ptr<Shape> processShape(const JsonValue& shape);

    static std::unique_ptr<PointLight> processLight(const JsonValue& light);

    static std::unique_ptr<Shape> getShapeType(const JsonValue& shape);

    static Matrix<float, 4, 4> getTransformation(const JsonValue& value);

    static Material getMaterial(const JsonValue& value);

};


#endif //RAYTRACER_WORLDPARSER_H
