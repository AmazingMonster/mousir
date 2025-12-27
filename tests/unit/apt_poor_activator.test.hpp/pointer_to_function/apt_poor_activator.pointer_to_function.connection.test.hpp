// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_FUNCTION_CONNECTION_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_FUNCTION_CONNECTION_H

#include "mousir/apt_poor_activator.hpp"
#include "mousir/apt_rolodex.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>


namespace Mousir {
namespace UnitTests {
namespace TestAptActivator {
namespace PointerToFunction {
namespace Connection {

struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    { std::cout << "Argument copy constructed" << std::endl; }
    
    Argument(Argument const && argument)
    { std::cout << "Argument move constructed" << std::endl; }
};

inline void fun(Argument const &) {}

inline void test()
{
    using Activator = AptPoorActivator<std::nullptr_t>::Mold<Argument const &>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator(correspondence);

    {   
        std::nullptr_t key = nullptr;
        std::cout << "/**** Connect to PRvalue Function Object ****/" << std::endl;
        activator.connect(correspondence.increment(), key, fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }
}

}}}}}

#endif