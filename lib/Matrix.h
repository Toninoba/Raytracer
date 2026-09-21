//
// Created by tobi on 23.08.26.
//

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H
#include <cstddef>
#include <cmath>
#include <immintrin.h>
#include <type_traits>
#include <stdexcept>

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

    constexpr static Matrix identity() 
    requires (Rows == Cols) {
        Matrix result(T{ 0 });
        for (size_t i = 0; i < Rows; ++i) {
            result.at(i, i) = T{ 1 };
        }

        return result;
    }

    constexpr T& operator[](std::size_t i) {
        return data[i];
    }

    constexpr const T& operator[](std::size_t i) const {
        return data[i];
    }

    constexpr T& at(const size_t row, const size_t col) {
           
        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix index out of range");
        }

        return data[row * Cols + col];
    }

    [[nodiscard]] constexpr const T& at(const size_t row, const size_t col) const {

        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix index out of range");
        }

        return data[row * Cols + col];
    }

    constexpr Matrix operator+(const Matrix<T, Rows, Cols>& other) const {
        Matrix result;

        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    constexpr Matrix operator-(const Matrix<T, Rows, Cols>& other) const {
        Matrix result;

        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }

    constexpr Matrix operator*(const T value) const {
        Matrix result{};

        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            result.data[i] = data[i] * value;
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

    bool operator==(const Matrix& other) const {
        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            if (this->data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr Matrix<T, Cols, Rows> transpose() const {
        Matrix<T, Cols, Rows> result;

        for (std::size_t row = 0; row < Rows; ++row) {
            for (std::size_t col = 0; col < Cols; ++col) {
                result.at(col, row) = at(row, col);
            }
        }

        return result;
    }

    [[nodiscard]] constexpr T determinant() const
    requires(Rows == Cols) {

        if constexpr (Rows == 1) {
            return at(0, 0);
        }
        else if constexpr (Rows == 2) {
            return determinant2x2();
        }
        else if constexpr (Rows == 3) {
            return determinant3x3();
        }
        else if constexpr (Rows == 4) {
            return determinant4x4();
        }
        else {
            // Calculate determinant by using laplace expansion by i-th Row (take the first row)
            T det{};

            for (std::size_t j = 0; j < Rows; ++j) {
                det += (j % 2 == 0 ? T{1} : T{-1}) * this->at(0, j) * submatrix(0, j).determinant();
            }

            return det;
        }



    }


    [[nodiscard]] constexpr Matrix<T, Rows-1, Cols-1> submatrix(
        const std::size_t row,
        const std::size_t col
        ) const requires (Rows > 1 && Cols > 1) {

        Matrix<T, Rows-1, Cols-1> submatrix{};

        std::size_t subRow = 0;

        for (std::size_t i = 0; i < Rows; ++i) {

            std::size_t subCol = 0;

            if (i == row) {
                continue;
            }

            for (std::size_t j = 0; j < Cols; ++j) {

                if (j == col) {
                    continue;
                }
                submatrix.at(subRow, subCol) = this->at(i, j);

                subCol++;
            }
            subRow++;
        }

        return submatrix;
    }

    [[nodiscard]] Matrix cofactor() const {
        Matrix result{};

        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                T sign = ((i + j) % 2 ==0) ? T{1} : T{-1};

                result.at(i, j) = sign * this->submatrix(i, j).determinant();
            }
        }

        return result;
    }

    [[nodiscard]] Matrix adjoint() const {
        return cofactor().transpose();
    }


    [[nodiscard]] Matrix inverse() const {
        Matrix result{};

        // Calculate inverse of 4x4 with Cramersch Rule
        // A^-1 = 1/det(A) * adj(A)

        T det = this->determinant();

        if (std::abs(det) < 1e-9) {
            throw std::domain_error("Matrix is not invertible");
        }

        return this->adjoint() * (1.0/det) ;
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

    [[nodiscard]] constexpr T determinant2x2() const {
        return data[0] * data[3] - data[1] * data[2];
    }

    [[nodiscard]] constexpr T determinant3x3() const {
        return (data[0] * data[4] * data[8] + data[1] * data[5] * data[6] + data[2] * data[3] * data[7]) -
            (data[2] * data[4] * data[6] + data[0] * data[5] * data[7] + data[1] * data[3] * data[8]);
    }

    [[nodiscard]] constexpr T determinant4x4() const {
        return
            data[0] * (
                data[5] * (data[10] * data[15] - data[11] * data[14])
                - data[6] * (data[9] * data[15] - data[11] * data[13])
                + data[7] * (data[9] * data[14] - data[10] * data[13])
                )
            - data[1] * (
                data[4] * (data[10] * data[15] - data[11] * data[14])
                - data[6] * (data[8] * data[15] - data[11] * data[12])
                + data[7] * (data[8] * data[14] - data[10] * data[12])
                )
            + data[2] * (
                data[4] * (data[9] * data[15] - data[11] * data[13])
                - data[5] * (data[8] * data[15] - data[11] * data[12])
                + data[7] * (data[8] * data[13] - data[9] * data[12])
                )
            - data[3] * (
                data[4] * (data[9] * data[14] - data[10] * data[13])
                - data[5] * (data[8] * data[14] - data[10] * data[12])
                + data[6] * (data[8] * data[13] - data[9] * data[12])
                );
    }

};

#endif //RAYTRACER_MATRIX_H
