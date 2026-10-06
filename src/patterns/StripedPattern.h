//
// Created by tobi on 06.10.26.
//

#ifndef RAYTRACER_STRIPEDPATTERN_H
#define RAYTRACER_STRIPEDPATTERN_H

#include "Pattern.h"

class StripedPattern : public Pattern{
public:

    StripedPattern(const Color& a, const Color& b) {
        _a = a;
        _b = b;
    }

    [[nodiscard]] Color localPatternAt(const Vec<float, 4> &point) const override;

};


#endif //RAYTRACER_STRIPEDPATTERN_H
