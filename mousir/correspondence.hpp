// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CORRESPONDENCE_H
#define MOUSIR_CORRESPONDENCE_H

#include <unordered_map>

namespace Mousir {

template
<template<typename...> class TheMap=std::unordered_multimap>
struct Correspondence
{
    template<typename TheKey=int>
    struct ProtoMold
    {
        using Key = TheKey;
        using Map = TheMap<Key, bool>;
        
        ProtoMold(): map{}, counter{} {}

        Key get()
        { return counter; }

        bool at(Key const& key)
        { return map.at(key); }

        Key increment()
        {
            counter++;
            map.emplace(counter, false);
            return counter;
        }

        Map map;
        Key counter;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

}

#endif