#ifndef MATRIX_POLYNOMIAL_INL_H
#define MATRIX_POLYNOMIAL_INL_H

#include "Polynomial.h"

Polynomial::PolynomailVariableMaxPower Polynomial::find_variables(const Expression &expression) {
    return expression.variables();
}

#endif //MATRIX_POLYNOMIAL_INL_H
