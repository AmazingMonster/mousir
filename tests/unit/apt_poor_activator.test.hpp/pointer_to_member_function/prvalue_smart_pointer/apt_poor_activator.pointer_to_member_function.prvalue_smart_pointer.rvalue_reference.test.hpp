// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_PRVALUE_SMART_POINTER_RVALUE_REFERENCE_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_PRVALUE_SMART_POINTER_RVALUE_REFERENCE_H

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
namespace PRvalueSmartPointer {
namespace RvalueReference {

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

    virtual void fun(Argument &&)
    {
        std::cout << "Pointer to member function called by rvalue reference" << std::endl;
    }
};

struct CallerDescendant: public Caller
{
    CallerDescendant() = default;

    CallerDescendant(CallerDescendant const & caller)
    { std::cout << "Function object copy constructed" << std::endl; }
    
    CallerDescendant(CallerDescendant && caller)
    { std::cout << "Function object move constructed" << std::endl; }

    void fun(Argument &&) override
    {
        std::cout << "Descendant pointer to member function called by rvalue reference" << std::endl;
    }
};

template<typename C>
struct CustomSmartPointer
{
    CustomSmartPointer(): smart_ptr{std::make_shared<C>()} {}

    CustomSmartPointer(CustomSmartPointer const & caller)
    {
        smart_ptr = caller.smart_ptr;
        std::cout << "Custom smart pointer copy constructed" << std::endl;
    }
    
    CustomSmartPointer(CustomSmartPointer && caller)
    {
        smart_ptr = std::move(caller.smart_ptr);
        std::cout << "Custom smart pointer move constructed" << std::endl;
    }

    auto get() const 
    {return smart_ptr.get();}

    std::shared_ptr<C> smart_ptr;
};

inline void test()
{
    using Activator = AptPoorActivator<PointerSpecifier>::Mold<Argument &&>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator {correspondence};
    PointerSpecifier key {PointerSpecifier::Pointer};
    PointerSpecifier virtual_key {PointerSpecifier::Virtual};

    {    
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Smart Pointer ****/" << std::endl;
        activator.connect(correspondence.increment(), key, CustomSmartPointer<Caller>{}, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {    
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Smart Pointer to Descendant ****/" << std::endl;
        activator.connect(correspondence.increment(), virtual_key, CustomSmartPointer<CallerDescendant>{}, &Caller::fun);
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

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called by Lvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        BLANKET(bool ret = activator.execute(virtual_key, arg));
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
        bool ret = activator.execute(virtual_key, Argument{});
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Descendant called by Xvalue Reference ****/" << std::endl;
        Argument arg {};

        bool & flag {correspondence.find(1) -> second};
        flag = false;

        std::cout << "Execution ---> " << std::boolalpha << flag << std::endl;
        bool ret = activator.execute(virtual_key, std::move(arg));
        std::cout << "Execution <--- " << std::boolalpha << flag << std::endl;
    }
}

}}}}}}

#undef BLANKET
#undef CHECK_VIABILITY

#endif