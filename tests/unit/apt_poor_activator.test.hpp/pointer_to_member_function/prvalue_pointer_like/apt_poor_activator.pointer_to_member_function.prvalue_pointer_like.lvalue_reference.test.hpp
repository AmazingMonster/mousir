// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_PRVALUE_POINTER_LIKE_LVALUE_REFERENCE_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_PRVALUE_POINTER_LIKE_LVALUE_REFERENCE_H

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
namespace PointerToMemberFunction {
namespace PRvaluePointerLike {
namespace LvalueReference {

enum PointerSpecifier
{
    Pointer
    , PointerToConst
    , PRvalueSmartPointer
    , LvalueSmartPointer
    , XvalueSmartPointer
    , PRvalueSmartPointerToConst
    , LvalueSmartPointerToConst
    , XvalueSmartPointerToConst
    , PRvaluePointerLike
    , LvaluePointerLike
    , XvaluePointerLike
    , Virtual
};

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

    virtual void fun(Argument &)
    {
        std::cout << "Pointer to member function called by lvalue reference" << std::endl;
    }
};

struct CallerDescendant: public Caller
{
    CallerDescendant() = default;

    CallerDescendant(CallerDescendant const & caller)
    { std::cout << "Function object copy constructed" << std::endl; }
    
    CallerDescendant(CallerDescendant && caller)
    { std::cout << "Function object move constructed" << std::endl; }

    void fun(Argument &) override
    {
        std::cout << "Descendant pointer to member function called by lvalue reference" << std::endl;
    }
};

template<typename C>
struct CustomPointer
{
    CustomPointer(C* the_c): c{the_c} {}

    CustomPointer(CustomPointer const & caller)
    {
        c = caller.c;
        std::cout << "Custom pointer copy constructed" << std::endl;
    }
    
    CustomPointer(CustomPointer && caller)
    {
        c = caller.c;
        std::cout << "Custom pointer move constructed" << std::endl;
    }
    
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...)) const
    {
        return [fun, this](Ps...ps) -> R
        {
            std::cout << "Calling pointer to member function from pointer like object" << std::endl;
            return (c->*fun)(std::forward<Ps>(ps)...);
        };
    }
    
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...) const) const
    {
        return [fun, this](Ps...ps) -> R
        {
            std::cout << "Calling pointer to const member function from pointer like object" << std::endl;
            return (c->*fun)(std::forward<Ps>(ps)...);
        };
    }

    C& operator*() { return *c; }

    C* c;
};

inline void test()
{
    using Activator = AptPoorActivator<PointerSpecifier>::Mold<Argument &>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator {correspondence};
    PointerSpecifier key {PointerSpecifier::Pointer};
    PointerSpecifier virtual_key {PointerSpecifier::Virtual};
    Caller caller{};
    CallerDescendant caller_descendant{};

    {    
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Pointer Like ****/" << std::endl;
        activator.connect(correspondence.increment(), key, CustomPointer<Caller>{&caller}, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {    
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Pointer Like to Descendant ****/" << std::endl;
        activator.connect(correspondence.increment(), virtual_key, CustomPointer<Caller>{&caller_descendant}, &Caller::fun);
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
        BLANKET(bool ret = activator.execute(key, arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by PRvalue Reference ****/" << std::endl;

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(key, Argument{}));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Called by Xvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(0) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(key, std::move(arg)));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called by Lvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(virtual_key, arg);
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called by Lvalue Reference to const ****/" << std::endl;
        const Argument arg {};

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(virtual_key, arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called  by PRvalue Reference ****/" << std::endl;

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(virtual_key, Argument{}));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called by Xvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(virtual_key, std::move(arg)));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }
}

}}}}}}

#undef BLANKET
#undef CHECK_VIABILITY

#endif