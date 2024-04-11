#include "RationalExpression.h"

RationalExpression::RationalExpression(Polynomial numerator, Polynomial denominator) :
        numerator(std::move(numerator)),
        denominator(std::move(denominator)) {}

RationalExpression::RationalExpression(const RationalExpression &another) :
        numerator(another.numerator),
        denominator(another.denominator) {}

RationalExpression::RationalExpression(RationalExpression &&another) noexcept :
        numerator(std::move(another.numerator)),
        denominator(std::move(another.denominator)) {}
