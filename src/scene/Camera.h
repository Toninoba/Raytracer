//
// Created by tobi on 04.10.26.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#include "Matrix.h"
#include "Ray.h"
#include "World.h"
#include "../canvas/Canvas.h"


class Camera {
public:


    Camera(const unsigned int hsize, const unsigned int vsize, const float fov) : _hsize(hsize), _vsize(vsize), _fov(fov) {
        const float halfView = tanf(fov / 2);
        const float aspect = static_cast<float>(hsize) / static_cast<float>(vsize);

        if (aspect >= 1) {
            _halfWidth = halfView;
            _halfHeight = halfView / aspect;
        } else {
            _halfWidth = halfView * aspect;
            _halfHeight = halfView;
        }

        _pixelSize = (_halfWidth * 2) / static_cast<float>(hsize);
    }

    Camera(const unsigned int hsize, const unsigned int vsize, const float fov,
           const Matrix<float, 4, 4> &viewTransformation) : _hsize(hsize), _vsize(vsize), _fov(fov),
                                                            _viewTransformation(viewTransformation),
                                                            _inverseViewTransformation(viewTransformation.inverse()) {
        const float halfView = tanf(fov / 2);
        const float aspect = static_cast<float>(hsize) / static_cast<float>(vsize);

        if (aspect >= 1) {
            _halfWidth = halfView;
            _halfHeight = halfView / aspect;
        } else {
            _halfWidth = halfView / aspect;
            _halfHeight = halfView;
        }

        _pixelSize = (_halfWidth * 2) / static_cast<float>(hsize);
    }

    [[nodiscard]] unsigned int hsize() const {
        return _hsize;
    }

    [[nodiscard]] unsigned int vsize() const {
        return _vsize;
    }

    [[nodiscard]] float fov() const {
        return _fov;
    }

    [[nodiscard]] float pixelSize() const {
        return _pixelSize;
    }

    [[nodiscard]] const Matrix<float, 4, 4>& getViewTransformation() const {
        return _viewTransformation;
    }

    void setViewTransformation(const Matrix<float, 4, 4>& transformation) {
        _viewTransformation = transformation;
        _inverseViewTransformation = transformation.inverse();
    }

    [[nodiscard]] Ray rayForPixel(unsigned int px, unsigned int py) const;

    [[nodiscard]] Canvas render(const World& world) const;

private:

    unsigned int _hsize;
    unsigned int _vsize;
    float _fov;
    Matrix<float, 4, 4> _viewTransformation = Matrix<float, 4, 4>::identity();
    Matrix<float, 4, 4> _inverseViewTransformation = _viewTransformation.inverse();

    float _pixelSize;
    float _halfWidth;
    float _halfHeight;

};


#endif //RAYTRACER_CAMERA_H
