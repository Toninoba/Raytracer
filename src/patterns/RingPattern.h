//
// Created by tobi on 06.10.26.
//

#ifndef RAYTRACER_RINGPATTERN_H
#define RAYTRACER_RINGPATTERN_H
#include "Pattern.h"


class RingPattern : public Pattern{

public:

    RingPattern(const Color& a, const Color& b) : Pattern(a,b){}

    [[nodiscard]] Color localPatternAt(const Vec<float, 4> &point) const override;

};


#endif //RAYTRACER_RINGPATTERN_H
