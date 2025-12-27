// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_RICH_ACTIVATOR_H
#define MOUSIR_APT_RICH_ACTIVATOR_H

#include "mousir/rich_activator.hpp"
#include "mousir/apt_rolodex.hpp"

namespace Mousir {

template<typename TheKey>
struct AptRichActivator
{
    template<typename...Args>
    using Mold = RichActivator<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<AptRolodex>
    ::template Mold<Args...>;
};

}

#endif