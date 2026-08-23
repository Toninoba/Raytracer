//
// Created by tobi on 23.08.26.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H
#include <cstddef>
#include <immintrin.h>
#include <type_traits>

template<typename T, std::size_t Rows, std::size_t Cols>
class Matrix {

public:

    alignas(16) T data[Rows * Cols]{};

    constexpr Matrix() = default;

    template<typename... Args>
    requires (sizeof...(Args) == Cols * Rows)
    constexpr Matrix(Args... args)
        : data{static_cast<T>(args)...} {
    }

    constexpr explicit Matrix(T value) {
        for (std::size_t i = 0; i < Cols * Rows; ++i) {
            data[i] = value;
        }
    }

    constexpr T& operator[](std::size_t i) {
        return data[i];
    }

    constexpr const T& operator[](std::size_t i) const {
        return data[i];
    }

    constexpr T& at(const size_t row, const size_t col) {
        return data[row * Cols + col];
    }

    constexpr const T& at(const size_t row, const size_t col) const {
        return data[row * Cols + col];
    }

    constexpr Matrix operator+(const Matrix& other) const {
        Matrix result;

        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    template<std::size_t OtherCols>
    constexpr Matrix<T, Rows, OtherCols>
    operator*(const Matrix<T, Cols, OtherCols>& other) const {

        if constexpr (
            std::is_same_v<T, float> &&
            Rows == 4 &&
            Cols == 4 &&
            OtherCols == 4
        ) {
            return multiply4x4Simd(other);
        } else {
            return multiplyGeneric(other);
        }
    }


private:

    template<std::size_t OtherCols>
    constexpr Matrix<T, Rows, OtherCols>
    multiplyGeneric(const Matrix<T, Cols, OtherCols>& other) const {
        Matrix<T, Rows, OtherCols> result{};

        for (std::size_t row = 0; row < Rows; ++row) {
            for (std::size_t col = 0; col < OtherCols; ++col) {

                T sum{};

                for (std::size_t j = 0; j < Cols; ++j) {
                    sum += at(row, j) * other.at(j, col);
                }

                result.at(row, col) = sum;
            }
        }

        return result;
    }

    [[nodiscard]] Matrix<float, 4, 4>
    multiply4x4Simd(const Matrix<float, 4, 4>& other) const
    requires (
        std::is_same_v<T, float> &&
        Rows == 4 &&
        Cols == 4
    )
    {

        Matrix<T, 4, 4> result{};

        const __m128 b0 = _mm_load_ps(&other.data[0]);
        const __m128 b1 = _mm_load_ps(&other.data[4]);
        const __m128 b2 = _mm_load_ps(&other.data[8]);
        const __m128 b3 = _mm_load_ps(&other.data[12]);

        for (std::size_t row = 0; row < 4; ++row) {
            const float* a = &data[row * 4];

            __m128 r = _mm_mul_ps(
                _mm_set1_ps(a[0]),
                b0
            );

            r = _mm_fmadd_ps(
                _mm_set1_ps(a[1]),
                b1,
                r
            );

            r = _mm_fmadd_ps(
                _mm_set1_ps(a[2]),
                b2,
                r
            );

            r = _mm_fmadd_ps(
                _mm_set1_ps(a[3]),
                b3,
                r
            );

            _mm_store_ps(
                &result.data[row * 4],
                r
            );
        }

        return result;
    }


};

#endif //RAYTRACER_MATRIX_H
