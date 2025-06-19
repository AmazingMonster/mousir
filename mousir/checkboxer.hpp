// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHECKBOXER_H
#define MOUSIR_CHECKBOXER_H

#include <map>

namespace Mousir {

template<template<typename...> class TheMap=std::map>
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

        Key increment(bool flag=false)
        {
            counter++;
            map.emplace(counter, flag);
            return counter;
        }

        auto begin() const
        { return map.begin(); }

        auto begin()
        { return map.begin(); }

        auto end() const
        { return map.end(); }

        auto end()
        { return map.end(); }

        Map map;
        Key counter;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

}

#endif