// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_GENERAL_TESTS_TEST_INITIALIZATION_OF_STANDARD_FUNCTION_H
#define MOUSIR_GENERAL_TESTS_TEST_INITIALIZATION_OF_STANDARD_FUNCTION_H

#include <functional>
#include <iostream>
#include <ostream>


namespace Mousir {
namespace GeneralTests {
namespace TestInitialzationOfStandardFunction {

struct Caller
{
    Caller() = default;

    Caller(Caller const & caller)
    { std::cout << "Function object copy constructed" << std::endl; }
    
    Caller(Caller const && caller)
    { std::cout << "Function object move constructed" << std::endl; }

    void operator()()
    {    
        std::cout << "Function object called" << std::endl;
    }
};

inline void test() {

    {   
        std::cout << "/**** Initialized by PRvalue ****/" << std::endl;
        std::function<void()> fun {Caller{}};
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Initialized by Lvalue ****/" << std::endl;
        Caller caller{};
        std::function<void()> fun {caller};
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Initialized by Xvalue ****/" << std::endl;
        Caller caller{};
        std::function<void()> fun {std::move(caller)};
    }

}

}}}

#endif