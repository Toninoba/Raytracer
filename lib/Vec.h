//
// Created by tobi on 22.08.26.
//

#ifndef VECTOM_VEC_H
#define VECTOM_VEC_H
#include <cstddef>
#include <ostream>

#include "Matrix.h"
#include <Constants.h>


template<typename T, std::size_t N>
class Vec {
public:

    T data[N]{};

    constexpr Vec() = default;

    template<typename... Args>
    requires (sizeof...(Args) == N)
    constexpr Vec(Args... args)
        : data{static_cast<T>(args)...} {
    }

    constexpr explicit Vec(T value) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }

    constexpr T& operator[](std::size_t i) {
        return data[i];
    }

    constexpr const T& operator[](std::size_t i) const {
        return data[i];
    }

    constexpr T& x() {
        return data[0];
    }

    constexpr T& y() {
        return data[1];
    }

    constexpr T& z() {
        return data[2];
    }

    constexpr T& w() {
        return data[3];
    }

    constexpr bool operator==(const Vec& other) const {
        for (std::size_t i = 0; i < N; ++i) {
            if (!floats_equal(data[i], other.data[i])) {
                return false;
            }
        }
        return true;
    }

    constexpr Vec operator+(const Vec& other) const {
        Vec result;

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    constexpr Vec operator-(const Vec& other) const {
        Vec result;

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }

    constexpr Vec operator-() const {
        Vec result{};

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = -data[i];
        }

        return result;
    }

    friend Vec operator*(const Vec& left, const T right) {
        Vec result;

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = left.data[i] * right;
        }


        return result;
    }

    friend Vec operator*(const T left, const Vec& right) {
        Vec result;

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = right.data[i] * left;
        }


        return result;
    }

    template<size_t Rows>
    friend Vec operator*(const Matrix<T, Rows, N>& left, const Vec& right) {
        Vec result{};

        for (std::size_t i = 0; i < N; ++i) {
            T sum{0};
            for (std::size_t j = 0; j < N; ++j) {
                sum += left.at(i, j) * right.data[j];
            }
            result.data[i] = sum;
        }

        return result;
    }

    constexpr T dot(const Vec& other) const {
        T result{};

        for (std::size_t i = 0; i < N; ++i) {
            result += data[i] * other[i];
        }

        return result;
    }

    constexpr Vec cross(const Vec& other) const {
        Vec result;

        result[0] = data[1]*other[2] - data[2]*other[1];
        result[1] = data[2]*other[0] - data[0]*other[2];
        result[2] = data[0]*other[1] - data[1]*other[0];

        return result;
    }

    constexpr T length_squared() const {
        T result{};

        for (std::size_t i = 0; i < N; ++i) {
            result += data[i] * data[i];
        }

        return result;
    }

    constexpr T magnitude() const {
        return sqrt(length_squared());
    }

    // TODO fix for arbitrary N
    constexpr Vec normalize() const {
        T magnitude = this->magnitude();

        return {
            data[0] / magnitude,
            data[1] / magnitude,
            data[2] / magnitude,
            data[3] / magnitude
        };
    }

    constexpr Vec reflect(const Vec& normal) const {
        return *this - normal * 2 * dot(normal);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec& vec) {
        os << "Vec" << N << "[";

        for (std::size_t i = 0; i < N; i++) {
            os << vec.data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }

        os << "]";
        return os;
    }

};




#endif //VECTOM_VEC_H
