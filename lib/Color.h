//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H
#include "Constants.h"
#include "Vec.h"


class Color {
public:

    explicit Color() = default;

    explicit Color(const Vec<float, 3>& color) {
        _data = color;
    }

    Color(const float r, const float g, const float b) {
        _data = Vec<float, 3>{r, g, b};
    }

    [[nodiscard]] float red() const {
        return _data[0];
    }

    [[nodiscard]] float green() const {
        return _data[1];
    }

    [[nodiscard]] float blue() const {
        return _data[2];
    }

    bool operator==(const Color& other) const {
        for (size_t i = 0; i < 3; i++) {
            if (!floats_equal(_data[i], other._data[i])) {
                return false;
            }
        }
        return true;
    }

    Color operator+(const Color& other) const {
        return Color{_data + other._data};
    }

    Color operator-(const Color& other) const {
        return Color{_data - other._data};
    }

    Color operator*(const float value) const {
        return Color{_data * value};
    }

    Color operator*(const Color& other) const {
        Color result{};

        result._data[0] = _data[0] * other._data[0];
        result._data[1] = _data[1] * other._data[1];
        result._data[2] = _data[2] * other._data[2];

        return result;
    }


private:
    Vec<float, 3> _data;




};


#endif //RAYTRACER_COLOR_H
