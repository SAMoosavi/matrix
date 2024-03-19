#ifndef MATRIX_POLYNOMIAL_INL_H
#define MATRIX_POLYNOMIAL_INL_H

#include "Polynomial.h"
#include <cmath>

bool Polynomial::compare_with_precision(const long double &num1, const long double &num2, const int &precision) {
    long double diff = std::abs(num1 - num2);
    long double epsilon = std::pow(10, -precision);

    return diff < epsilon;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
    for (auto& expr: polynomial.all_expressions)
        os << expr << ' ';
    return os;
}

#endif //MATRIX_POLYNOMIAL_INL_H
