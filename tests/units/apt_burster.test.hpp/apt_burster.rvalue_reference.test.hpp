// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_TESTS_UNIT_APT_BURSTER_RVALUE_REFERENCE_H
#define MOUSIR_TESTS_UNIT_APT_BURSTER_RVALUE_REFERENCE_H

#include "mousir/apt_burster.hpp"
#include <iostream>
#include <memory>
#include <ostream>


namespace Mousir {
namespace TestAptBursterRvalueReference {
    

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
    AptBurster<int>::Mold<Argument &&, bool> bur{};

    Caller caller{};
    Caller* c_ptr {&caller};
    std::shared_ptr<Caller> smart_c_ptr {std::make_shared<Caller>()};
    CallerPtr<Caller> caller_ptr{&caller};

    std::cout << "/**** Connect ****/" << std::endl;
    std::cout << "0: Rvalue function object" << std::endl;
    bur.connect(0, Caller{});
    std::cout << "1: Lvalue function object" << std::endl;
    bur.connect(1, caller);
    std::cout << "2: Function" << std::endl;
    bur.connect(2, fun);
    std::cout << "3: Lambda" << std::endl;
    bur.connect(3, Lambda);
    std::cout << "4: Rvalue smart pointer to object and pointer to member function" << std::endl;
    bur.connect(4, std::make_shared<Caller>(), &Caller::fun);
    std::cout << "5: Lvalue smart pointer to object and pointer to member function" << std::endl;
    bur.connect(5, smart_c_ptr, &Caller::fun);
    std::cout << "6: Rvalue pointer to object and pointer to member function" << std::endl;
    bur.connect(6, &caller, &Caller::fun);
    std::cout << "7: Lvalue pointer to object and pointer to member function" << std::endl;
    bur.connect(7, c_ptr, &Caller::fun);
    std::cout << "8: Rvalue pointer to object like and pointer to member function" << std::endl;
    bur.connect(8, CallerPtr<Caller>{&caller}, &Caller::fun);
    std::cout << "9: Lvalue pointer to object like and pointer to member function" << std::endl;
    bur.connect(9, caller_ptr, &Caller::fun);
    std::cout << "/********/" << std::endl;

    auto print_instruction 
    {
        []() -> void
        {
            std::cout << "/**** Instruction ****/" << std::endl;
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
            std::cout << "/********/" << std::endl;
        }
    };

    while (true)
    {
        Argument a {};

        char v;
        bool r;
        int k;
        
        print_instruction();
        
        std::cin >> v >> r >> k;
        if (v == 'L' || v == 'l')
        {
            std::cout << "/**** Lvalue argument fail ****/" << std::endl;
            // bur.execute(k, a, r);
            std::cout << "/********/" << std::endl;
        }
        else if (v == 'P' || v == 'p')
        {
            std::cout << "/**** Prvalue argument ****/" << std::endl;
            bur.execute(k, Argument{}, r);
            std::cout << "/********/" << std::endl;
        }
        else if (v == 'R' || v == 'r')
        {
            std::cout << "/**** Rvalue reference argument ****/" << std::endl;
            bur.execute(k, std::move(a), r);
            std::cout << "/********/" << std::endl;
        }
    }    
}

}}

#endif