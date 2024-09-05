#include "matrix.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class MatrixFunctionality: public Test {};

TEST_F(MatrixFunctionality, creat_matrix_with_size_should_creat_matrix_with_size_and_set_value_of_each_cell_zero)
{
	constexpr size_t NUMBER_OF_RAW = 4;
	constexpr size_t NUMBER_OF_COL = 5;
	const int DEFAULT_VALUE_OF_MATRIX_CONSTRUCTOR = 0;

	Matrix<int> matrix(NUMBER_OF_RAW, NUMBER_OF_COL);
	std::vector<std::vector<int>> TABLE_OF_MATRIX(NUMBER_OF_RAW, std::vector<int>(NUMBER_OF_COL,
		DEFAULT_VALUE_OF_MATRIX_CONSTRUCTOR));
	EXPECT_EQ(matrix.get_table(), TABLE_OF_MATRIX);
}

TEST_F(MatrixFunctionality, creat_matrix_with_vector)
{
	const std::vector<std::vector<double>> INITIALIZE_DATA_OF_MATRIX = {
			{1.2, 2.3, 3, 4},
			{1, 2, 3.5, 4},
			{5, 6, 7, 8.9}
	};

	Matrix<double> matrix(INITIALIZE_DATA_OF_MATRIX);
	EXPECT_EQ(matrix.get_table(), INITIALIZE_DATA_OF_MATRIX);
}

TEST_F(MatrixFunctionality, creat_matrix_with_intializer_list)
{
	const std::initializer_list<std::initializer_list<uint32_t>> INITIALIZE_LIST_OF_MATRIX = {
			{1, 2, 3, 4},
			{1, 2, 3, 4},
			{5, 6, 7, 8}
	};

	std::vector<std::vector<uint32_t>> table_of_matrix;
	for (const auto& row_of_matrix: INITIALIZE_LIST_OF_MATRIX)
		table_of_matrix.emplace_back(row_of_matrix);

	Matrix<uint32_t> matrix(INITIALIZE_LIST_OF_MATRIX);
	EXPECT_THAT(matrix.get_table(), Eq(table_of_matrix));
}

