// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_BURSTER_H
#define MOUSIR_BURSTER_H

#include "conceptrodon/functivore/apply_return_type.hpp"
#include "conceptrodon/functivore/concepts/invoke_return_as.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/mouldivore/concepts/deceive.hpp"
#include "mousir/cheesential/decipher.hpp"
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
struct Burster
{
    template<typename TheKey>
    struct ProtoMold
    {
        struct Detail
        {
            template<typename...Parameters>
            struct ProtoMold
            {
                using Key = TheKey;
                using TypeSignature = Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<Parameters...>;
                using Function = FunctionWrapper<Conceptrodon::Functivore::ApplyReturnType<bool>::Mold<std::remove_reference_t<Parameters>&..., Cheesential::Decipher<Parameters>...>>;
                using Map = TheMap<Key, Function>;
                
                template <typename Burst>
                requires std::invocable<Burst, Parameters...>
                Key connect
                (
                    Key const & key,
                    Burst&& burst
                )
                {
                    map.emplace
                    (
                        key,
                        wrap(std::forward<Burst>(burst))
                    );
                    return key;
                }
                
                template <typename ObjectPointer, typename Burst>
                Key connect
                (
                    Key const & key,
                    ObjectPointer&& object_pointer,
                    Burst&& burst
                )
                {
                    map.emplace
                    (
                        key,
                        wrap
                        (
                            std::forward<ObjectPointer>(object_pointer),
                            std::forward<Burst>(burst)
                        )
                    );
                    return key;
                }

                template <typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                Function wrap(Burst&& burst)
                {
                    return [burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }
            
                template <typename Burst>
                requires
                    Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                &&  Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Burst>>
                Function wrap(Burst&& burst)
                {
                    if constexpr (std::is_lvalue_reference_v<Burst>)
                    {
                        return [burst]
                         (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        { return burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                    }
            
                    else
                    {
                        return [burst=std::move(burst)]
                         (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        { return burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                    }
                }

                template <typename Burst>
                Function wrap(Burst&& burst)
                {
                    return [burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }
            
                template <typename Burst>
                requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Burst>>
                Function wrap(Burst&& burst)
                {
                    if constexpr (std::is_lvalue_reference_v<Burst>)
                    {
                        return [burst]
                         (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        {
                            burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                            return true;
                        };
                    }
            
                    else
                    {
                        return [burst=std::move(burst)]
                         (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        {
                            burst((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                            return true;
                        };
                    }
                }

/**** Member Function Pointer ****/
/**** Return Boolean ****/
                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                && Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                && Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Burst>())), Parameters...>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer=std::move(object_pointer), burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }
                
                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                && Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return (object_pointer.get() ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                && Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Burst>())), Parameters...>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::InvokeReturnAs<Burst, bool, Parameters...>
                && Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer=std::move(object_pointer), burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    { return (object_pointer.get() ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...); };
                }

/**** Return Others ****/
                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Burst>())), Parameters...>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer=std::move(object_pointer), burst]
                     (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }
                
                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                    (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        (object_pointer.get() ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Burst>())), Parameters...>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer, burst]
                    (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        (object_pointer ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }

                template <typename ObjectPointer, typename Burst>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Burst>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Burst&& burst)
                {
                    return [object_pointer=std::move(object_pointer), burst]
                    (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        (object_pointer.get() ->* burst)((deciphers.isForwardSafe() ? std::forward<Parameters>(args) : args)...);
                        return true;
                    };
                }

                template<typename GivenKey, typename...Args>
                requires std::invocable<TypeSignature, Args...>
                && std::convertible_to<GivenKey, Key>
                auto execute(GivenKey const & the_key, Args&&...args)
                {
                    auto [begin, end] = map.equal_range(static_cast<Key const &>(the_key));
                    bool result {false};
                    for (auto iter {begin}; iter != end; iter++)
                    {
                        result = result || iter -> second(args..., Cheesential::Decipher<Parameters>{std::type_identity<Args>{}}...);
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

}

#endif