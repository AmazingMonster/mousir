// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_POOR_INDICATOR_H
#define MOUSIR_APT_POOR_INDICATOR_H

#include "mousir/poor_indicator.hpp"

namespace Mousir {

template<typename TheKey>
struct AptPoorIndicator
{
    template<typename...Args>
    using Mold = PoorIndicator<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<Args...>;
};

}

#endif