// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_POOR_FINALIZER_H
#define MOUSIR_APT_POOR_FINALIZER_H

#include "mousir/poor_finalizer.hpp"
#include "mousir/apt_rolodex.hpp"

namespace Mousir {

template<typename TheKey>
struct AptPoorFinalizer
{
    template<typename...Args>
    using Mold = PoorFinalizer<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<AptRolodex>
    ::template Mold<Args...>;
};

}

#endif