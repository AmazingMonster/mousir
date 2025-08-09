// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_RELEASOR_H
#define MOUSIR_APT_RELEASOR_H

#include "mousir/releasor.hpp"
#include "mousir/apt_checkboxer.hpp"

namespace Mousir {

template<typename TheKey>
struct AptReleasor
{
    template<typename...Args>
    using Mold = Releasor<std::function, std::unordered_multimap>
    ::Mold<TheKey>
    ::template Mold<AptCheckBoxer>
    ::template Mold<Args...>;
};

}

#endif