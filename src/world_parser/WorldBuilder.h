//
// Created by tobi on 19.10.26.
//

#ifndef RAYTRACER_WORLDPARSER_H
#define RAYTRACER_WORLDPARSER_H

#include <memory>
#include <string>

#include "Camera.h"
#include "Matrix.h"


class Pattern;
class Material;
class PointLight;
class JsonValue;
class Shape;
class World;

struct WorldWithCamera {
    Camera camera;
    World world;
};

class WorldBuilder {

public:

    static WorldWithCamera buildWorld(const std::string& filepath);

    static std::unique_ptr<Shape> processShape(const JsonValue& shape);

    static std::unique_ptr<PointLight> processLight(const JsonValue& value);

    static std::unique_ptr<Shape> getShapeType(const JsonValue& shape);

    static Matrix<float, 4, 4> getTransformation(const JsonValue& value);

    static Material getMaterial(const JsonValue& value);

    static std::shared_ptr<Pattern> getPattern(const JsonValue& value);

    static std::shared_ptr<Pattern> getPatternType(const JsonValue& value);

    static Camera processCamera(const JsonValue& value);

    static Matrix<float, 4, 4> getViewTransformation(const JsonValue& value);

};


#endif //RAYTRACER_WORLDPARSER_H
