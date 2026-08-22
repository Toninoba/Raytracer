//
// Created by tobi on 22.08.26.
//

#ifndef VECTOM_VEC_H
#define VECTOM_VEC_H
#include <cstddef>

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

    constexpr Vec operator*(T scalar) const {
        Vec result;

        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] * scalar;
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

    constexpr T length_squared() const {
        T result{};

        for (std::size_t i = 0; i < N; ++i) {
            result += data[i] * data[i];
        }

        return result;
    }

};


#endif //VECTOM_VEC_H
