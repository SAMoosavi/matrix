#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include "Expression.h"

class Polynomial {
public:
    typedef std::vector<double> PolynomialRoot;
    typedef std::vector<Expression::Variable> PolynomailVariableMaxPower;

    explicit Polynomial(std::vector<Expression> expression);

    explicit Polynomial(Expression expression);

    Polynomial(double constant, const Polynomial &polynomial, const int64_t &power);

    Polynomial &operator+=(const Polynomial &another);

    Polynomial &operator-=(const Polynomial &another);

    Polynomial &operator*=(const Polynomial &another);

    Polynomial &operator/=(const Expression &another);

    Polynomial &power_equal(const int64_t& power);

    Polynomial &operator=(const Polynomial &another) = default;

    Polynomial operator+(const Polynomial &another) const;

    Polynomial operator-(const Polynomial &another) const;

    Polynomial operator*(const Polynomial &another) const;

    Polynomial operator/(const Expression &another) const;

    Polynomial power(const int64_t& power) const;

    PolynomialRoot solve(double guess = 0) const;

    Polynomial derivate(uint64_t degree) const;

    long double set_value(const std::vector<std::pair<char, double>> &values) const;

    long double set_value(const std::pair<char, double> &values) const;


    friend inline std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial);

private:
    std::vector<Expression> all_expressions;

    static void delete_repeated_expressions(std::vector<Expression> &expression);

    static PolynomailVariableMaxPower create_variables(const std::vector<int64_t> &alphabets);

    static inline bool compare_with_precision(const long double &num1, const long double &num2, const int &precision);

    static int32_t create_random_number(const int32_t &max_value = INT32_MAX);

    Expression *find_similar_expression(const Expression &expression) const;

    bool check_solve_validation(const PolynomailVariableMaxPower &variableMaxPower) const;

    PolynomailVariableMaxPower find_variables_and_max_power() const;

    Expression *find_expression_by_power(int64_t target_power) const;

    PolynomialRoot solve_linear_equation() const;

    PolynomialRoot solve_quardatic_equation() const;

    PolynomialRoot find_cubic_roots(double delta, double p, double q, double a) const;

    PolynomialRoot solve_cubic_equation() const;

    PolynomialRoot solve_by_newton_technique(double guess) const;

    int64_t calculate_constant_of_derivated(int64_t power, uint64_t degree) const;
};

#include "Polynomial-inl.h"

#endif //MATRIX_POLYNOMIAL_H