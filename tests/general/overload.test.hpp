// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_GENERAL_TESTS_TEST_OVERLOAD_H
#define MOUSIR_GENERAL_TESTS_TEST_OVERLOAD_H

#include <concepts>
#include <utility>
#include <iostream>


namespace Mousir {
namespace GeneralTests {
namespace TestOverload {

struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    { std::cout << "Argument copy constructed" << std::endl; }
    
    Argument(Argument const && argument)
    { std::cout << "Argument move constructed" << std::endl; }
};

struct Caller
{
    Caller() = default;

    Caller(Caller const & caller)
    { std::cout << "Function object copy constructed" << std::endl; }
    
    Caller(Caller const && caller)
    { std::cout << "Function object move constructed" << std::endl; }

    // void operator()(Argument arg)
    // {    
    //     std::cout << "Function object called by regular argument" << std::endl;
    // }

    void operator()(Argument const & arg)
    {    
        std::cout << "Function object called by lvalue reference to const" << std::endl;
    }

    void operator()(Argument & arg)
    {    
        std::cout << "Function object called lvalue reference" << std::endl;
    }

    void operator()(Argument && arg)
    {    
        std::cout << "Function object called Rvalue reference" << std::endl;
    }

    // void operator()(Argument arg) const
    // {    
    //     std::cout << "Const Function object called by regular argument" << std::endl;
    // }

    void operator()(Argument const & arg) const
    {    
        std::cout << "Const function object called by lvalue reference to const" << std::endl;
    }

    void operator()(Argument & arg) const
    {    
        std::cout << "Const function object called lvalue reference" << std::endl;
    }

    void operator()(Argument && arg) const
    {    
        std::cout << "Const function object called Rvalue reference" << std::endl;
    }
};

struct Tester {};

inline void test() {

    Caller caller{};
    Argument argument{};

    caller(Argument{});
    caller(argument);

}

}}}

#endif