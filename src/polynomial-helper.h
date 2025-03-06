#ifndef POLYNOMIAL_HELPER_H
#define POLYNOMIAL_HELPER_H

#include <cstdint>

#include "concept.h"

namespace polynomial_helper
{

template <Numberable Number>
[[nodiscard]] constexpr Number round(Number number, uint8_t precision) noexcept;

template <Integrable Int>
[[nodiscard]] Int create_random_number(Int begin, Int end) noexcept;

}		 // namespace polynomial_helper

#include "polynomial-helper-tmp.h"

#endif