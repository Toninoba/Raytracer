//
// Created by tobi on 06.10.26.
//

#ifndef RAYTRACER_CHECKERPATTERN_H
#define RAYTRACER_CHECKERPATTERN_H
#include "Pattern.h"


class CheckerPattern : public Pattern{
public:
    CheckerPattern(const Color& a, const Color& b) : Pattern(a, b) {}

    [[nodiscard]] Color localPatternAt(const Vec<float, 4> &point) const override;

};


#endif //RAYTRACER_CHECKERPATTERN_H
