//
// Created by mahsan on 3/7/24.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <ranges>
#include "Consept.h"

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

    Matrix<Element> sum(const Matrix<Element> &other);

    Matrix<Element> operator+(const Matrix<Element> &other);

    Element at(size_t row_index,size_t col_index);
    RowType operator[](size_t idx) const;

private:

    RowType &operator[](size_t idx);

    size_t row;
    size_t col;
    TableType table;
};



#include "Matrix-tmp.h"

#endif
