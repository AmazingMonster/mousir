// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_ACTIVATOR_H
#define MOUSIR_APT_ACTIVATOR_H

#include "mousir/activator.hpp"
#include "mousir/apt_checkboxer.hpp"

namespace Mousir {

template<typename TheKey>
struct AptActivator
{
    template<typename...Args>
    using Mold = Activator<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<AptCheckBoxer>
    ::template Mold<Args...>;
};

}

#endif