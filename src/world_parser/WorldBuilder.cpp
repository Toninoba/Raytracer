//
// Created by tobi on 19.10.26.
//

#include "WorldBuilder.h"

#include "Camera.h"
#include "CheckerPattern.h"
#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "GradientPattern.h"
#include "JsonParser.h"
#include "JsonValue.h"
#include "MatrixTransformations.h"
#include "Plane.h"
#include "RingPattern.h"
#include "Sphere.h"
#include "StripedPattern.h"
#include "World.h"



WorldWithCamera WorldBuilder::buildWorld(const std::string &filepath) {

    // open file and parse it
    JsonParser parser(filepath);
    JsonValue root = parser.parse();

    World world;
    Camera camera{0, 0, 0};

    if (root.isObject() && root.contains("world")) {

        const auto& value = root.at("world");

        if (value.contains("objects")) {
            const auto& objects = value.at("objects");

            if (!objects.isArray()) {
                throw std::invalid_argument("objects must be an array");
            }

            for (std::size_t i = 0; i < objects.size(); ++i) {
                world.addObject(processShape(objects[i]));
            }

        }

        if (value.contains("lights")) {
            const auto& lights = value.at("lights");

            if (!lights.isArray()) {
                throw std::invalid_argument("lights must be an array");
            }

            for (std::size_t i = 0; i < lights.size(); ++i) {
                world.addLight(processLight(lights[i]));
            }

        }

        if (value.contains("camera")) {
            const auto& cameraValue = value.at("camera");

            if (!cameraValue.isObject()) {
                throw std::invalid_argument("camera must be an object");
            }

            camera = processCamera(cameraValue);
        }
        else {
            throw std::runtime_error("world must have a camera");
        }

    }
    else {
        throw std::runtime_error("json is not in world format");
    }

    return WorldWithCamera{
        .camera = camera,
        .world = std::move(world)
    };
}


std::unique_ptr<Shape> WorldBuilder::processShape(const JsonValue &value) {

    std::unique_ptr<Shape> shape = getShapeType(value["type"]);

    if (value.contains("transform")) {
        shape->setTransform(getTransformation(value));
    }

    if (value.contains("material")) {
        shape->setMaterial(getMaterial(value.at("material")));
    }

    if (value.contains("pattern")) {
        shape->material().pattern = getPattern(value.at("pattern"));
    }

    // Pattern

    return std::move(shape);
}

std::unique_ptr<Shape> WorldBuilder::getShapeType(const JsonValue &shape) {
    std::string type = shape.asString();
    std::transform(type.begin(), type.end(), type.begin(),
                [](unsigned char c){ return std::tolower(c); });

    if (type == "sphere") {
        return std::make_unique<Sphere>();
    }
    if (type == "plane") {
        return std::make_unique<Plane>();
    }
    if (type == "cone") {
        return std::make_unique<Cone>();
    }
    if (type == "cube") {
        return std::make_unique<Cube>();
    }
    if (type == "cylinder") {
        return std::make_unique<Cylinder>();
    }

    throw std::invalid_argument("Shape not recognised when building world");
}

Matrix<float, 4, 4> WorldBuilder::getTransformation(const JsonValue &value) {
    Matrix<float, 4, 4> transformation = Matrix<float, 4 ,4>::identity();

    const auto& transforms = value.at("transform");

    for (size_t i = 0; i < transforms.size(); ++i) {
        const auto& operation = transforms[i];

        if (operation.contains("translate")) {

            const auto& v = operation.at("translate");

            transformation = transformation * tfn::translate(
                v[0].asNumber(), v[1].asNumber(), v[2].asNumber()
            );

        } else if (operation.contains("scaling")) {

            const auto& v = operation.at("scaling");

            transformation = transformation * tfn::scaling(
                v[0].asNumber(), v[1].asNumber(), v[2].asNumber()
            );

        } else if (operation.contains("rotateX")) {

            const float rotationRadians = operation.at("rotateX").asNumber() * PI / 180.0f;

            transformation = transformation *
                tfn::rotateX(rotationRadians);

        } else if (operation.contains("rotateY")) {

            const float rotationRadians = operation.at("rotateY").asNumber() * PI / 180.0f;

            transformation = transformation *
                tfn::rotateY(rotationRadians);

        } else if (operation.contains("rotateZ")) {

            const float rotationRadians = operation.at("rotateZ").asNumber() * PI / 180.0f;

            transformation = transformation *
                tfn::rotateZ(rotationRadians);

        } else if (operation.contains("shearing")) {

            const auto& v = operation.at("shearing");

            transformation = transformation * tfn::shearing(
                v[0].asNumber(), v[1].asNumber(), v[2].asNumber(),
                v[3].asNumber(), v[4].asNumber(), v[5].asNumber()
            );
        }
    }

    return transformation;
}

