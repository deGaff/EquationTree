//
// Created by d3Gaff on 29.03.2022.
//

#ifndef CALC_BINARYOPERATIONS_H
#define CALC_BINARYOPERATIONS_H
#include <cmath>


template <typename L, typename R>
struct SUM {
    auto operator () (const L lhs, const R rhs) const {
        return lhs + rhs;
    }
};

template <typename L, typename R>
struct SUBTR {
    auto operator () (const L lhs, const R rhs) const {
        return lhs - rhs;
    }
};

template <typename L, typename R>
struct MULT {
    auto operator () (const L lhs, const R rhs) const {
        return lhs * rhs;
    }
};

template <typename L, typename R>
struct DIV {
    auto operator () (const L lhs, const R rhs) const {
        return lhs / rhs;
    }
};

template <typename L, typename R>
struct DEG {
    auto operator () (const L lhs, const R rhs) const {
        return pow(lhs, rhs);
    }
};
#endif //CALC_BINARYOPERATIONS_H
