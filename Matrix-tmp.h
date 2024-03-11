#ifndef MATRIX_MATRIX_TMP_H
#define MATRIX_MATRIX_TMP_H

template <Elementable Element>
Matrix<Element>::Matrix()
	: row(0), col(0), table({{}}){};

template <Elementable Element>
Matrix<Element>::Matrix(size_t row, size_t col)
	: row(row), col(col), table(row, RowType(col, 0)){};

template <Elementable Element>
template <template <Containerable> typename Container>
Matrix<Element>::Matrix(Container<Container<Element>> matrix)
	: row(matrix.size()), col(matrix[0].size()), table(row, RowType(col, 0))
{
	for (int row_index = 0; row_index < row; ++row_index) {
		for (int col_index = 0; col_index < col; ++col_index) {
			table[row_index][col_index] = matrix[row_index][col_index];
		}
	}
};

template <Elementable Element>
Matrix<Element> Matrix<Element>::sum(const Matrix<Element>& other)
{
	if (row != other.row && col != other.col)
		throw invalid_argument("Cannot sum spans of different sizes");
	Matrix<Element> result(row, col);
	for (size_t row_index = 0; row_index < row; ++row_index)
		for (size_t col_index = 0; col_index < col; ++col_index)
			result[row_index][col_index] = other[row_index][col_index] + table[row_index][col_index];

	return result;
}

template <Elementable Element>
Matrix<Element> Matrix<Element>::operator+(const Matrix<Element>& other)
{
	return sum(other);
}

template <Elementable Element>
Matrix<Element>::RowType Matrix<Element>::operator[](size_t idx) const
{
	return table[idx];
}

template <Elementable Element>
Matrix<Element>::RowType& Matrix<Element>::operator[](size_t idx)
{
	return table[idx];
}

template <Elementable Element>
Element Matrix<Element>::at(size_t row_index, size_t col_index)
{
	return table[row_index][col_index];
}

#endif