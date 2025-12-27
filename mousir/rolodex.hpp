// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_ROLODEX_H
#define MOUSIR_ROLODEX_H

#include <map>

namespace Mousir {

template<template<typename...> class TheMap=std::map>
struct Rolodex
{
    template<typename TheKey=int>
    struct ProtoMold
    {
        using Key = TheKey;
        using Map = TheMap<Key, bool>;
        using key_type = Map::key_type;
        
        ProtoMold(): map{}, counter{-1} {}

        bool is_valid() const
        { return map.find(counter) != map.end(); }

        auto const & get_counter() const
        { return counter; }

        auto find(Key const& key) const
        { return map.find(key); }

        auto find(Key const& key)
        { return map.find(key); }

        auto const & increment(bool flag=false)
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