#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include <cinttypes>

#include <numeric>
#include <vector>

#include "concept.h"

template <Polynomialable Element>
class Polynomial
{
private:
	using Coefficient = std::vector<Element>;
	using NewtonOutput = std::pair<double, bool>;
	using PolynomialRoot = std::vector<double>;

public:
	Polynomial() = default;

	explicit Polynomial(const Coefficient& coefficients);

	Polynomial(const Polynomial& other) = default;
	Polynomial(Polynomial&& other) noexcept = default;

	~Polynomial() = default;

	Polynomial& operator=(const Polynomial& another) = default;
	Polynomial& operator=(Polynomial&& another) noexcept = default;

	bool operator==(const Polynomial<Element>& other) const = default;

	// TODO: Add to helper
	template <typename Float>
		requires std::floating_point<Float>
	[[nodiscard]] static constexpr bool compare_with_precision(Float number1, Float number2,
			uint16_t precision) noexcept;

	template <typename OtherElement>
		requires SumableDifferentType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> sum(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	[[nodiscard]] Polynomial<Element> operator+(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SumableDifferentType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> operator+(const OtherElement& other) const;
	template <typename OtherElement>
	Polynomial<Element>& operator+=(const Polynomial<OtherElement>& other);
	Polynomial<Element>& operator+=(const Element& new_coefficient);

	[[nodiscard]] Polynomial<Element> operator-() const;

	template <typename OtherElement>
	[[nodiscard]] Polynomial<Element> submission(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	[[nodiscard]] Polynomial<Element> operator-(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SumableDifferentType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> operator-(const OtherElement& other) const;
	template <typename OtherElement>
	Polynomial<Element>& operator-=(const Polynomial<OtherElement>& other);
	Polynomial<Element>& operator-=(const Element& new_coefficient);

	template <typename OtherElement>
		requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> multiple(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires MultiplableDifferentType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> operator*(const OtherElement& other) const;
	template <typename OtherElement>
	[[nodiscard]] Polynomial<Element> operator*(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	Polynomial<Element>& operator*=(const OtherElement& other);
	template <typename OtherElement>
	Polynomial<Element>& operator*=(const Polynomial<OtherElement>& other);

	[[nodiscard]] Polynomial<Element> power(uint64_t number) const;
	Polynomial<Element>& power_equal(uint64_t number);

	[[nodiscard]] Polynomial<Element> derivative() const;
	Polynomial<Element>& derivative_equal();

	template <Numberable Number>
	[[nodiscard]] Number set_value(Number value) const;

	[[nodiscard]] PolynomialRoot solve(double guess = 0, uint16_t max_iteration = 100, uint16_t precision = 6) const;

	[[nodiscard]] Element& at(size_t index);
	[[nodiscard]] const Element& at(size_t index) const;

	[[nodiscard]] Element& operator[](size_t index);
	[[nodiscard]] const Element& operator[](size_t index) const;

private:
	[[nodiscard]] constexpr Polynomial<Element> sum_smaller_degree_with_greater(Coefficient greater_degree_coefficients,
			const Coefficient& smaller_degree_coefficients) const noexcept;

	[[nodiscard]] PolynomialRoot solve_quadratic_equation(uint16_t precision = 6) const;

	[[nodiscard]] PolynomialRoot solve_greater_power(double guess, uint16_t max_iteration, uint16_t precision) const;

	[[nodiscard]] NewtonOutput solve_by_newton(double guess, uint16_t max_iteration, uint16_t precision) const;

	void simplify_by_horner(NewtonOutput info);

	static constexpr double NOT_FOUND = std::numeric_limits<double>::min_exponent10;
	// Biggest to smallest` degree
	Coefficient coefficients;
};

template <typename Element, typename OtherElement>
	requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement>
constexpr Polynomial<Element> operator*(const OtherElement& other, const Polynomial<Element>& polynomial);

template <typename Element, typename OtherElement>
	requires MultiplableDifferentTypeReturnSecondType<Element, OtherElement> and Polynomialable<OtherElement>
constexpr Polynomial<OtherElement> operator*(const OtherElement& other, const Polynomial<Element>& polynomial);

#include "polynomial-tmp.h"

#endif
