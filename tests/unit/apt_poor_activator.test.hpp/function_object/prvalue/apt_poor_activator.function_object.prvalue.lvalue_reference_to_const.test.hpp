// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_FUNCTION_OBJECT_PRVALUE_LVALUE_REFERENCE_TO_CONST_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_FUNCTION_OBJECT_PRVALUE_LVALUE_REFERENCE_TO_CONST_H

#include "mousir/apt_poor_activator.hpp"
#include "mousir/apt_rolodex.hpp"
#include <ios>
#include <iostream>
#include <ostream>


namespace Mousir {
namespace UnitTests {
namespace TestAptActivator {
namespace FunctionObject {
namespace PRvalue {
namespace LvalueReferenceToConst {

enum class ValueCategory {PRvalue, Lvalue, Xvalue, LvalueConst, XvalueConst};

struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    { std::cout << "Argument copy constructed" << std::endl; }
    
    Argument(Argument && argument)
    { std::cout << "Argument move constructed" << std::endl; }
};

struct Caller
{
    Caller() = default;

    Caller(Caller const & caller)
    { std::cout << "Function object copy constructed" << std::endl; }
    
    Caller(Caller && caller)
    { std::cout << "Function object move constructed" << std::endl; }

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
        std::cout << "Function object called rvalue reference" << std::endl;
    }

    void operator()(Argument const & arg) const
    {    
        std::cout << "Const function object called by lvalue reference to const" << std::endl;
    }

    void operator()(Argument & arg) const
    {    
        std::cout << "Const function object called by lvalue reference" << std::endl;
    }

    void operator()(Argument && arg) const
    {    
        std::cout << "Const function object called by rvalue reference" << std::endl;
    }
};

inline void test()
{
    using Activator = AptPoorActivator<ValueCategory>::Mold<Argument const &>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator{correspondence};
    Caller caller{};
    const Caller const_caller{};
    ValueCategory key {ValueCategory::PRvalue};

    {    
        std::cout << "/**** Connect to PRvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), key, Caller{});
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Lvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(key, arg);
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Lvalue Reference to const ****/" << std::endl;
        const Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(key, arg);
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

}}}}}}

#endif