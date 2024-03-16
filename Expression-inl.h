#ifndef MATRIX_EXPRESSION_INL_H
#define MATRIX_EXPRESSION_INL_H

#include "Expression.h"

constexpr bool Expression::is_alpha(const char &ch) noexcept {
    return ch - 'a' <= 'z' - 'a';
}

constexpr bool Expression::is_number(const char &ch) noexcept {
    return ch - '0' <= '9' - '0';
}

double Expression::constant() const {
    return _constant;
}

int64_t Expression::power() const {
    return _power;
}

const std::vector<Expression::Variable> &Expression::variables() const {
    return _variables;
}

bool Expression::Variable::operator==(const Expression::Variable &another) const {
    return (this->variable == another.variable) && (this->power == another.power);
}

#endif //MATRIX_EXPRESSION_INL_H
