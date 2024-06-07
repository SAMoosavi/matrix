#ifndef MATRIX_POLYNOMIAL_H
#define MATRIX_POLYNOMIAL_H

#include <cstdint>

#include <vector>

#include "concept.h"

template <Polynomialable Element>
class Polynomial {
private:
	typedef std::vector<Element> Coefficient;

	Coefficient coefficients;

public:
	explicit Polynomial(const Coefficient& coefficients);

	Polynomial(const Polynomial& other);

	Polynomial(Polynomial&& other) noexcept;

	inline Polynomial& operator=(const Polynomial& another) = default;

	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	Polynomial<Element> sum(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator+(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	inline Polynomial<Element> operator+(const OtherElement& other) const;
	template <typename OtherElement>
	inline Polynomial<Element>& operator+=(const Polynomial<OtherElement>& other);

	Polynomial<Element> operator-() const;

	template <typename OtherElement>
	Polynomial<Element> submission(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator-(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	inline Polynomial<Element> operator-(const OtherElement& other) const;
	template <typename OtherElement>
	Polynomial<Element>& operator-=(const Polynomial<OtherElement>& other);

	template <typename OtherElement>
		requires MultipleableDifferentTypeReturnFirstType<Element, OtherElement>
	Polynomial<Element> multiple(const Polynomial<OtherElement>& other) const;
	template <typename OtherElement>
	inline Polynomial<Element> operator*(const OtherElement& other) const;
	template <typename OtherElement>
	inline Polynomial<Element>& operator*=(const OtherElement& other);

	Polynomial<Element> power(uint64_t number) const;
	inline Polynomial<Element>& power_equal(uint64_t number);


	inline Polynomial<Element> derivate(uint64_t degree) const;
	inline Polynomial<Element>& derivate_equal(uint64_t degree = 1);

	Element& at(size_t index);


	Element& operator[](size_t idx);
};


#include "polynomial-temp.h"


#endif//MATRIX_POLYNOMIAL_H
