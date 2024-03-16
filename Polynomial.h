#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include "Expression.h"

class Polynomial {
public:
    explicit Polynomial(std::vector<Expression> expression);

    explicit Polynomial(Expression expression);

    Polynomial& operator+=(const Polynomial &another);

    Polynomial& operator-=(const Polynomial &another);

    Polynomial& operator*=(const Polynomial &another);

    Polynomial& operator/=(const Expression &another);

    Polynomial& operator=(const Polynomial &another) = default;


private:
    std::vector<Expression> all_expressions;

    static void delete_repeated_expressions(std::vector<Expression> &expression);

    Expression *find_expression(const Expression &expression) const;
};


#endif //MATRIX_POLYNOMIAL_H
