#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <ranges>
#include <vector>

#include "concept.h"

using namespace std;

template <Elementable Element>
class Matrix {
private:
	typedef vector<Element> RowType;
	typedef vector<RowType> TableType;

public:
	Matrix();

	Matrix(size_t row, size_t col);

	template <template <Containerable> typename Container>
	Matrix(const Container<Container<Element>>& matrix);

	TableType get_table() const;
	size_t get_row() const;
	size_t get_col() const;

	template <typename OtherElement>
		requires SamableDifferentType<Element, OtherElement>
	Matrix<Element> sum(const Matrix<OtherElement>& other) const;
	template <typename OtherElement>
	Matrix<Element> operator+(const Matrix<OtherElement>& other) const;
	template <typename OtherElement>
	Matrix<Element>& operator+=(const Matrix<OtherElement>& other);

	Matrix<Element> operator-() const;

	template <typename OtherElement>
	Matrix<Element> submission(const Matrix<OtherElement>& other) const;
	template <typename OtherElement>
	Matrix<Element> operator-(const Matrix<OtherElement>& other) const;
	template <typename OtherElement>
	Matrix<Element>& operator-=(const Matrix<OtherElement>& other);

	template <typename OtherElement>
		requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement>
	Matrix<Element> multiple(const Matrix<OtherElement>& other) const;
	template <typename OtherElement>
		requires(not IsMatrixable<OtherElement>) and MultiplableDifferentType<Element, OtherElement>
	Matrix<Element> multiple(const OtherElement& other) const;
	template <typename OtherElement>
	Matrix<Element> operator*(const OtherElement& other) const;
	template <typename OtherElement>
	Matrix<Element>& operator*=(const OtherElement& other);

	Element at(size_t row_index, size_t col_index);

	RowType operator[](size_t idx) const;

	Element determinant() const;

private:
	RowType& operator[](size_t idx);

	size_t row;
	size_t col;
	TableType table;
};


template <typename Element, typename OtherElement>
	requires(not IsMatrixable<Element>) and (not IsMatrixable<OtherElement>) and MultiplableDifferentType<Element, OtherElement>
Matrix<Element> operator*(const OtherElement& number, const Matrix<Element>& matrix);

#include "matrix-tmp.h"

#endif
