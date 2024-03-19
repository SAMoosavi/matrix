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

std::ostream &operator<<(std::ostream &os, const Expression &expr) {
    if (expr._constant < 0)
        os << "- ";
    else
        os << "+ ";
    os << std::abs(expr._constant);
    for (auto &var: expr._variables)
        os << '*' << var.variable << '^' << var.power * expr._power;
    return os;
}

bool Expression::operator==(const Expression &expression) const {
    bool result = true;
    if (_constant != expression._constant)
        result = false;
    else
        result = is_similar_terms(expression);
    return result;
}

Expression &Expression::power_equal(const int64_t &pow) {
    _power *= pow;
    return *this;
}

Expression Expression::power(const int64_t &pow) const {
    Expression another = *this;
    another.power_equal(pow);
    return another;
}


bool Expression::Variable::operator==(const Expression::Variable &another) const {
    return (this->variable == another.variable) && (this->power == another.power);
}

#endif //MATRIX_EXPRESSION_INL_H
