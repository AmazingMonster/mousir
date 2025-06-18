// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHECKBOXER_H
#define MOUSIR_CHECKBOXER_H

#include <unordered_map>

namespace Mousir {

template<template<typename...> class TheMap=std::unordered_map>
struct Checkboxer
{
    template<typename TheKey=int>
    struct ProtoMold
    {
        using Key = TheKey;
        using Map = TheMap<Key, bool>;
        
        ProtoMold(): map{}, counter{-1} {}

        bool isValid()
        { return map.find(counter) != map.end(); }

        Key get()
        { return counter; }

        auto find(Key const& key) const
        { return map.find(key); }

        auto find(Key const& key)
        { return map.find(key); }

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