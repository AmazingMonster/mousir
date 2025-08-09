// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_BURSTER_H
#define MOUSIR_APT_BURSTER_H

#include "mousir/burster.hpp"

namespace Mousir {

template<typename TheKey>
struct AptBurster
{
    template<typename...Args>
    using Mold = Burster<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<Args...>;
};

}

#endif