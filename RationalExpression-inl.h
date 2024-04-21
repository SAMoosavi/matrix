#ifndef MATRIX_RATIONALEXPRESSION_INL_H
#define MATRIX_RATIONALEXPRESSION_INL_H

#include "RationalExpression.h"

Polynomial RationalExpression::calculate_common_denominator(const Polynomial &another) const {
    return another * denominator;
}

bool RationalExpression::operator==(const RationalExpression &another) const {
    const auto temp1 = numerator * another.denominator;
    const auto temp2 = denominator * another.numerator;

    return temp1 == temp2;
}

RationalExpression &RationalExpression::operator+=(const RationalExpression &another) {
    denominator = calculate_common_denominator(another.denominator);
    numerator *= another.denominator;
    numerator += another.numerator * denominator;

    return *this;
}

RationalExpression &RationalExpression::operator-=(const RationalExpression &another) {
    denominator = calculate_common_denominator(another.denominator);
    numerator *= another.denominator;
    numerator -= another.numerator * denominator;

    return *this;
}

RationalExpression &RationalExpression::operator*=(const RationalExpression &another) {
    numerator *= another.numerator;
    denominator *= another.denominator;

    return *this;
}

RationalExpression &RationalExpression::operator/=(const RationalExpression &another) {
    if (another.numerator == Polynomial(0))
        throw std::runtime_error("division numerator could not be zero");
    numerator *= another.denominator;
    denominator *= another.numerator;

    return *this;
}

RationalExpression &RationalExpression::power_equal(const int64_t &power) {
    numerator.power_equal(power);
    denominator.power_equal(power);

    return *this;
}

RationalExpression &RationalExpression::derivate_equal() {
    auto temp = numerator * denominator.derivate(1);
    numerator.derivate_equal(1) *= denominator;
    numerator += temp;

    denominator.power_equal(2);
}

RationalExpression RationalExpression::operator+(const RationalExpression &another) const {
    auto temp = *this;
    return std::move(temp += another);
}

RationalExpression RationalExpression::operator-(const RationalExpression &another) const {
    auto temp = *this;
    return std::move(temp -= another);
}

RationalExpression RationalExpression::operator*(const RationalExpression &another) const {
    auto temp = *this;
    return std::move(temp *= another);
}

RationalExpression RationalExpression::operator/(const RationalExpression &another) const {
    auto temp = *this;
    return std::move(temp /= another);
}

RationalExpression RationalExpression::power(const int64_t &power) const {
    auto temp = *this;
    return std::move(temp.power_equal(power));
}

RationalExpression RationalExpression::derivate() const {
    auto temp = *this;
    return std::move(temp.derivate_equal());
}

long double RationalExpression::set_value(const std::vector<std::pair<char, double>> &values) const {
    auto denominator_response = denominator.set_value(values);
    if (denominator_response == 0)
        throw std::runtime_error("denominator should not be zero");
    return numerator.set_value(values) / denominator_response;
}

long double RationalExpression::set_value(const std::pair<char, double> &values) const {
    auto denominator_response = denominator.set_value(values);
    if (denominator_response == 0)
        throw std::runtime_error("denominator should not be zero");
    return numerator.set_value(values) / denominator_response;
}


#endif //MATRIX_RATIONALEXPRESSION_INL_H
