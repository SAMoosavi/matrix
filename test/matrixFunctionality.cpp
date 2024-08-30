#include "matrix.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class MatrixFunctionality: public Test {
public:
	const size_t DEFAULT_VALUE_OF_MATRIX_CONSTRUCTOR = 0;
};

TEST_F(MatrixFunctionality, default_values_of_table_in_matrix_shuld_be_zero)
{
	constexpr size_t NUMBER_OF_RAW = 4;
	constexpr size_t NUMBER_OF_COL = 4;

	Matrix<int> matrix(NUMBER_OF_RAW, NUMBER_OF_COL);
	const auto& table = matrix.get_table();
	EXPECT_EQ(matrix.get_number_of_row(), NUMBER_OF_RAW);
	for (const auto& row: table) {
		EXPECT_THAT(row, SizeIs(NUMBER_OF_COL));
		EXPECT_THAT(row, Each(DEFAULT_VALUE_OF_MATRIX_CONSTRUCTOR));
	}
}
