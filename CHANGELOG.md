# Changelog

## 1.0.0 (2026-10-04)


### Features

* **canvas:** add Canvas class and tests ([436a605](https://github.com/Toninoba/Raytracer/commit/436a605803fd425a41d654fa29567aa4fd88257a))
* **canvas:** add SDL window and renderer ([95f74eb](https://github.com/Toninoba/Raytracer/commit/95f74ebd1c563830b3711b699f41f547ffd96aba))
* **canvas:** add Threadpool for rendering ([2c29be7](https://github.com/Toninoba/Raytracer/commit/2c29be7076a3ec4b0874b3dbffd3105ab456d9ca))
* **canvas:** finish live rendering ([048cb61](https://github.com/Toninoba/Raytracer/commit/048cb61850e70ae03b4010e21e4940605f7871c7))
* **geometry:** change Material parameter of Sphere class ([4653615](https://github.com/Toninoba/Raytracer/commit/46536152d4906ed6191b1df0348b68a5bc37ffa7))
* implement transpose and subtraction ([f78e7ad](https://github.com/Toninoba/Raytracer/commit/f78e7ad5e852b88dbbd3512f132a31dbc9051ecb))
* implement transpose and subtraction for matrices ([e4b3901](https://github.com/Toninoba/Raytracer/commit/e4b3901b8eaad5a5f2e17fdfc62f7a325703d3e5))
* **lib:** add Color class ([25cc3b2](https://github.com/Toninoba/Raytracer/commit/25cc3b254db69d0e6da5fdc180a62c731a26a246))
* **lib:** add cross product to vector class ([9a0dae0](https://github.com/Toninoba/Raytracer/commit/9a0dae023f52e07e6c0f75790667f4f8fc7bfc1f))
* **lib:** add determinant calculation for matrices ([3b8697b](https://github.com/Toninoba/Raytracer/commit/3b8697be40fd58020cf994eb19b4b40bef9998d7))
* **lib:** add matrix class with basic functionality ([d9c9424](https://github.com/Toninoba/Raytracer/commit/d9c9424cefbbb22b71fde3615692209022b34a15))
* **lib:** add matrix determinant calculation for arbitrary big matrices ([f1ac688](https://github.com/Toninoba/Raytracer/commit/f1ac6888cbf4b6ab2228b9e89512ca7dd8d2451e))
* **lib:** add matrix inverse calculation for 4x4 matrices ([2524e4d](https://github.com/Toninoba/Raytracer/commit/2524e4d1016f925a2f7e42892109e95222ac40a3))
* **lib:** add vector class ([03ae44a](https://github.com/Toninoba/Raytracer/commit/03ae44a5f1a3829f9aa05c665b599c01a967af22))
* **lib:** update Vec and Color class with += operator ([97749a6](https://github.com/Toninoba/Raytracer/commit/97749a6da84be2c4f91bc69bdeac544d2909ea61))
* **lighting:** implement PointLight and Phong shading model ([3fcaa7b](https://github.com/Toninoba/Raytracer/commit/3fcaa7be85fd1213d7c17214397dad0229ffbb68))
* **lighting:** implement vector reflection and normal calculation for spheres ([5a2e970](https://github.com/Toninoba/Raytracer/commit/5a2e970c5815494528b5a231e5fa785672fea92e))
* **primitives:** add Computations class ([0816e6a](https://github.com/Toninoba/Raytracer/commit/0816e6a90e24ecbf108666299755969d6fd89980))
* **primitives:** add first implementation of rays ([d9e05b7](https://github.com/Toninoba/Raytracer/commit/d9e05b779cca3db788ec76ccd6e84b725da93cda))
* **primitives:** add Intersection hit method ([b0616ab](https://github.com/Toninoba/Raytracer/commit/b0616aba5b8779332ba8153ab580c4648c326491))
* **primitives:** add Matrix transformations ([5440fd9](https://github.com/Toninoba/Raytracer/commit/5440fd922b626545a2570e8d436e6af73f8d90e1))
* **primitives:** add ray intersection method ([191dbb5](https://github.com/Toninoba/Raytracer/commit/191dbb5844305fd080ba086ce8ec0ccafe3d6067))
* **primitives:** add view transformation ([8c60fa2](https://github.com/Toninoba/Raytracer/commit/8c60fa282602006ebacba34564be7a206ba1cc0c))
* **primitives:** finish Ray implementation ([5fd269b](https://github.com/Toninoba/Raytracer/commit/5fd269ba09a4b9763676524afdbf755a464671e1))
* **scene:** add Camera class ([7a8d2c8](https://github.com/Toninoba/Raytracer/commit/7a8d2c8edfa58a27da96df7dfe4b81cdf8afbab6))
* **scene:** add colorAt and shadeHit function to World class ([d3f3687](https://github.com/Toninoba/Raytracer/commit/d3f3687d40eb7249ff291b6d12e4e5c7bdebe080))
* **scene:** start on World class implementation ([721cb37](https://github.com/Toninoba/Raytracer/commit/721cb378bef2a6ed3337f10fbca3e88112ea2a1b))


### Bug Fixes

* **canvas:** fix cxx feature not supported by github runner ([7e01c0b](https://github.com/Toninoba/Raytracer/commit/7e01c0b6523f62a48906e333c9e7b2462cdb8799))
* **canvas:** fix cxx feature not supported by github runner ([66659e5](https://github.com/Toninoba/Raytracer/commit/66659e5a52545acb0e1bf4e2b5f661a4d0b14b45))
* **canvas:** fix mismatched function definition ([d89ba19](https://github.com/Toninoba/Raytracer/commit/d89ba192df465b1cc12e64eb5a658e8a76a0047c))
* fix ci file ([2a320bf](https://github.com/Toninoba/Raytracer/commit/2a320bfbc14b47069eb05bc4cd7c64dc00484fc0))
* fix ci file cppcheck ([bf4b758](https://github.com/Toninoba/Raytracer/commit/bf4b758ec790a7fc6863e42a3a8940eecc526dc8))
* fix ci language and missing dependencies ([6f293e6](https://github.com/Toninoba/Raytracer/commit/6f293e66581a7d11b14356cb65394b2087e92afe))
* fix cmake file location ([c7bfe4a](https://github.com/Toninoba/Raytracer/commit/c7bfe4af303bde94c7a69ae151f8219c631b30d8))
* fix duplicate symbol error ([aaf2283](https://github.com/Toninoba/Raytracer/commit/aaf22839202428c7c66732c73d1d6641f55e2987))
* fix misssing imports ([c92aeb1](https://github.com/Toninoba/Raytracer/commit/c92aeb1887a7863afa41336424a2862a55182e6b))
* **lib:** fix matrix comparison ([f456217](https://github.com/Toninoba/Raytracer/commit/f4562171ffe992a42dc9f023efa798ce952ce85a))
