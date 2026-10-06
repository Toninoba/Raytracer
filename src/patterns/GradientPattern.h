//
// Created by tobi on 06.10.26.
//

#ifndef RAYTRACER_GRADIENTPATTERN_H
#define RAYTRACER_GRADIENTPATTERN_H
#include "Pattern.h"


class GradientPattern : public Pattern{
public:

    GradientPattern(const Color& a, const Color& b) : Pattern(a, b) {}

    [[nodiscard]] Color localPatternAt(const Vec<float, 4> &point) const override;

};


#endif //RAYTRACER_GRADIENTPATTERN_H
