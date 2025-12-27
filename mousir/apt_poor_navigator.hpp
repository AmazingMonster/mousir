// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_POOR_NAVIGATOR_H
#define MOUSIR_APT_POOR_NAVIGATOR_H

#include "mousir/poor_navigator.hpp"
#include "mousir/apt_rolodex.hpp"

namespace Mousir {

template<typename...Args>
using AptPoorNavigator = PoorNavigator<std::function, std::unordered_multimap>
    ::Mold<AptRolodex>
    ::template Mold<Args...>;

}

#endif