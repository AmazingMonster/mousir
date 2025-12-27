// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RICH_ACTIVATOR_H
#define MOUSIR_RICH_ACTIVATOR_H

#include "cheesential/decipher.hpp"
#include "conceptrodon/concepts/functivore/member_function_pointer_probe.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"
#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include "mousir/cheesential/executor.hpp"
#include <concepts>
#include <type_traits>
#include <functional>
#include <unordered_map>
#include <utility>

namespace Mousir {

template
<
    template<typename...> class FunctionWrapper=std::function,
    template<typename...> class TheMap=std::unordered_multimap
>
struct RichActivator
{
    template<typename TheKey>
    struct ProtoMold
    {
        struct Detail
        {
            template<typename Correspondence>
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

                        ProtoMold(Correspondence & the_correspondence)
                        : correspondence{the_correspondence} {}

/**** Pointer to Function ****/
/**** Copy ****/

                        template <typename Counter, typename Activate>
                        Function wrap(Counter const & counter, Activate&& activate)
                        {
                            return [this, counter, activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};
                                
                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    (activate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));

                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }
                    
                        template <typename Counter, typename Activate>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Activate>>
                        Function wrap(Counter const & counter, Activate&& activate)
                        {
                             
/**** Function Object ****//**** LValue ****/
/**** Copy ****/
                            if constexpr (std::is_lvalue_reference_v<Activate>)
                            {

                                return [this, counter, activate]
                                (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter {correspondence.find(counter)};

                                    if (iter != correspondence.end())
                                    {
                                        iter -> second = static_cast<bool>
                                        (activate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return iter -> second;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                };
                            }
                             
/**** Function Object ****//**** RValue ****/
/**** Move ****/
                    
                            else
                            {

                                return [this, counter, activate=std::move(activate)]
                                (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter {correspondence.find(counter)};

                                    if (iter != correspondence.end())
                                    {
                                        iter -> second = static_cast<bool>
                                        (activate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));

                                        return iter -> second;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                };
                            }
                        }
                        
/**** Pointer to Member Function ****/
/**** Pointer ****/
/**** Copy ****/

                        template <typename Counter, typename ObjectPointer, typename Activate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Activate&& activate)
                        {
                            return [this, counter, object_pointer, activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};

                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    ((object_pointer ->* activate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));

                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }
                            
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `operator->*` ****//**** RValue ****/
/**** Move ****/

                        template <typename Counter, typename ObjectPointer, typename Activate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Activate>())), Parameters...>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Activate&& activate)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};

                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    ((object_pointer ->* activate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                    
                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }
                            
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `get` Returning a Pointer ****//**** LValue ****/
/**** Copy ****/

                        template <typename Counter, typename ObjectPointer, typename Activate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Activate&& activate)
                        {
                            return [this, counter, object_pointer, activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};

                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    ((object_pointer.get() ->* activate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                    
                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }
                        
/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `operator->*` ****//**** LValue ****/
/**** Copy ****/

                        template <typename Counter, typename ObjectPointer, typename Activate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Activate>())), Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Activate&& activate)
                        {
                            return [this, counter, object_pointer, activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};
                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    ((object_pointer ->* activate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                    
                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }

/**** Pointer to Member Function ****/
/**** Pointer-like ****//**** Implemented `get` Returning a Pointer ****//**** RValue ****/
/**** Move ****/

                        template <typename Counter, typename ObjectPointer, typename Activate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Activate&& activate)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), activate]
                            (Parameters const &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter {correspondence.find(counter)};

                                if (iter != correspondence.end())
                                {
                                    iter -> second = static_cast<bool>
                                    ((object_pointer.get() ->* activate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                    
                                    return iter -> second;
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }

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