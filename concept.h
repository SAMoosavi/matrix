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
concept MultipleableDifferentTypeReturnFirstType = requires(T t, U u) {
	{
		t* u
	} -> same_as<T>;
};

template <typename T, typename U>
concept MultipleableDifferentTypeReturnSecondType = requires(T t, U u) {
	{
		u* t
	} -> same_as<T>;
};

template <typename T, typename U>
concept MultipleableDifferentType = requires(T, U) {
	requires MultipleableDifferentTypeReturnSecondType<T, U> or
					 MultipleableDifferentTypeReturnFirstType<T, U> or
					 MultipleAssignableDifferentType<T, U>;
};


template <typename T>
concept Sumable = requires(T t) {
	{
		t + t
	} -> same_as<T>;
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
concept SamableDifferentTypeReturnFirstType = requires(T t, U u) {
	{
		t + u
	} -> same_as<T>;
};

template <typename T, typename U>
concept SamableDifferentTypeReturnSecondType = requires(T t, U u) {
	{
		u + t
	} -> same_as<T>;
};

template <typename T, typename U>
concept SamableDifferentType = requires(T, U) {
	requires SamableDifferentTypeReturnSecondType<T, U> or
					 SamableDifferentTypeReturnFirstType<T, U> or
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
};

template <typename Matrix>
concept IsMatrixable = requires(Matrix m) {
	{
		m.get_row()
	} -> std::same_as<size_t>;
	{
		m.get_col()
	} -> std::same_as<size_t>;
	{
		m.get_table()
	};
};

#endif