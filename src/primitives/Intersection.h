//
// Created by tobi on 01.10.26.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H



class Shape;

class Intersection {
public:

    Intersection(const float t, const Shape* s) : t(t), object(s){}

    float t;
    const Shape* object;

    bool operator<(const Intersection& other) const {
        return t < other.t;
    }

    bool operator==(const Intersection& other) const {
        return t == other.t && object == other.object;
    }

};


#endif //RAYTRACER_INTERSECTION_H