Material WorldBuilder::getMaterial(const JsonValue &value) {
    Material material{};

    if (value.contains("color")) {
        const auto& c = value.at("color");

        if (!c.isArray()) {
            throw std::invalid_argument("Color must be an array");
        }
        if (c.size() != 3) {
            throw std::invalid_argument("Color must contain exactly 3 Numbers");
        }
        for (std::size_t i = 0 ; i < 3; ++i) {
            if (!c[i].isNumber()) {
                throw std::invalid_argument("Color component type must be numbers");
            }
        }

        material.color = Color(c[0].asNumber(), c[1].asNumber(), c[2].asNumber());

    }

    if (value.contains("ambient")) {
        if (!value.at("ambient").isNumber()) {
            throw std::invalid_argument("Ambient value must be a number");
        }
        material.ambient = value.at("ambient").asNumber();
    }

    if (value.contains("diffuse")) {
        if (!value.at("diffuse").isNumber()) {
            throw std::invalid_argument("Diffuse value must be a number");
        }
        material.diffuse = value.at("diffuse").asNumber();
    }

    if (value.contains("specular")) {
        if (!value.at("specular").isNumber()) {
            throw std::invalid_argument("Specular value must be a number");
        }
        material.specular = value.at("specular").asNumber();
    }

    if (value.contains("shininess")) {
        if (!value.at("shininess").isNumber()) {
            throw std::invalid_argument("Shininess value must be a number");
        }
        material.shininess = value.at("shininess").asNumber();
    }

    if (value.contains("reflective")) {
        if (!value.at("reflective").isNumber()) {
            throw std::invalid_argument("Reflective value must be a number");
        }
        material.reflective = value.at("reflective").asNumber();
    }

    if (value.contains("transparency")) {
        if (!value.at("transparency").isNumber()) {
            throw std::invalid_argument("Transparency value must be a number");
        }
        material.transparency = value.at("transparency").asNumber();
    }

    if (value.contains("refractiveIndex")) {
        if (!value.at("refractiveIndex").isNumber()) {
            throw std::invalid_argument("RefractiveIndex value must be a number");
        }
        material.refractiveIndex = value.at("refractiveIndex").asNumber();
    }

    return material;
}

std::shared_ptr<Pattern> WorldBuilder::getPattern(const JsonValue &value) {

    std::shared_ptr<Pattern> pattern;

    if (value.contains("type")) {
        pattern = getPatternType(value.at("type"));
    }
    else {
        throw std::invalid_argument("Pattern must have a type");
    }

    if (value.contains("colorA") && value.at("colorA").isArray() && value.at("colorA").size() == 3) {
        const auto& color = value.at("colorA");

        for (std::size_t i = 0 ; i < 3; ++i) {
            if (!color[i].isNumber()) {
                throw std::invalid_argument("Pattern Color A component type must be numbers");
            }
        }

        pattern->a() = Color(color[0].asNumber(), color[1].asNumber(), color[2].asNumber());
    }
    else {
        throw std::invalid_argument("Pattern is missing color A attribute");
    }

    if (value.contains("colorB") && value.at("colorB").isArray() && value.at("colorA").size() == 3) {
        const auto& color = value.at("colorB");

        for (std::size_t i = 0 ; i < 3; ++i) {
            if (!color[i].isNumber()) {
                throw std::invalid_argument("Pattern Color B component type must be numbers");
            }
        }

        pattern->b() = Color(color[0].asNumber(), color[1].asNumber(), color[2].asNumber());
    }
    else {
        throw std::invalid_argument("Pattern is missing color B attribute");
    }

    if (value.contains("transform")) {
        pattern->setTransform(getTransformation(value));
    }

    return pattern;
}

std::shared_ptr<Pattern> WorldBuilder::getPatternType(const JsonValue &value) {


    if (!value.isString()) {
        throw std::invalid_argument("Pattern type is not a string");
    }

    const std::string& type = value.asString();

    if (type == "CheckerPattern") {
        return std::make_shared<CheckerPattern>(Color(0,0,0), Color(1,1,1));
    }
    if (type == "GradientPattern") {
        return std::make_shared<GradientPattern>(Color(0,0,0), Color(1,1,1));
    }
    if (type == "RingPattern") {
        return std::make_shared<RingPattern>(Color(0,0,0), Color(1,1,1));
    }
    if (type == "StripedPattern") {
        return std::make_shared<StripedPattern>(Color(0,0,0), Color(1,1,1));
    }

    throw std::invalid_argument("Pattern type is not recognised");
}

