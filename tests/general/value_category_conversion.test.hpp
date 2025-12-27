// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_GENERAL_TESTS_TEST_VALUE_CATEGORY_CONVERSION_H
#define MOUSIR_GENERAL_TESTS_TEST_VALUE_CATEGORY_CONVERSION_H

#include <concepts>
#include <utility>


namespace Mousir {
namespace GeneralTests {
namespace TestValueCategoryConversion {

struct Tester {};

inline void test() {

const Tester const_tester{};
static_assert(std::same_as<decltype(std::move(const_tester)), Tester const &&>);
static_assert(std::same_as<std::decay_t<decltype(std::move(const_tester))>, Tester>);

}

}}}

#endif