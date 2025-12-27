// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_RICH_INDICATOR_H
#define MOUSIR_APT_RICH_INDICATOR_H

#include "mousir/rich_indicator.hpp"

namespace Mousir {

template<typename TheKey>
struct AptRichIndicator
{
    template<typename...Args>
    using Mold = RichIndicator<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<Args...>;
};

}

#endif