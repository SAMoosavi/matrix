#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include "Expression.h"

class Polynomial {
public:
    typedef std::vector<double> PolynomialRoot;
    typedef std::vector<Expression::Variable> PolynomailVariableMaxPower;

    explicit Polynomial(std::vector<Expression> expression);

    explicit Polynomial(Expression expression);

    Polynomial &operator+=(const Polynomial &another);

    Polynomial &operator-=(const Polynomial &another);

    Polynomial &operator*=(const Polynomial &another);

    Polynomial &operator/=(const Expression &another);

    Polynomial &operator=(const Polynomial &another) = default;

    Polynomial operator+(const Polynomial &another) const;

    Polynomial operator-(const Polynomial &another) const;

    Polynomial operator*(const Polynomial &another) const;

    Polynomial operator/(const Expression &another) const;

    PolynomialRoot solve() const;

private:
    std::vector<Expression> all_expressions;

    static void delete_repeated_expressions(std::vector<Expression> &expression);

    static PolynomailVariableMaxPower find_variables(const std::vector<Expression> &expressions);

    static inline PolynomailVariableMaxPower find_variables(const Expression &expression);

    static PolynomailVariableMaxPower create_variables(const std::vector<int64_t> &alphabets);

    Expression *find_similar_expression(const Expression &expression) const;

    bool check_solve_validation(const PolynomailVariableMaxPower& variableMaxPower) const;

    PolynomailVariableMaxPower find_variables_and_max_power() const;

    Expression *find_expression_by_power(int64_t target_power) const;

    PolynomialRoot solve_linear_equation() const;

    PolynomialRoot solve_quardatic_equation() const;

    PolynomialRoot find_cubic_roots(double delta, double p, double q, double a) const;

    PolynomialRoot solve_cubic_equation() const;
};


#endif //MATRIX_POLYNOMIAL_H
