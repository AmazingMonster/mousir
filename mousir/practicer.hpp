// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_PRACTICER_H
#define MOUSIR_PRACTICER_H

#include "conceptrodon/functivore/apply_return_type.hpp"
#include "conceptrodon/functivore/concepts/invoke_return_as.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <conceptrodon/functivore/get_variadic_type_signature.hpp>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Mousir {

template
<
    template<typename...> class FunctionWrapper=std::function,
    template<typename...> class TheMap=std::unordered_multimap
>
struct Practicer
{
    template<typename TheCorrespondenceKey>
    struct ProtoMold
    {
        struct Detail
        {
            template<typename...Parameters>
            struct ProtoMold
            {
                struct Detail
                {
                    template<typename Correspondence>
                    struct ProtoMold
                    {
                        using Key = TheCorrespondenceKey;
                        using TypeSignature = Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<Parameters...>;
                        using Function = FunctionWrapper<Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<std::remove_reference_t<Parameters>&...>>;
                        using Map = TheMap<Key, Function>;

                        ProtoMold(Correspondence & the_correspondence)
                        : correspondence{the_correspondence} {}
                        
                        template <typename Practice>
                        requires std::invocable<Practice, Parameters...>
                        void insert
                        (
                            Key const & key,
                            Practice&& practice
                        )
                        {
                            map.emplace
                            (
                                key,
                                wrap(std::forward<Practice>(practice))
                            );
                        }
                        
                        template <typename ObjectPointer, typename Practice>
                        void insert
                        (
                            Key const & key,
                            ObjectPointer&& object_pointer,
                            Practice&& practice
                        )
                        {
                            map.emplace
                            (
                                key,
                                wrap
                                (
                                    std::forward<ObjectPointer>(object_pointer),
                                    std::forward<Practice>(practice)
                                )
                            );
                        }

                        template <typename Practice>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Practice, bool, Parameters...>
                        Function wrap(Practice&& practice)
                        {
                            return [practice]
                            (std::remove_reference_t<Parameters>&...args) -> bool
                            { return practice(std::forward<Parameters>(args)...); };
                        }

                        template <typename Practice, typename ObjectPointer>
                        requires
                            Conceptrodon::Functivore::InvokeReturnAs<Practice, bool, Parameters...>
                        &&  Conceptrodon::Functivore::MemberFunctionPointerProbe<Practice>
                        Function wrap(ObjectPointer&& object_pointer, Practice&& practice)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [practice, &object_pointer]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                { return (object_pointer ->* practice)(std::forward<Parameters>(args)...); };
                            }
                    
                            else
                            {
                                return [practice, object_pointer=std::move(object_pointer)]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                { return (object_pointer ->* practice)(std::forward<Parameters>(args)...); };
                            }
                        }
                    
                        template <typename Practice>
                        requires
                            Conceptrodon::Functivore::InvokeReturnAs<Practice, bool, Parameters...>
                        &&  Conceptrodon::Mouldivore::Confess<std::is_class, Practice>
                        Function wrap(Practice&& practice)
                        {
                            if constexpr (std::is_lvalue_reference_v<Practice>)
                            {
                                return [&practice]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                { return practice(std::forward<Parameters>(args)...); };
                            }
                    
                            else
                            {
                                return [practice=std::move(practice)]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                { return practice(std::forward<Parameters>(args)...); };
                            }
                        }

                        template <typename Practice>
                        Function wrap(Practice&& practice)
                        {
                            return [practice]
                            (std::remove_reference_t<Parameters>&...args) -> bool
                            {
                                practice(std::forward<Parameters>(args)...);
                                return true;
                            };
                        }

                        template <typename Practice, typename ObjectPointer>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Practice>
                        Function wrap(ObjectPointer&& object_pointer, Practice&& practice)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [practice, &object_pointer]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                {
                                    (object_pointer ->* practice)(std::forward<Parameters>(args)...);
                                    return true;
                                };
                            }
                    
                            else
                            {
                                return [practice, object_pointer=std::move(object_pointer)]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                {
                                    (object_pointer ->* practice)(std::forward<Parameters>(args)...);
                                    return true;
                                };
                            }
                        }
                    
                        template <typename Practice>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, Practice>
                        Function wrap(Practice&& practice)
                        {
                            if constexpr (std::is_lvalue_reference_v<Practice>)
                            {
                                return [&practice]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                {
                                    practice(std::forward<Parameters>(args)...);
                                    return true;
                                };
                            }
                    
                            else
                            {
                                return [practice=std::move(practice)]
                                (std::remove_reference_t<Parameters>&...args) -> bool
                                {
                                    practice(std::forward<Parameters>(args)...);
                                    return true;
                                };
                            }
                        }

                        template<typename GivenCorrespondenceKey, typename...Args>
                        requires std::invocable<Function, Args...>
                        && std::convertible_to<GivenCorrespondenceKey, Key>
                        bool execute(GivenCorrespondenceKey const & the_key, Args&&...args)
                        {
                            bool& flag {(*correspondence.find(the_key)).second};
                            if (flag)
                            {
                                auto [begin, end] = map.equal_range(the_key);
                                for (auto iter {begin}; iter != end; iter++)
                                {
                                    flag = flag && iter -> second(std::forward<Args>(args)...);
                                }
                                return flag;
                            }
                            return false;
                        }

                        Map map;
                        Correspondence & correspondence;
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

}

#endif