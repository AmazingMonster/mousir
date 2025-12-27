// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_FUNCTION_RVALUE_REFERENCE_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_FUNCTION_RVALUE_REFERENCE_H

#include "mousir/apt_poor_activator.hpp"
#include "mousir/apt_rolodex.hpp"
#include <ios>
#include <iostream>
#include <ostream>

#define CHECK_VIABILITY 0
#if CHECK_VIABILITY
#define BLANKET(...) __VA_ARGS__
#else
#define BLANKET(...)
#endif

namespace Mousir {
namespace UnitTests {
namespace TestAptActivator {
namespace PointerToFunction {
namespace RvalueReference {

enum class ValueCategory {PRvalue, Lvalue, Xvalue, LvalueConst, XvalueConst};

struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    { std::cout << "Argument copy constructed" << std::endl; }
    
    Argument(Argument const && argument)
    { std::cout << "Argument move constructed" << std::endl; }
};

inline void fun(Argument&&)
{
    std::cout << "Function pointer called by rvalue reference" << std::endl;
}

inline void test()
{
    using Activator = AptPoorActivator<std::nullptr_t>::Mold<Argument&&>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator(correspondence);
    std::nullptr_t key = nullptr;

    {    
        std::cout << "/**** Connect to PRvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), key, fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Lvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(key, arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Lvalue Reference to const ****/" << std::endl;
        const Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(key, arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by PRvalue Reference ****/" << std::endl;

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(key, Argument{});
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Xvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(key, std::move(arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }
}

}}}}}

#undef BLANKET
#undef CHECK_VIABILITY

#endif