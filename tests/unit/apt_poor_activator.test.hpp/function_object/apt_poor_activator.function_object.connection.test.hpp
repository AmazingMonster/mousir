// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_FUNCTION_OBJECT_CONNECTION_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_FUNCTION_OBJECT_CONNECTION_H

#include "mousir/apt_poor_activator.hpp"
#include "mousir/apt_rolodex.hpp"
#include <iostream>
#include <ostream>


namespace Mousir {
namespace UnitTests {
namespace TestAptActivator {
namespace FunctionObject {
namespace Connection {

enum class ValueCategory {PRvalue, Lvalue, Xvalue, LvalueConst, XvalueConst};

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

    void operator()(Argument const &) {}

    void operator()(Argument const &) const {}
};

inline void test()
{
    using Activator = AptPoorActivator<ValueCategory>::Mold<Argument const &>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator(correspondence);
    Caller caller{};
    const Caller const_caller{};

    {   
        ValueCategory key = ValueCategory::PRvalue;
        std::cout << "/**** Connect to PRvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), key, Caller{});
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {
        ValueCategory key = ValueCategory::Lvalue;
        std::cout << "/**** Connect to Lvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), ValueCategory::Lvalue, caller);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }
    
    std::cout << std::endl;

    {
        ValueCategory key = ValueCategory::Xvalue;
        std::cout << "/**** Connect to Xvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), ValueCategory::Xvalue, std::move(caller));
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {
        ValueCategory key = ValueCategory::LvalueConst;
        std::cout << "/**** Connect to Lvalue Const Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), ValueCategory::LvalueConst, const_caller);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }
}

}}}}}

#endif