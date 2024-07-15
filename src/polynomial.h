#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include <numeric>
#include <vector>

#include <inttypes.h>

#include "concept.h"

template <Polynomialable Element>
class Polynomial {
private:
	using Coefficient = std::vector<Element>;
	using NewtonOutput = std::pair<double, bool>;
	using PolynomialRoot = std::vector<double>;

	template <Numberable Number>
	[[nodiscard]] static constexpr Number round(Number number, uint16_t precision) noexcept;

	template <typename Float>
		requires std::floating_point<Float>
	[[nodiscard]] static constexpr bool
	compare_with_precision(Float number1, Float number2, uint16_t precision) noexcept;

	[[nodiscard]] static inline int64_t create_random_number(int64_t begin, int64_t end) noexcept;

	[[nodiscard]] PolynomialRoot solve_quadratic_equation(uint16_t precision = 6) const;

	[[nodiscard]] PolynomialRoot solve_greater_power(double guess, uint16_t max_iteration, uint16_t precision) const;

	[[nodiscard]] NewtonOutput solve_by_newton(double guess, uint16_t max_iteration, uint16_t precision) const;

	void simplify_by_horner(NewtonOutput info);

	static constexpr double NOT_FOUND = std::numeric_limits<double>::min_exponent10;
	Coefficient coefficients;

public:
	Polynomial();

	explicit Polynomial(Coefficient coefficients);

	Polynomial(const Polynomial& other);

	Polynomial(Polynomial&& other) noexcept;

	Polynomial& operator=(const Polynomial& another) = default;


	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> sum(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator+(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	inline Polynomial<Element> operator+(const OtherElement& other) const;
	template <typename OtherElement>
	inline Polynomial<Element>& operator+=(const Polynomial<OtherElement>& other);

	Polynomial<Element> operator-() const;

	template <typename OtherElement>
	[[nodiscard]] Polynomial<Element> submission(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator-(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	inline Polynomial<Element> operator-(const OtherElement& other) const;
	template <typename OtherElement>
	Polynomial<Element>& operator-=(const Polynomial<OtherElement>& other);

	template <typename OtherElement>
		requires MultipleableDifferentTypeReturnFirstType<Element, OtherElement>
	[[nodiscard]] Polynomial<Element> multiple(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator*(const OtherElement& other) const;
	template <typename OtherElement>
	inline Polynomial<Element>& operator*=(const OtherElement& other);

	[[nodiscard]] Polynomial<Element> power(uint64_t number) const;
	[[nodiscard]] inline Polynomial<Element>& power_equal(uint64_t number);

	[[nodiscard]] inline Polynomial<Element> derivate() const;
	[[nodiscard]] inline Polynomial<Element>& derivate_equal();

	template <Numberable Number>
	[[nodiscard]] Number set_value(Number value) const;

	[[nodiscard]] PolynomialRoot solve(double guess = 0, uint16_t max_iteration = 100, uint16_t precision = 6) const;

	Element& at(size_t index);


	Element& operator[](size_t index);
};


#include "polynomial-tmp.h"


#endif//MATRIX_POLYNOMIAL_H
