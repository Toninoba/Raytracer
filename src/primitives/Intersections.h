//
// Created by tobi on 01.10.26.
//

#ifndef RAYTRACER_INTERSECTIONS_H
#define RAYTRACER_INTERSECTIONS_H
#include <algorithm>
#include <vector>

#include "Intersection.h"


class Intersections {
public:

    std::size_t count = 0;


    Intersections() = default;

    template<std::convertible_to<Intersection> ...Args>
    Intersections(Args... intersections) : _vec{intersections...}, _isSorted(false) {
        count = _vec.size();
    }

    void add(const Intersection& intersection) {
        _vec.push_back(intersection);
        count++;
        _isSorted = false;
    }
    
    void add(const Intersections& other) {
        _vec.insert(_vec.end(), other._vec.begin(), other._vec.end());
        count += other.count;
        _isSorted = false;
    }

    constexpr Intersection& operator[](std::size_t i) {
        return _vec[i];
    }

    constexpr const Intersection& operator[](std::size_t i) const {
        return _vec[i];
    }

    std::optional<Intersection> hit() {
        
        if (!_isSorted) {
            std::sort(_vec.begin(), _vec.end());
            _isSorted = true;
        }

        auto it = std::lower_bound(_vec.begin(), _vec.end(), 0.0f,
            [](const Intersection& intersect, float value) {
                return intersect.t < value;
            });

        if (it != _vec.end()) {
            return *it;
        }

        return std::nullopt;
    }
    
    void sort() {
        std::sort(_vec.begin(), _vec.end());
        _isSorted = true;
    }



private:
    std::vector<Intersection> _vec;
    
    bool _isSorted;


};


#endif //RAYTRACER_INTERSECTIONS_H
