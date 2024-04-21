#include "RationalExpression.h"
#include <algorithm>

RationalExpression::RationalExpression(Polynomial numerator, Polynomial denominator) :
        numerator(std::move(numerator)),
        denominator(std::move(denominator)) {}

RationalExpression::RationalExpression(const RationalExpression &another) :
        numerator(another.numerator),
        denominator(another.denominator) {}

RationalExpression::RationalExpression(RationalExpression &&another) noexcept :
        numerator(std::move(another.numerator)),
        denominator(std::move(another.denominator)) {}

Polynomial::PolynomialRoot
RationalExpression::solve(double guess, const uint16_t &max_iteration, const uint16_t &precision) const {
    auto numerator_roots = numerator.solve(guess, max_iteration, precision);
    auto denominator_roots = denominator.solve(guess, max_iteration, precision);
    size_t i = 0;
    while (i < numerator_roots.size()) {
        if (std::find(denominator_roots.begin(), denominator_roots.end(),numerator_roots[i]) != denominator_roots.end()) {
            std::swap(numerator_roots[i], numerator_roots[numerator_roots.size() - 1]);
            numerator_roots.pop_back();
        } else
            ++i;
    }

    return numerator_roots;
}