std::unique_ptr<PointLight> WorldBuilder::processLight(const JsonValue &value) {

    std::unique_ptr<PointLight> light = std::make_unique<PointLight>(Vec<float, 4>(0,0,0,1), Color(0,0,0));

    if (value.contains("type")) {
        // expand later for more light types
        const auto& type = value.at("type");
        if (type.isString() && type.asString() == "PointLight") {
            // there is no point in changing type right now, expand later
        }
    }
    else {
        throw std::invalid_argument("Light is missing type argument");
    }

    if (value.contains("position") && value.at("position").isArray() && value.at("position").size() == 3) {
        const auto& position = value.at("position");

        for (std::size_t i = 0 ; i < 3; ++i) {
            if (!position[i].isNumber()) {
                throw std::invalid_argument("Light position component type must be numbers");
            }
        }

        light->position = Vec<float, 4>(position[0].asNumber(), position[1].asNumber(), position[2].asNumber(), 1);
    }

    if (value.contains("intensity") && value.at("intensity").isArray() && value.at("intensity").size() == 3) {
        const auto& intensity = value.at("intensity");

        for (std::size_t i = 0 ; i < 3; ++i) {
            if (!intensity[i].isNumber()) {
                throw std::invalid_argument("Light intensity component type must be numbers");
            }
        }

        light->intensity = Color(intensity[0].asNumber(), intensity[1].asNumber(), intensity[2].asNumber());
    }


    return std::move(light);
}

Camera WorldBuilder::processCamera(const JsonValue &value) {

    unsigned int hsize;
    unsigned int vsize;
    float fov;
    Matrix<float, 4, 4> viewTransformation;

    if (value.contains("hsize") && value.at("hsize").isNumber()) {
        hsize = static_cast<unsigned int>(value.at("hsize").asNumber());
    }
    else {
        throw std::invalid_argument("Camera must have hsize argument as a number");
    }

    if (value.contains("vsize") && value.at("vsize").isNumber()) {
        vsize = static_cast<unsigned int>(value.at("vsize").asNumber());
    }
    else {
        throw std::invalid_argument("Camera must have vsize argument as a number");
    }

    if (value.contains("fov") && value.at("fov").isNumber()) {
        fov = value.at("fov").asNumber() * PI / 180.0f;
    }
    else {
        throw std::invalid_argument("Camera must have fov argument as a number");
    }

    if (value.contains("viewTransform") && value.at("viewTransform").isObject()) {
        viewTransformation = getViewTransformation(value.at("viewTransform"));
    }
    else {
        throw std::invalid_argument("Camera must have a view transformation");
    }

    return {hsize, vsize, fov, viewTransformation};
}

Matrix<float, 4, 4> WorldBuilder::getViewTransformation(const JsonValue &value) {

    Vec<float, 4> from;
    Vec<float, 4> to;
    Vec<float, 4> up;

    if (value.contains("from") && value.at("from").isArray() && value.at("from").size() == 3) {
        const auto& fromValue = value.at("from");

        for (std::size_t i = 0; i < 3; ++i) {
            if (!fromValue[i].isNumber()) {
                throw std::invalid_argument("From vector values must be numbers");
            }
        }

        from = Vec<float, 4>(fromValue[0].asNumber(), fromValue[1].asNumber(), fromValue[2].asNumber(), 1);
    }
    else {
        throw std::invalid_argument("The view transformation must have a from parameter");
    }

    if (value.contains("to") && value.at("to").isArray() && value.at("to").size() == 3) {
        const auto& toValue = value.at("to");

        for (std::size_t i = 0; i < 3; ++i) {
            if (!toValue[i].isNumber()) {
                throw std::invalid_argument("To vector values must be numbers");
            }
        }

        to = Vec<float, 4>(toValue[0].asNumber(), toValue[1].asNumber(), toValue[2].asNumber(), 1);
    }
    else {
        throw std::invalid_argument("The view transformation must have a to parameter");
    }

    if (value.contains("up") && value.at("up").isArray() && value.at("up").size() == 3) {
        const auto& upValue = value.at("up");

        for (std::size_t i = 0; i < 3; ++i) {
            if (!upValue[i].isNumber()) {
                throw std::invalid_argument("Up vector values must be numbers");
            }
        }

        up = Vec<float, 4>(upValue[0].asNumber(), upValue[1].asNumber(), upValue[2].asNumber(), 0);
    }
    else {
        throw std::invalid_argument("The view transformation must have a up parameter");
    }

    return tfn::viewTransform(from, to, up);
}
