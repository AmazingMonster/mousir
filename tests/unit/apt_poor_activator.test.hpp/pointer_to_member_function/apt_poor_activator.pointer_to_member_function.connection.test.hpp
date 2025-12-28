// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_CONNECTION_H
#define MOUSIR_UNIT_TESTS_TEST_APT_POOR_ACTIVATOR_POINTER_TO_MEMBER_FUNCTION_CONNECTION_H

#include "mousir/apt_poor_activator.hpp"
#include "mousir/apt_rolodex.hpp"
#include <iostream>
#include <ostream>
#include <memory>


namespace Mousir {
namespace UnitTests {
namespace TestAptActivator {
namespace PointerToMemberFunction {
namespace Connection {

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

    void fun(Argument const &) const {}
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
            return (c->*fun)(ps...);
        };
    }
    
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...) const) const
    {
        return [fun, this](Ps...ps) -> R
        {
            std::cout << "Calling pointer to const member function from pointer like object" << std::endl;
            return (c->*fun)(ps...);
        };
    }

    C& operator*() { return *c; }

    C* c;
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
    using Activator = AptPoorActivator<PointerSpecifier>::Mold<Argument const &>;
    using Rolodex = AptRolodex;

    Rolodex correspondence{};
    Activator activator{correspondence};

    {   
        Caller caller{};
        PointerSpecifier key {PointerSpecifier::Pointer};
        std::cout << "/**** Connect to Pointer to Member Function with Pointer ****/" << std::endl;
        activator.connect(correspondence.increment(), key, &caller, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        const Caller const_caller{};
        PointerSpecifier key {PointerSpecifier::Pointer};
        std::cout << "/**** Connect to Pointer to Member Function with Pointer to Const ****/" << std::endl;
        activator.connect(correspondence.increment(), key, &const_caller, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        PointerSpecifier key {PointerSpecifier::PRvalueSmartPointer};
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Smart Pointer ****/" << std::endl;
        activator.connect(correspondence.increment(), key, CustomSmartPointer<Caller>{}, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        CustomSmartPointer<Caller> smart_ptr{};
        PointerSpecifier key {PointerSpecifier::LvalueSmartPointer};
        std::cout << "/**** Connect to Pointer to Member Function with Lvalue Smart Pointer ****/" << std::endl;
        activator.connect(correspondence.increment(), key, smart_ptr, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        CustomSmartPointer<Caller> smart_ptr{};
        PointerSpecifier key {PointerSpecifier::XvalueSmartPointer};
        std::cout << "/**** Connect to Pointer to Member Function with Xvalue Smart Pointer ****/" << std::endl;
        activator.connect(correspondence.increment(), key, std::move(smart_ptr), &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        PointerSpecifier key {PointerSpecifier::PRvalueSmartPointerToConst};
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Smart Pointer to Const ****/" << std::endl;
        activator.connect(correspondence.increment(), key, CustomSmartPointer<const Caller>{}, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        CustomSmartPointer<const Caller> smart_ptr{};
        PointerSpecifier key {PointerSpecifier::LvalueSmartPointerToConst};
        std::cout << "/**** Connect to Pointer to Member Function with Lvalue Smart Pointer to Const ****/" << std::endl;
        activator.connect(correspondence.increment(), key, smart_ptr, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        CustomSmartPointer<const Caller> smart_ptr{};
        PointerSpecifier key {PointerSpecifier::XvalueSmartPointerToConst};
        std::cout << "/**** Connect to Pointer to Member Function with Xvalue Smart Pointer to Const ****/" << std::endl;
        activator.connect(correspondence.increment(), key, std::move(smart_ptr), &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        Caller caller{};
        PointerSpecifier key {PointerSpecifier::PRvaluePointerLike};
        std::cout << "/**** Connect to Pointer to Member Function with PRvalue Pointer Like ****/" << std::endl;
        activator.connect(correspondence.increment(), key, CustomPointer<Caller>{&caller}, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        Caller caller{};
        CustomPointer<Caller> custom_ptr{&caller};
        PointerSpecifier key {PointerSpecifier::LvaluePointerLike};
        std::cout << "/**** Connect to Pointer to Member Function with Lvalue Pointer Like ****/" << std::endl;
        activator.connect(correspondence.increment(), key, custom_ptr, &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }

    std::cout << std::endl;

    {   
        Caller caller{};
        CustomPointer<Caller> custom_ptr{&caller};
        PointerSpecifier key {PointerSpecifier::XvaluePointerLike};
        std::cout << "/**** Connect to Pointer to Member Function with Xvalue Pointer Like ****/" << std::endl;
        activator.connect(correspondence.increment(), key, std::move(custom_ptr), &Caller::fun);
        std::cout << "Current counter: " << correspondence.get_counter() << std::endl; 
    }
}

}}}}}

#endif