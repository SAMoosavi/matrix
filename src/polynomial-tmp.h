#ifndef MATRIX_POLYNOMIAL_TEMP_H
#define MATRIX_POLYNOMIAL_TEMP_H

#include <random>

#include "polynomial-helper.h"
#include "polynomial.h"

template <Polynomialable Element>
Polynomial<Element>::Polynomial(const Coefficient &coefficients)
: coefficients(coefficients)
{
}

template <Polynomialable Element>
template <typename Float>
	requires std::floating_point<Float>
constexpr bool Polynomial<Element>::compare_with_precision(Float number1, Float number2, uint16_t precision) noexcept
{
	Float diff = std::abs(number1 - number2);
	Float epsilon = std::pow(10, -precision);

	return diff < epsilon;
}

template <Polynomialable Element>
Polynomial<Element>::NewtonOutput Polynomial<Element>::solve_by_newton(double guess, uint16_t max_iteration,
		uint16_t precision) const
{
	NewtonOutput result;
	const Polynomial<Element> derived = derivative();
	double previous_answer = NOT_FOUND;
	double current_answer = guess;
	double polynomial_answer = NAN;
	double derived_answer = NAN;
	uint16_t iteration = 0;
	while (!compare_with_precision(previous_answer, current_answer, precision) && iteration < max_iteration)
	{
		previous_answer = current_answer;
		polynomial_answer = set_value(previous_answer);
		derived_answer = derived.set_value(previous_answer);
		if (compare_with_precision(polynomial_answer, 0.0, precision))
			break;
		if (compare_with_precision(derived_answer, 0.0, precision / 2))
		{
			// TODO: it could replace with 2 or three as precision. check this
			if (compare_with_precision(polynomial_answer, 0.0, precision / 2))
				result.second = true;
			else
				current_answer = polynomial_helper::create_random_number(static_cast<int64_t>(guess - guess * 0.1),
						static_cast<int64_t>(guess + guess * 0.1));
		}
		else
		{
			current_answer = previous_answer - (polynomial_answer / derived_answer);
		}
		++iteration;
	}
	if (compare_with_precision(set_value(current_answer), 0.0, precision / 2))
		result.first = polynomial_helper::round(current_answer, precision);
	return result;
}

template <Polynomialable Element>
void Polynomial<Element>::simplify_by_horner(NewtonOutput info)
{
	Element temp = *coefficients.rbegin();
	for (auto it = (coefficients.rbegin() + 1); it != coefficients.rend(); ++it)
	{
		Element current_coefficient = *it;
		temp = temp * info.first + current_coefficient;
		*it = temp;
	}

	coefficients.erase(coefficients.begin());
}

template <Polynomialable Element>
auto Polynomial<Element>::solve_quadratic_equation(uint16_t precision) const -> PolynomialRoot
{
	PolynomialRoot result;
	Element coefficient = coefficients[0];
	Element one_power = coefficients[1];
	Element two_power = coefficients[2];

	// need tp support sqrt
	Element delta = (one_power * one_power) - (4 * two_power * coefficient);

	if (delta >= 0)
	{
		result.emplace_back(polynomial_helper::round(((-1 * one_power) + sqrt(delta)) / (2 * two_power), precision));
		result.emplace_back(polynomial_helper::round(((-1 * one_power) - sqrt(delta)) / (2 * two_power), precision));
	}

	return result;
}

template <Polynomialable Element>
Polynomial<Element>::PolynomialRoot Polynomial<Element>::solve_greater_power(double guess, uint16_t max_iteration,
		uint16_t precision) const
{
	PolynomialRoot result;
	Polynomial<Element> temp_polynomial(*this);
	NewtonOutput temp_newton;
	while (temp_polynomial.coefficients.size() > 3)
	{
		temp_newton = temp_polynomial.solve_by_newton(guess, max_iteration, precision);
		if (temp_newton.first == NOT_FOUND)
			guess = polynomial_helper::create_random_number(static_cast<int64_t>(guess - guess * 0.1),
					static_cast<int64_t>(guess + guess * 0.1));
		else
		{
			temp_polynomial.simplify_by_horner(temp_newton);
			result.emplace_back(temp_newton.first);
			if (temp_newton.second)
				result.emplace_back(temp_newton.first);
		}
	}
	PolynomialRoot temp = temp_polynomial.solve(guess, max_iteration, precision);
	result.insert(result.end(), temp.begin(), temp.end());
	return result;
}

