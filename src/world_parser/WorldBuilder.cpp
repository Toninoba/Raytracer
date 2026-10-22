//
// Created by tobi on 19.10.26.
//

#include "WorldBuilder.h"

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "JsonParser.h"
#include "JsonValue.h"
#include "MatrixTransformations.h"
#include "Plane.h"
#include "Sphere.h"
#include "World.h"

World WorldBuilder::buildWorld(const std::string &filepath) {

    // open file and parse it
    JsonParser parser(filepath);
    JsonValue root = parser.parse();

    World world;

    // iterate over every object in array and process it
    try {
        int i = 0;

        while (true) {
            std::string type = root[i]["type"].asString();
            std::transform(type.begin(), type.end(), type.begin(),
                [](unsigned char c){ return std::tolower(c); });

            // handle lights first
            if (type == "pointlight") {
                //processLight(root[i]);
            }
            else {
                // check in method if passed object is shape or not
                world.addObject(processShape(root[i]));
            }

            i++;
        }
    }
    catch (std::out_of_range& e) {

    }

    return std::move(world);
}


std::unique_ptr<Shape> WorldBuilder::processShape(const JsonValue &value) {

    std::unique_ptr<Shape> shape = getShapeType(value["type"]);

    if (value.contains("transform")) {
        shape->setTransform(getTransformation(value));
    }

    if (value.contains("material")) {
        shape->setMaterial(getMaterial(value.at("material")));
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
            transformation = transformation *
                tfn::rotateX(operation.at("rotateX").asNumber());
        } else if (operation.contains("rotateY")) {
            transformation = transformation *
                tfn::rotateY(operation.at("rotateY").asNumber());
        } else if (operation.contains("rotateZ")) {
            transformation = transformation *
                tfn::rotateZ(operation.at("rotateZ").asNumber());
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
