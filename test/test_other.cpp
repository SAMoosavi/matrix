#include "matrix.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Define your test cases here
TEST(TestCaseName, TestName) {
	// Your test code goes here
	ASSERT_EQ(1, 1);
	Matrix<int> a(5,5);

	ASSERT_EQ(a.at(2,3),0);

}

// Add more test cases as needed
