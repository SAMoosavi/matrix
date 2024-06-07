#ifndef MATRIX_POLYNOMIAL_TEMP_H
#define MATRIX_POLYNOMIAL_TEMP_H

#include "polynomial.h"

template <Polynomialable Element>
Polynomial<Element>::Polynomial(const vector<Element> &coefficients)
	: coefficients(coefficients)
{
}

template <Polynomialable Element>
Polynomial<Element>::Polynomial(const Polynomial &other)
	: coefficients(other, coefficients)
{
}

template <Polynomialable Element>
Polynomial<Element>::Polynomial(Polynomial &&other) noexcept
	: coefficients(std::move(other.coefficients))
{
}

template <Polynomialable Element>
template <typename OtherElement>
	requires SamableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::sum(const Polynomial<OtherElement> &other) const
{
	uint64_t max_length = std::max(coefficients.size(), other.coefficients.size());
	std::vector<Element> temp(max_length);
	for (uint64_t i = 0; i < max_length; ++i) {
		if (coefficients.size() <= i)
			temp[i] = other.coefficients[i];
		else if (other.coefficients.size() <= i)
			temp[i] = coefficients[i];
		else
			temp[i] = coefficients[i] + other.coefficients[i];
	}
	return Polynomial(std::move(temp));
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> Polynomial<Element>::operator+(const Polynomial<OtherElement> &other) const
{
	return sum(other);
}

template <Polynomialable Element>
template <typename OtherElement>
	requires SamableDifferentType<Element, OtherElement>
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
	return this;
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::operator-() const
{
	Polynomial new_polynomial(*this);
	for (auto &coeff: new_polynomial.coefficients)
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
	requires SamableDifferentType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::operator-(const OtherElement &other) const
{
	Polynomial new_polynomial(*this);
	new_polynomial[0] += -other;
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
	requires MultipleableDifferentTypeReturnFirstType<Element, OtherElement>
Polynomial<Element> Polynomial<Element>::multiple(const Polynomial<OtherElement> &other) const
{
	uint64_t max_length = std::max(coefficients.size(), other.coefficients.size());
	Polynomial result(std::vector<Element>(0));
	for (const auto &coeff: coefficients) {
		for (const auto &other_coeff: other.coefficients) {
			result += coeff * other_coeff;
		}
	}
	return Polynomial(std::move(result));
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> Polynomial<Element>::operator*(const OtherElement &other) const
{
	Polynomial new_polynomial(*this);
	for (const auto &coeff: new_polynomial.coefficients)
		coeff *= other;
	return new_polynomial;
}

template <Polynomialable Element>
template <typename OtherElement>
Polynomial<Element> &Polynomial<Element>::operator*=(const OtherElement &other)
{
	*this = multiple(other);
	return this;
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::power(uint64_t number) const
{
	if (number == 0)
		return Polynomial(std::vector<Element>(0));
	Polynomial result(*this);
	for (uint64_t i = 0; i < number - 1; ++i) {
		result *= *this;
	}
	return result;
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::power_equal(uint64_t number)
{
	*this = power(number);
}

template <Polynomialable Element>
Polynomial<Element> Polynomial<Element>::derivate(uint64_t degree) const
{
	Polynomial result(*this);
	result.coefficients.erase(result.coefficients.begin());
	for (size_t i = 0; i < result.coefficients.size(); ++i)
		result.coefficients[i] *= i + 1;
	return std::move(result);
}

template <Polynomialable Element>
Polynomial<Element> &Polynomial<Element>::derivate_equal(uint64_t degree)
{
	*this = derivate(degree);
	return this;
}

template <Polynomialable Element>
Element &Polynomial<Element>::at(size_t index)
{
	return coefficients[index];
}

template <Polynomialable Element>
Element &Polynomial<Element>::operator[](size_t index)
{
	return at(index);
}

#endif//MATRIX_POLYNOMIAL_TEMP_H
