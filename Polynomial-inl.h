#ifndef MATRIX_POLYNOMIAL_INL_H
#define MATRIX_POLYNOMIAL_INL_H

#include "Polynomial.h"
#include <cmath>
#include <iostream>

// Internal_Monomial

constexpr bool Polynomial::Internal_Monomial::is_alpha(const char &ch) noexcept {
    return ch - 'a' <= 'z' - 'a';
}

constexpr bool Polynomial::Internal_Monomial::is_number(const char &ch) noexcept {
    return ch - '0' <= '9' - '0';
}

double Polynomial::Internal_Monomial::get_coefficient() const {
    return coefficient;
}

const std::vector<Polynomial::Variable> &Polynomial::Internal_Monomial::get_variables() const {
    return variables;
}

bool Polynomial::Internal_Monomial::operator==(const Internal_Monomial &expression) const {
    bool result = true;
    if (coefficient != expression.coefficient)
        result = false;
    else
        result = is_similar_terms(expression);
    return result;
}

Polynomial::Internal_Monomial &Polynomial::Internal_Monomial::power_equal(const uint64_t &pow) {
    for (auto &var: variables)
        var.power *= pow;
    return *this;
}

Polynomial::Internal_Monomial Polynomial::Internal_Monomial::operator+(const Internal_Monomial &expression) const {
    return Internal_Monomial(*this) += expression;
}

Polynomial::Internal_Monomial Polynomial::Internal_Monomial::operator-(const Internal_Monomial &expression) const {
    return Internal_Monomial(*this) -= expression;
}

Polynomial::Internal_Monomial Polynomial::Internal_Monomial::operator*(const Internal_Monomial &expression) const {
    return Internal_Monomial(*this) *= expression;
}

Polynomial::Internal_Monomial Polynomial::Internal_Monomial::operator/(const Internal_Monomial &expression) const {
    return Internal_Monomial(*this) /= expression;
}

Polynomial::Internal_Monomial Polynomial::Internal_Monomial::power(const uint64_t &pow) const {
    Internal_Monomial another = *this;
    another.power_equal(pow);
    return another;
}

void Polynomial::Internal_Monomial::set_coefficient(double coefficient) {
    this->coefficient = coefficient;
}

void Polynomial::Internal_Monomial::increase_power() {
    for (auto &var: variables)
        ++var.power;
}

void Polynomial::Internal_Monomial::decrease_power() {
    size_t i = 0;
    while (i < variables.size()) {
        if (variables[i].power == 1) {
            std::swap(variables[i], variables[variables.size() - 1]);
            variables.pop_back();
        } else{
            --variables[i].power;
            ++i;
        }
    }
}

bool Polynomial::Variable::operator==(const Polynomial::Variable &another) const {
    return (this->variable == another.variable) && (this->power == another.power);
}


// Polynomial
Polynomial Polynomial::operator+(const Polynomial &another) const {
    return std::move(Polynomial(*this) += another);
}

Polynomial Polynomial::operator-(const Polynomial &another) const {
    return std::move(Polynomial(*this) -= another);
}

Polynomial Polynomial::operator*(const Polynomial &another) const {
    return std::move(Polynomial(*this) *= another);
}

Polynomial Polynomial::operator/(const Monomial &another) const {
    return std::move(Polynomial(*this) /= another);
}

Polynomial Polynomial::power(const uint64_t &power) const {
    Polynomial another = *this;
    another.power_equal(power);
    return std::move(another);
}

Polynomial Polynomial::derivate(uint64_t degree) const {
    Polynomial another = *this;
    return std::move(another.derivate_equal(degree));
}

bool Polynomial::compare_with_precision(const long double &num1, const long double &num2, const int &precision) {
    long double diff = std::abs(num1 - num2);
    long double epsilon = std::pow(10, -precision);

    return diff < epsilon;
}

void Polynomial::save_newton_answer(Polynomial::PolynomialRoot &result, const Polynomial::NewtonOutput &answer,
                                    Polynomial &polynomial) const {
    uint16_t equation_calculation_number = 1;
    if (answer.is_repeated)
        equation_calculation_number = 2;
    for (uint16_t i = 0; i < equation_calculation_number; ++i) {
        result.emplace_back(answer.root);
        polynomial.all_monomials = polynomial.calculate_quotient(answer.root);
    }
}

void Polynomial::save_fixed_point_answer(Polynomial::PolynomialRoot &result, long double answer,
                                         Polynomial &polynomial) const {
    result.emplace_back(answer);
    polynomial.all_monomials = polynomial.calculate_quotient(answer);
}

template<typename T>
T Polynomial::round(const T &number, const uint16_t &precision) {
    double precision_number = std::pow(10.0, precision);
    return std::round(number * precision_number) / precision_number;
}

Polynomial Polynomial::create_g_function() const {
    std::vector<Internal_Monomial> expressions = all_monomials;
    expressions.emplace_back(1, 'x', 1);
    Polynomial g(std::move(expressions));
    return std::move(g);
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
    bool flag = false;
    for (auto &expr: polynomial.all_monomials) {
        if (expr.get_coefficient() < 0)
            os << '-';
        else
            os << '+';
        if (flag)
            os << ' ';
        os << std::abs(expr.get_coefficient());
        for (auto &var: expr.get_variables())
            os << '*' << var.variable << '^' << var.power;

        os << ' ';
        flag = true;
    }
    return os;
}

#endif //MATRIX_POLYNOMIAL_INL_H
