// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_CHEESENTIAL_EXECUTOR_H
#define MOUSIR_CHEESENTIAL_EXECUTOR_H

#include "conceptrodon/functivore/apply_return_type.hpp"
#include "mousir/cheesential/execute.hpp"
#include <concepts>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <utility>

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
            template<typename...Parameters>
            struct ProtoMold
            {
                struct Detail
                {
                    template<typename Derived>
                    struct ProtoMold
                    {
                        using Key = TheKey;
                        using TypeSignature = Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<Parameters...>;
                        using Function = FunctionWrapper<Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<std::remove_reference_t<Parameters>&...>>;
                        using Map = TheMap<Key, Function>;

                        template <typename Counter, typename Execute>
                        requires std::invocable<Execute, Parameters...>
                        void insert
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
                                    std::forward<Execute>(exec),
                                    counter
                                )
                            );
                        }

                        template <typename Counter, typename ObjectPointer, typename Execute>
                        void insert
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
                                    std::forward<ObjectPointer>(object_pointer),
                                    std::forward<Execute>(exec),
                                    counter
                                )
                            );
                        }

                        template<typename GivenKey, typename...Args>
                        requires std::invocable<TypeSignature, Args...>
                        && std::convertible_to<GivenKey, Key>
                        auto execute(GivenKey const & the_key, Args&&...args)
                        { Cheesential::execute(map, static_cast<Key const &>(the_key), args...); }

                        Map map;
                    };
                };

                template<typename...Args>
                using Mold = Detail::template ProtoMold<Args...>;
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