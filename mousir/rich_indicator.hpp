// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RICH_INDICATOR_H
#define MOUSIR_RICH_INDICATOR_H

#include "conceptrodon/concepts/functivore/member_function_pointer_probe.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"
#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include "mousir/cheesential/decipher.hpp"
#include "mousir/cheesential/executor.hpp"
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
struct RichIndicator
{
    template<typename TheKey>
    struct ProtoMold
    {
        struct Detail
        {
            template<typename...Args>
            using AncestorTemplate = Cheesential::Executor<FunctionWrapper, TheMap>
            ::template Mold<TheKey>
            ::template Mold<Args...>;

            template<typename...Parameters>
            struct ProtoMold
            : public AncestorTemplate<ProtoMold<Parameters...>>
            {
                using Ancestor = AncestorTemplate<ProtoMold>;
                using typename Ancestor::Key;
                using typename Ancestor::TypeSignature;
                using typename Ancestor::Function;
                using typename Ancestor::Map;
                using Ancestor::map;
                
                template <typename Indicate>
                requires std::invocable<Indicate, Parameters...>
                Key connect
                (
                    Key const & key,
                    Indicate&& indicate
                )
                {
                    map.emplace
                    (
                        key,
                        wrap(std::forward<Indicate>(indicate))
                    );
                    return key;
                }
                
                template <typename ObjectPointer, typename Indicate>
                Key connect
                (
                    Key const & key,
                    ObjectPointer&& object_pointer,
                    Indicate&& indicate
                )
                {
                    map.emplace
                    (
                        key,
                        wrap
                        (
                            std::forward<ObjectPointer>(object_pointer),
                            std::forward<Indicate>(indicate)
                        )
                    );
                    return key;
                }
                             
/**** Pointer to Function ****//**** LValue ****/
/**** Copy ****/

                template <typename Indicate>
                Function wrap(Indicate&& indicate)
                {
                    return [indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        (indicate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }
            
                template <typename Indicate>
                requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Indicate>>
                Function wrap(Indicate&& indicate)
                {
                             
/**** Function Object ****//**** LValue ****/
/**** Copy ****/

                    if constexpr (std::is_lvalue_reference_v<Indicate>)
                    {
                        return [indicate]
                        (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        {
                            return static_cast<bool>
                            (indicate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                        };
                    }
                             
/**** Function Object ****//**** RValue ****/
/**** Move ****/
            
                    else
                    {
                        return [indicate=std::move(indicate)]
                        (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                        {
                            return static_cast<bool>
                            (indicate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                        };
                    }
                }
                        
/**** Pointer to Member Function ****/
/**** Pointer ****/
/**** Copy ****/

                template <typename ObjectPointer, typename Indicate>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Indicate>
                && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Indicate&& indicate)
                {
                    return [object_pointer, indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        ((object_pointer ->* indicate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }
                            
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `operator->*` ****//**** RValue ****/
/**** Move ****/

                template <typename ObjectPointer, typename Indicate>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Indicate>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Indicate>())), Parameters...>
                Function wrap(ObjectPointer&& object_pointer, Indicate&& indicate)
                {
                    return [object_pointer=std::move(object_pointer), indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        ((object_pointer ->* indicate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }
                            
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `get` Returning a Pointer ****//**** LValue ****/
/**** Copy ****/
                
                template <typename ObjectPointer, typename Indicate>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Indicate>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Indicate&& indicate)
                {
                    return [object_pointer, indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        ((object_pointer.get() ->* indicate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }
                        
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `operator->*` ****//**** LValue ****/
/**** Copy ****/

                template <typename ObjectPointer, typename Indicate>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Indicate>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Indicate>())), Parameters...>
                && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                Function wrap(ObjectPointer&& object_pointer, Indicate&& indicate)
                {
                    return [object_pointer, indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        ((object_pointer ->* indicate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }

/**** Pointer Member Function ****/
/**** Pointer-like ****//**** Implemented `get` Returning a Pointer ****//**** RValue ****/
/**** Move ****/

                template <typename ObjectPointer, typename Indicate>
                requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Indicate>
                && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                Function wrap(ObjectPointer&& object_pointer, Indicate&& indicate)
                {
                    return [object_pointer=std::move(object_pointer), indicate]
                    (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                    {
                        return static_cast<bool>
                        ((object_pointer.get() ->* indicate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                    };
                }
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