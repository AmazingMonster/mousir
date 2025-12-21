// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHEESENTIAL_EXECUTOR_H
#define MOUSIR_CHEESENTIAL_EXECUTOR_H

#include "conceptrodon/metafunctions/functivore/apply_return_type.hpp"
#include <concepts>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include "mousir/cheesential/decipher.hpp"

namespace Mousir {
namespace Cheesential {

template
<
    template<typename...> class FunctionWrapper=std::function,
    template<typename...> class TheMap=std::unordered_multimap
>
struct Executor
{
    template<typename TheKey>
    struct ProtoMold
    {
        struct Detail
        {    
            template<typename Derived>
            struct ProtoMold {};

            template<template<typename...> class DerivedTemplate, typename...Parameters>
            struct ProtoMold<DerivedTemplate<Parameters...>>
            {
                using Derived = DerivedTemplate<Parameters...>;
                using Key = TheKey;
                using TypeSignature = Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<Parameters...>;
                using Function = FunctionWrapper<Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<std::remove_reference_t<Parameters>&..., Decipher<Parameters>...>>;
                using Map = TheMap<Key, Function>;

                template <typename Counter>
                Counter connect
                (
                    Counter const & counter,
                    Key const & key
                )
                {
                    map.emplace
                    (
                        key,
                        static_cast<Derived*>(this) -> wrap(counter)
                    );
                    return counter;
                }

                template <typename Counter, typename Execute>
                requires std::invocable<Execute, Parameters...>
                Counter connect
                (
                    Counter const & counter,
                    Key const & key,
                    Execute&& exec
                )
                {
                    map.emplace
                    (
                        key,
                        static_cast<Derived*>(this) -> wrap
                        (
                            counter,
                            std::forward<Execute>(exec)
                        )
                    );
                    return counter;
                }

                template <typename Counter, typename ObjectPointer, typename Execute>
                Counter connect
                (
                    Counter const & counter,
                    Key const & key,
                    ObjectPointer&& object_pointer,
                    Execute&& exec
                )
                {
                    map.emplace
                    (
                        key,
                        static_cast<Derived*>(this) -> wrap
                        (
                            counter,
                            std::forward<ObjectPointer>(object_pointer),
                            std::forward<Execute>(exec)
                        )
                    );
                    return counter;
                }

                template<typename GivenKey, typename...Args>
                requires std::invocable<TypeSignature, Args...>
                && std::convertible_to<GivenKey, Key>
                auto execute(GivenKey const & the_key, Args&&...args)
                {
                    auto [begin, end] = map.equal_range(static_cast<Key const &>(the_key));
                    bool result {false};

                    if (std::distance(begin, end) == 1)
                    {
                        for (auto iter {begin}; iter != end; iter++)
                        {
                            result = result || iter -> second(args..., Decipher<Parameters>{std::type_identity<Args>{}}...);
                        }
                    }
                    else
                    {
                        for (auto iter {begin}; iter != end; iter++)
                        {
                            result = result || iter -> second(args..., Decipher<Parameters>{std::type_identity<void>{}}...);
                        }
                    }

                    return result;
                }

                Map map;
            };
        };

        template<typename...Args>
        using Mold = Detail::template ProtoMold<Args...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

}}

#endif