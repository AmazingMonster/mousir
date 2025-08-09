// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_APT_PRACTICER_H
#define MOUSIR_APT_PRACTICER_H

#include "mousir/practicer.hpp"
#include "mousir/apt_checkboxer.hpp"

namespace Mousir {

template<typename...Args>
using AptPracticer = Practicer<std::function, std::unordered_multimap>
    ::Mold<AptCheckBoxer>
    ::Mold<AptCheckBoxer::Key>
    ::template Mold<Args...>;

}

#endif