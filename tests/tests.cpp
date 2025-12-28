// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#include "tests/general/initialization_of_standard_function.test.hpp"
#include "tests/general/overload.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/function_object/apt_poor_activator.function_object.connection.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/function_object/prvalue/apt_poor_activator.function_object.prvalue.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/function_object/prvalue/apt_poor_activator.function_object.prvalue.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/function_object/prvalue/apt_poor_activator.function_object.prvalue.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/function_object/prvalue/apt_poor_activator.function_object.prvalue.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_function/apt_poor_activator.pointer_to_function.connection.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_function/apt_poor_activator.pointer_to_function.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_function/apt_poor_activator.pointer_to_function.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_function/apt_poor_activator.pointer_to_function.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_function/apt_poor_activator.pointer_to_function.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/apt_poor_activator.pointer_to_member_function.connection.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer/apt_poor_activator.pointer_to_member_function.pointer.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer/apt_poor_activator.pointer_to_member_function.pointer.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer/apt_poor_activator.pointer_to_member_function.pointer.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer/apt_poor_activator.pointer_to_member_function.pointer.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer_to_const/apt_poor_activator.pointer_to_member_function.pointer_to_const.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer_to_const/apt_poor_activator.pointer_to_member_function.pointer_to_const.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer_to_const/apt_poor_activator.pointer_to_member_function.pointer_to_const.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/pointer_to_const/apt_poor_activator.pointer_to_member_function.pointer_to_const.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_smart_pointer/apt_poor_activator.pointer_to_member_function.prvalue_smart_pointer.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_smart_pointer/apt_poor_activator.pointer_to_member_function.prvalue_smart_pointer.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_smart_pointer/apt_poor_activator.pointer_to_member_function.prvalue_smart_pointer.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_smart_pointer/apt_poor_activator.pointer_to_member_function.prvalue_smart_pointer.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/lvalue_smart_pointer_to_const/apt_poor_activator.pointer_to_member_function.lvalue_smart_pointer_to_const.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/lvalue_smart_pointer_to_const/apt_poor_activator.pointer_to_member_function.lvalue_smart_pointer_to_const.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/lvalue_smart_pointer_to_const/apt_poor_activator.pointer_to_member_function.lvalue_smart_pointer_to_const.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/lvalue_smart_pointer_to_const/apt_poor_activator.pointer_to_member_function.lvalue_smart_pointer_to_const.lvalue_reference_to_const.test.hpp"

#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_pointer_like/apt_poor_activator.pointer_to_member_function.prvalue_pointer_like.rvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_pointer_like/apt_poor_activator.pointer_to_member_function.prvalue_pointer_like.regular.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_pointer_like/apt_poor_activator.pointer_to_member_function.prvalue_pointer_like.lvalue_reference.test.hpp"
#include "tests/unit/apt_poor_activator.test.hpp/pointer_to_member_function/prvalue_pointer_like/apt_poor_activator.pointer_to_member_function.prvalue_pointer_like.lvalue_reference_to_const.test.hpp"

int main()
{
    //Mousir::GeneralTests::TestInitialzationOfStandardFunction::test();
    //Mousir::GeneralTests::TestOverload::test();

    //Mousir::UnitTests::TestAptActivator::FunctionObject::Connection::test();

    //Mousir::UnitTests::TestAptActivator::FunctionObject::PRvalue::LvalueReferenceToConst::test();
    //Mousir::UnitTests::TestAptActivator::FunctionObject::PRvalue::LvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::FunctionObject::PRvalue::RvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::FunctionObject::PRvalue::Regular::test();

    //Mousir::UnitTests::TestAptActivator::PointerToFunction::Connection::test();

    //Mousir::UnitTests::TestAptActivator::PointerToFunction::LvalueReferenceToConst::test();
    //Mousir::UnitTests::TestAptActivator::PointerToFunction::LvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::PointerToFunction::RvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::PointerToFunction::Regular::test();

    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::Connection::test();

    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::Pointer::LvalueReferenceToConst::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::Pointer::LvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::Pointer::Regular::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::Pointer::RvalueReference::test();

    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PointerToConst::LvalueReferenceToConst::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PointerToConst::LvalueReference::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PointerToConst::Regular::test();
    //Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PointerToConst::RvalueReference::test();

    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvalueSmartPointer::LvalueReferenceToConst::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvalueSmartPointer::LvalueReference::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvalueSmartPointer::Regular::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvalueSmartPointer::RvalueReference::test();

    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::LvalueSmartPointerToConst::LvalueReferenceToConst::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::LvalueSmartPointerToConst::LvalueReference::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::LvalueSmartPointerToConst::Regular::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::LvalueSmartPointerToConst::RvalueReference::test();

    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvaluePointerLike::LvalueReferenceToConst::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvaluePointerLike::LvalueReference::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvaluePointerLike::Regular::test();
    // Mousir::UnitTests::TestAptActivator::PointerToMemberFunction::PRvaluePointerLike::RvalueReference::test();
    return 0; 
}