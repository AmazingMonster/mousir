// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_GENERAL_TESTS_TEST_FORWARD_H
#define MOUSIR_GENERAL_TESTS_TEST_FORWARD_H

#include <concepts>
#include <utility>


namespace Mousir {
namespace GeneralTests {
namespace TestForward {

struct Tester {};

inline void test() {

const Tester const_tester{};

int a {1};

static_assert(std::same_as<decltype(std::forward<const int&>(a)), const int&>);
static_assert(std::same_as<decltype(std::forward<int>(a)), int&&>);
static_assert(std::same_as<std::decay_t<decltype(std::move(const_tester))>, Tester>);

}

}}}

#endif