// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ACTIVATOR_LVALUE_REFERENCE_H
#define CONCEPTRODON_TESTS_UNIT_ACTIVATOR_LVALUE_REFERENCE_H

#include "mousir/activator.hpp"
#include "mousir/checkboxer.hpp"
#include <iostream>
#include <memory>
#include <ostream>


namespace Mousir {
namespace TestActivatorLvalueReference {
    

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

    bool operator()(Argument const & p, bool r)
    {    
        std::cout << "Function object called" << std::endl;
        return r;
    }

    bool fun(Argument const & p, bool r)
    { 
        std::cout << "Pointer to member function called" << std::endl;
        return r; 
    }
};

template<typename C>
struct CallerPtr
{
    CallerPtr(C* the_c): c{the_c} {}
    
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...))
    {
        return [fun, this](Ps...ps) -> R
        {
            return (c->*fun)(ps...);
        };
    }

    C& operator*() { return *c; }

    C* c;
};

inline bool fun(Argument const & p, bool r)
    { 
        std::cout << "Function called" << std::endl;
        return r; 
    }

inline auto Lambda
{
    [](Argument const & p, bool r)
    { 
        std::cout << "Lambda called" << std::endl;
        return r; 
    }
};

inline void test()
{
    using Correspondence = Checkboxer<>::Mold<int>;
    Correspondence correspondence{};
    Activator<>::Mold<int>::Mold<Correspondence>::Mold<Argument const &, bool> act(correspondence);

    Caller caller{};
    Caller* c_ptr {&caller};
    std::shared_ptr<Caller> smart_c_ptr {std::make_shared<Caller>()};
    CallerPtr<Caller> caller_ptr{&caller};

    static_assert(std::invocable<decltype(std::declval<CallerPtr<Caller>>().operator->*(std::declval<decltype(&Caller::fun)>())), Argument, bool>);

    act.connect(correspondence.increment(), 0, Caller{});
    act.connect(correspondence.increment(), 1, caller);
    act.connect(correspondence.increment(), 2, fun);
    act.connect(correspondence.increment(), 3, Lambda);
    act.connect(correspondence.increment(), 4, std::make_shared<Caller>(), &Caller::fun);
    act.connect(correspondence.increment(), 5, smart_c_ptr, &Caller::fun);
    act.connect(correspondence.increment(), 6, &caller, &Caller::fun);
    act.connect(correspondence.increment(), 7, c_ptr, &Caller::fun);
    act.connect(correspondence.increment(), 8, CallerPtr<Caller>{&caller}, &Caller::fun);
    act.connect(correspondence.increment(), 9, caller_ptr, &Caller::fun);

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
        std::cout << "4: Rvalue smart pointer to object and pointer to member function" << std::endl;
        std::cout << "5: Lvalue smart pointer to object and pointer to member function" << std::endl;
        std::cout << "6: Rvalue pointer to object and pointer to member function" << std::endl;
        std::cout << "7: Lvalue pointer to object and pointer to member function" << std::endl;
        std::cout << "8: Rvalue pointer to object like and pointer to member function" << std::endl;
        std::cout << "9: Lvalue pointer to object like and pointer to member function" << std::endl;

        std::cin >> v >> k >> r;
        if (v == 'L' || v == 'l')
        {
            std::cout << "Lvalue argument" << std::endl;
            act.execute(k, a, r);
        }
        else if (v == 'P' || v == 'p')
        {
            std::cout << "Prvalue argument" << std::endl;
            act.execute(k, Argument{}, r);
        }
        else if (v == 'R' || v == 'r')
        {
            std::cout << "Rvalue reference argument" << std::endl;
            act.execute(k, std::move(a), r);
        }
    }    
}

}}

#endif