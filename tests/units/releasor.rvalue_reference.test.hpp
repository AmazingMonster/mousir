// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RELEASOR_RVALUE_REFERENCE_H
#define CONCEPTRODON_TESTS_UNIT_RELEASOR_RVALUE_REFERENCE_H

#include "mousir/releasor.hpp"
#include "mousir/checkboxer.hpp"
#include <iostream>
#include <memory>
#include <ostream>


namespace Mousir {
namespace TestReleasorRvalueReference {
    

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

    bool operator()(Argument && p, bool r)
    {    
        std::cout << "Function object called" << std::endl;
        return r;
    }

    bool fun(Argument && p, bool r)
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
            return (c->*fun)(std::move(ps)...);
        };
    }

    C& operator*() { return *c; }

    C* c;
};

inline bool fun(Argument && p, bool r)
    { 
        std::cout << "Function called" << std::endl;
        return r; 
    }

inline auto Lambda
{
    [](Argument && p, bool r)
    { 
        std::cout << "Lambda called" << std::endl;
        return r; 
    }
};

inline void test()
{
    using Correspondence = Checkboxer<>::Mold<int>;
    Correspondence correspondence{};
    Releasor<>::Mold<int>::Mold<Correspondence>::Mold<Argument&&, bool> rel(correspondence);

    Caller caller{};
    Caller* c_ptr {&caller};
    std::shared_ptr<Caller> smart_c_ptr {std::make_shared<Caller>()};
    CallerPtr<Caller> caller_ptr{&caller};

    static_assert(std::invocable<decltype(std::declval<CallerPtr<Caller>>().operator->*(std::declval<decltype(&Caller::fun)>())), Argument, bool>);

    rel.connect(correspondence.increment(true), 0, Caller{});
    rel.connect(correspondence.increment(true), 1, caller);
    rel.connect(correspondence.increment(true), 2, fun);
    rel.connect(correspondence.increment(true), 3, Lambda);
    rel.connect(correspondence.increment(true), 4, std::make_shared<Caller>(), &Caller::fun);
    rel.connect(correspondence.increment(true), 5, smart_c_ptr, &Caller::fun);
    rel.connect(correspondence.increment(true), 6, &caller, &Caller::fun);
    rel.connect(correspondence.increment(true), 7, c_ptr, &Caller::fun);
    rel.connect(correspondence.increment(true), 8, CallerPtr<Caller>{&caller}, &Caller::fun);
    rel.connect(correspondence.increment(true), 9, caller_ptr, &Caller::fun);

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
            std::cout << "Lvalue argument fail" << std::endl;
            //rel.execute(k, a, r);
        }
        else if (v == 'P' || v == 'p')
        {
            std::cout << "PRvalue argument" << std::endl;
            rel.execute(k, Argument{}, r);
        }
        else if (v == 'R' || v == 'r')
        {
            std::cout << "Rvalue reference argument" << std::endl;
            rel.execute(k, std::move(a), r);
        }
    }    
}

}}

#endif