template <Polynomialable Element>
template <typename OtherElement>
	requires SumableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::sum(const Polynomial<OtherElement> &other) const
{
	Coefficient coefficient_of_result = coefficients;
	for (size_t i = 0; i < other.coefficients.size(); i++)
	{
		if (i < coefficient_of_result.size())
			coefficient_of_result[i] += other.coefficients[i];
		else
			coefficient_of_result.emplace_back(Element() + other.coefficients[i]);
	}
	return Polynomial(coefficient_of_result);
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> Polynomial<Element>::operator+(const Polynomial<OtherElement> &other) const
{
	return sum(other);
}

template <Polynomialable Element>
template <typename OtherElement>
	requires SumableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::operator+(const OtherElement &other) const
{
	Polynomial new_polynomial(*this);
	new_polynomial.coefficients[0] += other;
	return new_polynomial;
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> &Polynomial<Element>::operator+=(const Polynomial<OtherElement> &other)
{
	*this = sum(other);
	return *this;
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::operator+=(const Element &new_coefficient)
{
	coefficients[0] += new_coefficient;
	return *this;
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::operator-() const
{
	Polynomial new_polynomial(*this);
	for (auto &coeff : new_polynomial.coefficients)
		coeff = -coeff;
	return new_polynomial;
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> Polynomial<Element>::submission(const Polynomial<OtherElement> &other) const
{
	return sum(-other);
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> Polynomial<Element>::operator-(const Polynomial<OtherElement> &other) const
{
	return submission(other);
}

template <Polynomialable Element>
template <typename OtherElement>
	requires SumableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::operator-(const OtherElement &other) const
{
	Polynomial new_polynomial(*this);
	new_polynomial[0] -= other;
	return new_polynomial;
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> &Polynomial<Element>::operator-=(const Polynomial<OtherElement> &other)
{
	*this = submission(other);
	return *this;
}

template <Polynomialable Element>
template <typename OtherElement>
	requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::multiple(const Polynomial<OtherElement> &other) const
{
	Coefficient multiple_result_coefficients(coefficients.size() + other.coefficients.size() - 1, Element());
	for (size_t i = 0; i < coefficients.size(); i++)
		for (size_t j = 0; j < other.coefficients.size(); j++)
			multiple_result_coefficients[i + j] += coefficients[i] * other.coefficients[j];

	return Polynomial(multiple_result_coefficients);
}

template <Polynomialable Element>
template <typename OtherElement>
	requires MultiplableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::operator*(const OtherElement &other) const
{
	Polynomial new_polynomial(*this);
	for (auto &coeff : new_polynomial.coefficients)
		coeff *= other;
	return new_polynomial;
}

template <Polynomialable Element>
template <typename OtherElement>
inline Polynomial<Element> Polynomial<Element>::operator*(const Polynomial<OtherElement> &other) const
{
	return multiple(other);
}

template <Polynomialable Element>
template <typename OtherElement>
inline Polynomial<Element> &Polynomial<Element>::operator*=(const OtherElement &other)
{
	*this = *this * other;
	return *this;
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> &Polynomial<Element>::operator*=(const Polynomial<OtherElement> &other)
{
	*this = multiple(other);
	return *this;
}

template <Polynomialable Element>
template <Numberable Number>
Number Polynomial<Element>::set_value(Number value) const
{
	Number result{};
	Number variable_nth_power = 1;
	for (const auto &coeff : coefficients)
	{
		result += variable_nth_power * coeff;
		variable_nth_power *= value;
	}
	return result;
}

template <Polynomialable Element>
Polynomial<Element>::PolynomialRoot Polynomial<Element>::solve(double guess, uint16_t max_iteration,
		uint16_t precision) const
{
	PolynomialRoot result;
	switch (coefficients.size())
	{
		case 0:
			break;
		case 1:
			result.emplace_back(coefficients[0]);
			break;
		case 2:
			result.emplace_back((-coefficients[0]) / coefficients[1]);
			break;
		case 3:
			result = solve_quadratic_equation();
			break;
		default:
			result = solve_greater_power(guess, max_iteration, precision);
			break;
	}

	return result;
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::operator-=(const Element &new_coefficient)
{
	coefficients[0] -= new_coefficient;
	return *this;
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::power(uint64_t number) const
{
	if (number == 0)
		return Polynomial();

	Polynomial result(*this);
	for (uint64_t i = 0; i < number - 1; ++i)
		result *= *this;

	return result;
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::power_equal(uint64_t number)
{
	*this = power(number);
	return *this;
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::derivative() const
{
	Polynomial result(*this);
	result.coefficients.erase(result.coefficients.begin());
	for (size_t i = 0; i < result.coefficients.size(); ++i)
		result.coefficients[i] *= i + 1;
	return result;
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::derivative_equal()
{
	*this = derivative();
	return *this;
}

template <Polynomialable Element>
Element &Polynomial<Element>::at(size_t index)
{
	return coefficients[index];
}

template <Polynomialable Element>
const Element &Polynomial<Element>::at(size_t index) const
{
	return coefficients[index];
}

template <Polynomialable Element>
Element &Polynomial<Element>::operator[](size_t index)
{
	return at(index);
}

template <Polynomialable Element>
const Element &Polynomial<Element>::operator[](size_t index) const
{
	return at(index);
}

template <typename Element, typename OtherElement>
	requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement>
constexpr Polynomial<Element> operator*(const OtherElement &other, const Polynomial<Element> &polynomial)
{
	return polynomial * other;
}

template <typename Element, typename OtherElement>
	requires MultiplableDifferentTypeReturnSecondType<Element, OtherElement> and Polynomialable<OtherElement>
constexpr Polynomial<OtherElement> operator*(const OtherElement &other, const Polynomial<Element> &polynomial)
{
	Polynomial other_polynomial(other);
	return other_polynomial * polynomial;
}

#endif
