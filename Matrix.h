#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "concept.h"
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

template<typename Element>
concept Elementable = requires(Element){
	requires Multiplicationable<Element>;
	requires Sumable<Element>;
};

template<Elementable Element>
class Matrix {
private:
	typedef vector<Element> RowType;
	typedef vector<RowType> TableType;
public:
	Matrix();

	Matrix(size_t row, size_t col);

	template<template<Containerable> typename Container>
	Matrix(Container<Container<Element>> matrix);

	TableType get_table() const { return table; }

private:

	size_t row;
	size_t col;
	TableType table;
};

#include "Matrix-tmp.h"

#endif
