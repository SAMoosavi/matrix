#include "RationalExpression.h"

RationalExpression::RationalExpression(Polynomial numerator, Polynomial denominator) :
        numerator(std::move(numerator)),
        denominator(std::move(denominator)) {}
