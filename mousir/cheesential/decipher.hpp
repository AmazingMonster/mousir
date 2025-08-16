// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHEESENTIAL_DECIPHER_H
#define MOUSIR_CHEESENTIAL_DECIPHER_H

#include <memory>
#include <type_traits>
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/mouldivore/concepts/deceive.hpp"

namespace Mousir {
namespace Cheesential {

template<typename Supposed>
struct Decipher
{
    template<typename...Args>
    Decipher(Args...) {}

    bool is_forward_safe()
    { return true; }
};

template<typename Supposed>
requires Conceptrodon::Mouldivore::Deceive<std::is_lvalue_reference, Supposed>
&&  Conceptrodon::Mouldivore::Deceive<std::is_rvalue_reference, Supposed>
struct Decipher<Supposed>
{
    struct ArgumentConcept
    {
        virtual bool is_forward_safe() = 0;
    virtual ~ArgumentConcept() = default;
    };

    template<typename Provided>
    struct Argument: public ArgumentConcept
    {
        bool is_forward_safe() override
        { return true; }
    };

    template<typename Provided>
    requires Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, Provided>
    struct Argument<Provided>: public ArgumentConcept
    {
        bool is_forward_safe() override
        { return false; }
    };
    
    template<typename Provided>
    Decipher(std::type_identity<Provided>)
    : checker {std::make_unique<Argument<Provided>>(Argument<Provided>{})} {}

    bool is_forward_safe()
    { return checker -> is_forward_safe(); }

    std::unique_ptr<ArgumentConcept> checker;
};

}}

#endif