TEST_F(MatrixFunctionality, creat_matrix_with_different_column_size_should_be_get_trow)
{
	EXPECT_THROW(Matrix<int>({{1, 2, 3}, {1, 4}, {5, 6, 7, 8}}), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_sum_function_suold_be_trow_when_first_and_second_matrix_is_not_same_column_number)
{
	constexpr size_t ROW_NUMBER = 1;
	constexpr size_t FIRST_COL_NUMBER = 1;
	constexpr size_t SECOND_COL_NUMBER = 2;
	const Matrix<int> FIRST_MATRIX(ROW_NUMBER, FIRST_COL_NUMBER);
	const Matrix<int> SECOND_MATRIX(ROW_NUMBER, SECOND_COL_NUMBER);
	EXPECT_THROW(FIRST_MATRIX.sum(SECOND_MATRIX), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_sum_function_suold_be_trow_when_first_and_second_matrix_is_not_same_row_number)
{
	constexpr size_t FIRST_ROW_NUMBER = 1;
	constexpr size_t SECOND_ROW_NUMBER = 2;
	constexpr size_t COL_NUMBER = 1;
	const Matrix<int> FIRST_MATRIX(FIRST_ROW_NUMBER, COL_NUMBER);
	const Matrix<int> SECOND_MATRIX(SECOND_ROW_NUMBER, COL_NUMBER);
	EXPECT_THROW(FIRST_MATRIX.sum(SECOND_MATRIX), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_submission_function_suold_be_trow_when_first_and_second_matrix_is_not_same_column_number)
{
	constexpr size_t ROW_NUMBER = 1;
	constexpr size_t FIRST_COL_NUMBER = 1;
	constexpr size_t SECOND_COL_NUMBER = 2;
	const Matrix<int> FIRST_MATRIX(ROW_NUMBER, FIRST_COL_NUMBER);
	const Matrix<int> SECOND_MATRIX(ROW_NUMBER, SECOND_COL_NUMBER);
	EXPECT_THROW(FIRST_MATRIX.submission(SECOND_MATRIX), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_submission_function_suold_be_trow_when_first_and_second_matrix_is_not_same_row_number)
{
	constexpr size_t FIRST_ROW_NUMBER = 1;
	constexpr size_t SECOND_ROW_NUMBER = 2;
	constexpr size_t COL_NUMBER = 1;
	const Matrix<int> FIRST_MATRIX(FIRST_ROW_NUMBER, COL_NUMBER);
	const Matrix<int> SECOND_MATRIX(SECOND_ROW_NUMBER, COL_NUMBER);
	EXPECT_THROW(FIRST_MATRIX.submission(SECOND_MATRIX), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_multiple_function_suold_be_trow_when_col_number_of_first_and_row_number_of_second_matrix_is_not_same)
{
	constexpr size_t FIRST_ROW_NUMBER = 1;
	constexpr size_t FIRST_COL_NUMBER = 1;
	constexpr size_t SECOND_ROW_NUMBER = 2;
	constexpr size_t SECOND_COL_NUMBER = 1;
	const Matrix<int> FIRST_MATRIX(FIRST_ROW_NUMBER, FIRST_COL_NUMBER);
	const Matrix<int> SECOND_MATRIX(SECOND_ROW_NUMBER, SECOND_COL_NUMBER);
	EXPECT_THROW(FIRST_MATRIX.multiple(SECOND_MATRIX), std::invalid_argument);
}

TEST_F(MatrixFunctionality, the_determinant_function_suold_be_trow_when_the_matrix_is_not_squrt)
{
	constexpr size_t ROW_NUMBER = 1;
	constexpr size_t COL_NUMBER = 2;
	const Matrix<int> MATRIX(ROW_NUMBER, COL_NUMBER);
	EXPECT_THROW(MATRIX.determinant(), std::invalid_argument);
}

using BaineryOperatorType = std::tuple<Matrix<int>, Matrix<int>, Matrix<int>>;

class SumOfTwoMatrix: public ::testing::TestWithParam<BaineryOperatorType> {};

TEST_P(SumOfTwoMatrix, the_sum_function_should_return_third_param_when_sum_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX.sum(SECOND_MATRIX), THIRD_MATRIX);
}

TEST_P(SumOfTwoMatrix, the_sum_operator_should_return_third_param_when_sum_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX + SECOND_MATRIX, THIRD_MATRIX);
}

TEST_P(SumOfTwoMatrix, the_sum_equal_operator_should_set_first_matrix_equal_to_third_param_when_sum_first_and_second_params)
{
	Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());
	FIRST_MATRIX += SECOND_MATRIX;
	EXPECT_EQ(FIRST_MATRIX, THIRD_MATRIX);
}

INSTANTIATE_TEST_SUITE_P(
		SumData,
		SumOfTwoMatrix,
		Values(
				std::make_tuple(
						Matrix<int>({{1, 2, 3}, {1, 2, 3}}),
						Matrix<int>({{6, 5, 4}, {6, 5, 4}}),
						Matrix<int>({{7, 7, 7}, {7, 7, 7}})
				),
				std::make_tuple(
						Matrix<int>({{1, 2, 3, 4, 5, 6, 7}}),
						Matrix<int>({{7, 6, 5, 4, 3, 2, 1}}),
						Matrix<int>({{8, 8, 8, 8, 8, 8, 8}})
				)
		)
);

class SubmissionOfTwoMatrix: public ::testing::TestWithParam<BaineryOperatorType> {};

TEST_P(SubmissionOfTwoMatrix, the_submission_function_should_return_third_param_when_submission_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX.submission(SECOND_MATRIX), THIRD_MATRIX);
}

TEST_P(SubmissionOfTwoMatrix, the_submission_operator_should_return_third_param_when_submission_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX - SECOND_MATRIX, THIRD_MATRIX);
}

TEST_P(SubmissionOfTwoMatrix, the_submission_equal_operator_should_set_first_matrix_equal_to_third_param_when_submission_first_and_second_params)
{
	Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());
	FIRST_MATRIX -= SECOND_MATRIX;
	EXPECT_EQ(FIRST_MATRIX, THIRD_MATRIX);
}

INSTANTIATE_TEST_SUITE_P(
		SubmissionData,
		SubmissionOfTwoMatrix,
		Values(
				std::make_tuple(
						Matrix<int>({{1, 2, 3}, {1, 2, 3}}),
						Matrix<int>({{6, 5, 4}, {6, 5, 4}}),
						Matrix<int>({{-5, -3, -1}, {-5, -3, -1}})
				),
				std::make_tuple(
						Matrix<int>({{1, 2, 3, 4, 5, 6, 7}}),
						Matrix<int>({{7, 6, 5, 4, 3, 2, 1}}),
						Matrix<int>({{-6, -4, -2, 0, 2, 4, 6}})
				)
		)
);

class MultipleOfTwoMatrix: public ::testing::TestWithParam<BaineryOperatorType> {};

