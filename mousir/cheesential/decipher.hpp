// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHEESENTIAL_DECIPHER_H
#define MOUSIR_CHEESENTIAL_DECIPHER_H

#include <type_traits>
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/mouldivore/concepts/deceive.hpp"
#include <utility>

namespace Mousir {
namespace Cheesential {

template<typename Given>
struct Decipher
{
    template<typename Passed>
    Decipher(std::remove_reference_t<Passed>& the_reference): reference{the_reference} {}

        auto forward() { return std::forward<Given>(reference); }

    
    template<typename Passed>
    requires Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, Passed>
    &&  Conceptrodon::Mouldivore::Deceive<std::is_lvalue_reference, Given>
    &&  Conceptrodon::Mouldivore::Deceive<std::is_rvalue_reference, Given>
    Decipher(Passed&& the_reference) {}

        void* forward;
    };

}}

#endif