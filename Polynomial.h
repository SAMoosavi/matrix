#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include "Expression.h"

class Polynomial {
public:
    Polynomial(const std::vector<Expression> expression);
    Polynomial(const Expression expression);

    Polynomial operator+(const Polynomial &expression);

    Polynomial operator-(const Polynomial &expression);

    Polynomial operator*(const Polynomial &expression);

    Polynomial operator/(const Polynomial &expression);


private:
    std::vector<Expression> polynomial;
};


#endif //MATRIX_POLYNOMIAL_H