TEST_P(MultipleOfTwoMatrix, the_multiple_function_should_return_third_param_when_multiple_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX.multiple(SECOND_MATRIX), THIRD_MATRIX);
}

TEST_P(MultipleOfTwoMatrix, the_multiple_operator_should_return_third_param_when_multiple_first_and_second_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());

	EXPECT_EQ(FIRST_MATRIX * SECOND_MATRIX, THIRD_MATRIX);
}

TEST_P(MultipleOfTwoMatrix, the_multiple_equal_operator_should_set_first_matrix_equal_to_third_param_when_multiple_first_and_second_params)
{
	Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	const Matrix<int> THIRD_MATRIX = std::get<2>(GetParam());
	FIRST_MATRIX *= SECOND_MATRIX;
	EXPECT_EQ(FIRST_MATRIX, THIRD_MATRIX);
}

INSTANTIATE_TEST_SUITE_P(
		MultipleData,
		MultipleOfTwoMatrix,
		Values(
				std::make_tuple(
						Matrix<int>({{1, 2}, {1, 2}}),
						Matrix<int>({{1, 2}, {1, 2}}),
						Matrix<int>({{3, 6}, {3, 6}})
				),
				std::make_tuple(
						Matrix<int>({{1, 2, 3, 4, 5, 6, 7}}),
						Matrix<int>({{7}, {6}, {5}, {4}, {3}, {2}, {1}}),
						Matrix<int>({{84, 0, 0, 0, 0, 0, 0}})
				),
				std::make_tuple(
						Matrix<int>({
								{1, 2, 3, 4, 5, 6, 7},
								{1, 2, 3, 4, 5, 6, 7},
								{1, 2, 3, 4, 5, 6, 7},
								{1, 2, 3, 4, 5, 6, 7},
								{1, 2, 3, 4, 5, 6, 7}
						}),
						Matrix<int>({
								{7, 2, 3, 4, 5, 6, 9, 7},
								{6, 2, 3, 4, 5, 6, 9, 7},
								{5, 2, 3, 4, 5, 6, 9, 7},
								{4, 2, 3, 4, 5, 6, 9, 7},
								{3, 2, 3, 4, 5, 6, 9, 7},
								{2, 2, 3, 4, 5, 6, 9, 7},
								{1, 2, 3, 4, 5, 6, 9, 7}
						}),
						Matrix<int>({
								{84, 56, 84, 112, 140, 168, 252},
								{84, 56, 84, 112, 140, 168, 252},
								{84, 56, 84, 112, 140, 168, 252},
								{84, 56, 84, 112, 140, 168, 252},
								{84, 56, 84, 112, 140, 168, 252}
						})
				)
		)
);

class OppositeOfMatrix: public ::testing::TestWithParam<std::tuple<Matrix<int>, Matrix<int>>> {};

TEST_P(OppositeOfMatrix, the_opposite_operator_should_return_second_param_when_opposit_first_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const Matrix<int> SECOND_MATRIX = std::get<1>(GetParam());
	EXPECT_EQ(-FIRST_MATRIX, SECOND_MATRIX);
}

INSTANTIATE_TEST_SUITE_P(
		OppositeData,
		OppositeOfMatrix,
		Values(
				std::make_tuple(
						Matrix<int>({{1, 2, 3}, {1, 2, 3}}),
						Matrix<int>({{-1, -2, -3}, {-1, -2, -3}})
				),
				std::make_tuple(
						Matrix<int>({{1, 2, 3, 4, 5, 6, 7}}),
						Matrix<int>({{-1, -2, -3, -4, -5, -6, -7}})
				)
		)
);

class DeterminantOfMatrix: public ::testing::TestWithParam<std::tuple<Matrix<int>, int>> {};

TEST_P(DeterminantOfMatrix, the_determinant_should_return_second_param_when_determinant_first_params)
{
	const Matrix<int> FIRST_MATRIX = std::get<0>(GetParam());
	const int DETERMINANT = std::get<1>(GetParam());
	EXPECT_EQ(FIRST_MATRIX.determinant(), DETERMINANT);
}

INSTANTIATE_TEST_SUITE_P(
		DeterminantData,
		DeterminantOfMatrix,
		Values(
				std::make_tuple(Matrix<int>({{1, 2}, {0, 2}}), 2),
				std::make_tuple(Matrix<int>({{1, 2, 3}, {0, 2, 3}, {1, 2, 0}}), -6),
				std::make_tuple(Matrix<int>({{1, 2, 3, 4}, {0, 2, 3, 5}, {1, 2, 0, 5}, {1, 2, 8, 5}}), -12),
				std::make_tuple(Matrix<int>({{1}}), 1)
		)
);