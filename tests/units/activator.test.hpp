// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ACTIVATOR_H
#define CONCEPTRODON_TESTS_UNIT_ACTIVATOR_H

#include "mousir/activator.hpp"
#include "mousir/correspondence.hpp"
#include <iostream>
#include <memory>
#include <ostream>


namespace Mousir {
namespace TestActivator {
    

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
    { std::cout << "Caller copy constructed" << std::endl; }
    
    Caller(Caller const && caller)
    { std::cout << "Caller move constructed" << std::endl; }

    bool operator()(Argument p, bool r)
    {    
        std::cout << "Function object called" << std::endl;
        return r;
    }

    bool fun(Argument p, bool r)
    { 
        std::cout << "Pointer to member function called" << std::endl;
        return r; 
    }
};

inline bool fun(Argument p, bool r)
    { 
        std::cout << "Function called" << std::endl;
        return r; 
    }

inline auto Lambda
{
    [](Argument p, bool r)
    { 
        std::cout << "Lambda called" << std::endl;
        return r; 
    }
};

inline void test()
{
    Correspondence<>::Mold<int> correspondence{};
    Activator<>::Mold<int>::Mold<Argument, bool>::Mold<Correspondence<>::Mold<int>> act_0(correspondence);

    Caller caller{};

    act_0.insert(correspondence.increment(), 0, Caller{});
    act_0.insert(correspondence.increment(), 1, caller);
    act_0.insert(correspondence.increment(), 2, fun);
    act_0.insert(correspondence.increment(), 3, Lambda);
    act_0.insert(correspondence.increment(), 4, std::make_shared<Caller>(), &Caller::fun);
    act_0.insert(correspondence.increment(), 5, &caller, &Caller::fun);

    while (true)
    {
        Argument a {};

        char v;
        int k;
        bool r;
        
        std::cout << "0: Rvalue function object" << std::endl;
        std::cout << "1: Lvalue function object" << std::endl;
        std::cout << "2: Function" << std::endl;
        std::cout << "3: Lambda" << std::endl;

        std::cin >> v >> k >> r;
        if (v == 'L' || v == 'l')
        {
            std::cout << "Lvalue argument" << std::endl;
            act_0.execute(k, a, r);
        }
        else if (v == 'R' || v == 'r')
        {
            std::cout << "Rvalue argument" << std::endl;
            act_0.execute(k, Argument{}, r);
        }
    }    
}

}}

#endif