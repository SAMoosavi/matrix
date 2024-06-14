#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include <cfloat>
#include <cstdint>

#include <random>
#include <vector>

#include "concept.h"

template <Polynomialable Element>
class Polynomial {
private:
	typedef std::vector<Element> Coefficient;
	typedef std::pair<double, bool> NewtonOutput;
	typedef std::vector<double> PolynomialRoot;

	template <typename Number>
	[[nodiscard]] static inline std::enable_if_t<std::is_arithmetic_v<Number>, Number>
	round(Number number, uint16_t precision);

	template <typename Float>
	[[nodiscard]] static inline std::enable_if_t<std::is_floating_point_v<Float>, bool>
	compare_with_precision(Float number1, Float number2, uint16_t precision);

	[[nodiscard]] static inline int64_t create_random_number(int64_t begin, int64_t end);

	[[nodiscard]] PolynomialRoot solve_quadratic_equation(uint16_t precision = 6) const;

	[[nodiscard]] PolynomialRoot solve_greater_power(double guess, uint16_t max_iteration, uint16_t precision) const;

	[[nodiscard]] NewtonOutput solve_by_newton(double guess, uint16_t max_iteration, uint16_t precision) const;

	void simplify_by_horner(NewtonOutput info);

	static constexpr double NOT_FOUND = LDBL_MIN_10_EXP;
	Coefficient coefficients;

public:
	explicit Polynomial(const Coefficient& coefficients);

	Polynomial(const Polynomial& other);

	Polynomial(Polynomial&& other) noexcept;

	inline Polynomial& operator=(const Polynomial& another) = default;


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

	template <typename Number>
	[[nodiscard]] std::enable_if_t<std::is_arithmetic_v<Number>, Number>
	set_value(Number value) const;

	[[nodiscard]] PolynomialRoot solve(double guess = 0, uint16_t max_iteration = 100, uint16_t precision = 6) const;

	Element& at(size_t index);


	Element& operator[](size_t idx);
};


#include "polynomial-temp.h"


#endif//MATRIX_POLYNOMIAL_H
