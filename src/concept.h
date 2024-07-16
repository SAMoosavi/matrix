#ifndef MATRIX_CONCEPT_H
#define MATRIX_CONCEPT_H

#include <iostream>
#include <ranges>
#include <vector>

using namespace std;
template <typename T>
concept Multiplicationable = requires(T t) {
	{
		t* t
	} -> same_as<T>;
};
template <typename T>
concept AssignMultiplicationable = requires(T t) {
	{
		t *= t
	} -> same_as<T&>;
};

template <typename T, typename U>
concept MultipleAssignableDifferentType = requires(T t, U u) {
	{
		t *= u
	} -> same_as<T&>;
};

template <typename T, typename U>
concept MultiplableDifferentTypeReturnFirstType = requires(T t, U u) {
	{
		t* u
	} -> same_as<T>;
};

template <typename T, typename U>
concept MultiplableDifferentTypeReturnSecondType = requires(T t, U u) {
	{
		u* t
	} -> same_as<T>;
};

template <typename T, typename U>
concept MultiplableDifferentType = requires(T, U) {
	requires MultiplableDifferentTypeReturnSecondType<T, U> or
					 MultiplableDifferentTypeReturnFirstType<T, U> or
					 MultipleAssignableDifferentType<T, U>;
};


template <typename T>
concept Sumable = requires(T t) {
	{
		t + t
	} -> same_as<T>;
};
template <typename T>
concept Symmetryable = requires(T t) {
	{
		-t
	} -> same_as<T>;
	{
		t * -1
	} -> same_as<T>;
	-t == t * -1;
};
template <typename T>
concept AssignSumable = requires(T t) {
	{
		t += t
	} -> same_as<T&>;
};


template <typename T, typename U>
concept SamAssignableDifferentType = requires(T t, U u) {
	{
		t += u
	} -> same_as<T&>;
};

template <typename T, typename U>
concept SumableDifferentTypeReturnFirstType = requires(T t, U u) {
	{
		t + u
	} -> same_as<T>;
};

template <typename T, typename U>
concept SumableDifferentTypeReturnSecondType = requires(T t, U u) {
	{
		u + t
	} -> same_as<T>;
};

template <typename T, typename U>
concept SumableDifferentType = requires(T, U) {
	requires SumableDifferentTypeReturnSecondType<T, U> or
					 SumableDifferentTypeReturnFirstType<T, U> or
					 SamAssignableDifferentType<T, U>;
};


template <typename Container, typename Element = typename Container::value_type>
concept Containerable = requires(Container c, Element e) {
	requires ranges::range<Container>;
	{
		c.size()
	} -> same_as<ranges::range_size_t<Container>>;
	typename Element;
};

template <typename Element>
concept Elementable = requires(Element) {
	requires Multiplicationable<Element>;
	requires Sumable<Element>;
	requires Symmetryable<Element>;
};

template <typename Matrix>
concept IsMatrixable = requires(Matrix m) {
	{
		m.get_row()
	} -> same_as<size_t>;
	{
		m.get_col()
	} -> same_as<size_t>;
	{
		m.get_table()
	};
};

template <typename Coefficientable>
concept Polynomialable = requires(Coefficientable c) {
	requires Elementable<Coefficientable>;
	requires MultiplableDifferentType<Coefficientable, int>;
	requires MultiplableDifferentType<Coefficientable, float>;
	{
		c < 0.0
	} -> same_as<bool>;
};

template <typename Element>
concept Numberable = is_arithmetic_v<Element>;

template <typename Element, typename OtherElement>
concept AnotherElementMultiplable = requires() {
	requires MultiplableDifferentTypeReturnFirstType<Element, OtherElement> or
					 (MultiplableDifferentTypeReturnSecondType<Element, OtherElement> and Polynomialable<OtherElement>);
};

#endif