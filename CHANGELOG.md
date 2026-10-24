# Changelog

## [0.2.0](https://github.com/Toninoba/Raytracer/compare/v0.1.0...v0.2.0) (2026-10-24)


### Features

* add refraction and fresnel effect rendering ([9ba0b2d](https://github.com/Toninoba/Raytracer/commit/9ba0b2dfcc965db837e93b67a7525ffd70fd6bdd))
* add shadow rendering ([19b2c91](https://github.com/Toninoba/Raytracer/commit/19b2c91ea7b86b35dfe1f237663e91d790fc804f))
* add shadow rendering ([caf0f75](https://github.com/Toninoba/Raytracer/commit/caf0f75ec7b729dc30b6e6e756ee3fc41daa56cb))
* **geometry:** add Glass Sphere object ([449c022](https://github.com/Toninoba/Raytracer/commit/449c022108ec28c84a46d3c688a7a25b022d1bf1))
* **patterns:** add Base Pattern class and Striped Pattern ([0b11459](https://github.com/Toninoba/Raytracer/commit/0b11459d3c0f1d50eebbac9708de1b2bcb66bd2b))
* **patterns:** add Checker Pattern ([c3b8343](https://github.com/Toninoba/Raytracer/commit/c3b83432f96e63fe2b0cd1b925ea5a3e629da1f6))
* **patterns:** add Gradient pattern ([db5e4ec](https://github.com/Toninoba/Raytracer/commit/db5e4ec6ed0db798f87afd3877e5780abdfecc07))
* **patterns:** add Ring pattern ([98d96f5](https://github.com/Toninoba/Raytracer/commit/98d96f530f04cd982ee873baeeb45970d4c74f11))
* **patterns:** add TestPattern for test purposes ([a0a6958](https://github.com/Toninoba/Raytracer/commit/a0a695806dc379120cebc1db4c9cb456112c909b))
* **primitives:** add reflection rendering ([db4f36f](https://github.com/Toninoba/Raytracer/commit/db4f36f0a6ea29bdf3a0d132b8c5c849e74dea74))
* **primitives:** add reflective parameter to computations ([2a146b3](https://github.com/Toninoba/Raytracer/commit/2a146b31a4f686856d2f771630748389ec74ae6b))
* **primitives:** add reflective parameter to material ([75ec4a4](https://github.com/Toninoba/Raytracer/commit/75ec4a49a46df74be2e7e1d9d8aa45c83fac80f8))
* **primitives:** make data structures support refraction ([c3422ab](https://github.com/Toninoba/Raytracer/commit/c3422ab0a317d77eac95fce10f7ff1b33bbe6740))
* **scene:** add functions to calculate refracted Color ([6e72070](https://github.com/Toninoba/Raytracer/commit/6e72070cdb82f881c033338f215837a464e54753))
* **world_parser:** add scaffold for json parsing ([7bdfcb3](https://github.com/Toninoba/Raytracer/commit/7bdfcb354f75acceb0715c9d1e7f38c9b9b835df))
* **world-parser:** add correct cone and cylinder parsing ([bf81c51](https://github.com/Toninoba/Raytracer/commit/bf81c51298610ca3d54a0a8512ee1f3991c5cb49))
* **world-parser:** add json-parser ([f3c99a3](https://github.com/Toninoba/Raytracer/commit/f3c99a3e8d080b686f4482f3b6dad087ab16fe39))
* **world-parser:** add parsing functionality ([9731400](https://github.com/Toninoba/Raytracer/commit/9731400eeafc220a60237414453266a3f42c9447))
* **world-parser:** add path parsing for executable ([8040484](https://github.com/Toninoba/Raytracer/commit/804048461a626008f5c341a2e026a86ba5a11025))
* **world-parser:** add tokenizer functionality ([d6594d9](https://github.com/Toninoba/Raytracer/commit/d6594d9bf5ea9de613381f8c007d7c3b746c3ddd))
* **world-parser:** add WorldBuilder with Shape identifying ([76b18b3](https://github.com/Toninoba/Raytracer/commit/76b18b399a186a4964e55b1da1b702fd3403275a))
* **world-parser:** implement camera, pattern and light creation ([5f10ec7](https://github.com/Toninoba/Raytracer/commit/5f10ec74a91e50a553fab4e6b54211e938d43c8f))
* **world-parser:** update JsonValue to ease work ([24d4c67](https://github.com/Toninoba/Raytracer/commit/24d4c6793368b58469a4aa26a56057370c4a98c7))


### Bug Fixes

* add support for MSVC ([896ee49](https://github.com/Toninoba/Raytracer/commit/896ee494051624117dc139a2e583a94c1d26fe9b))
* change sqrtf to sqrt ([6bedc2b](https://github.com/Toninoba/Raytracer/commit/6bedc2bb2355799aa3f2b326d0f3ad148ea01466))
* fix broken tests ([2f1b079](https://github.com/Toninoba/Raytracer/commit/2f1b079611c15c0fd85b7c7c4dff52ceeb798238))
* fix broken tests ([49a62b6](https://github.com/Toninoba/Raytracer/commit/49a62b600200f79a9747cc22e7790ae580a87e49))
* fix cmake not building SIMD intrinsics for debug ([859dfab](https://github.com/Toninoba/Raytracer/commit/859dfabf8189c44aeb7655927ec43eba21c7c6a1))
* fix EPSIOLON being to small ([ed57811](https://github.com/Toninoba/Raytracer/commit/ed578117af981b0b68db8f756ab3c6183ec9b881))
* fix missing inlcude in window main ([3817519](https://github.com/Toninoba/Raytracer/commit/3817519d293c5ac6f62cd79b98d38e4aef64d816))
* **lib:** fix shadow constant now being lower for precision purpose ([0dfbe27](https://github.com/Toninoba/Raytracer/commit/0dfbe27e1bc6494377980a7da92ca58f20e00b5a))

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
