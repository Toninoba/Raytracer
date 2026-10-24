//
// Created by tobi on 08.10.26.
//

#ifndef RAYTRACER_TESTPATTERN_H
#define RAYTRACER_TESTPATTERN_H
#include "Pattern.h"


class TestPattern : public Pattern{



public:

    [[nodiscard]] Color localPatternAt(const Vec<float, 4> &point) const override;

};


#endif //RAYTRACER_TESTPATTERN_H
