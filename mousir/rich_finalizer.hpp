// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RICH_FINALIZER_H
#define MOUSIR_RICH_FINALIZER_H

#include "mousir/cheesential/executor.hpp"
#include "conceptrodon/concepts/functivore/member_function_pointer_probe.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"
#include <functional>
#include <unordered_map>
#include <utility>

namespace Mousir {

template
<
    template<typename...> class FunctionWrapper=std::function,
    template<typename...> class TheMap=std::unordered_multimap
>
struct RichFinalizer
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

                        template <typename Counter, typename Finalize>
                        Function wrap(Counter const & counter, Finalize&& finalize)
                        {
                            return [this, counter, finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        (finalize((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
                                }
                                else
                                {
                                    return false;
                                }
                            };
                        }
                    
                        template <typename Counter, typename Finalize>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Finalize>>
                        Function wrap(Counter const & counter, Finalize&& finalize)
                        {
                             
/**** Function Object ****//**** LValue ****/
/**** Copy ****/
                            if constexpr (std::is_lvalue_reference_v<Finalize>)
                            {
                                return [this, counter, finalize]
                                (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'finalize' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'finalize'.
                                            flag = ! static_cast<bool>
                                            (finalize((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                            
                                            return ! flag;
                                        }
                                        else
                                        {
                                            return false; 
                                        }
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
                                return [counter, finalize=std::move(finalize), this]
                                (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'finalize' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'finalize'.
                                            flag = ! static_cast<bool>
                                            (finalize((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                            
                                            return ! flag;
                                        }
                                        else
                                        {
                                            return false; 
                                        }
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

                        template <typename Counter, typename ObjectPointer, typename Finalize>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Finalize>
                        && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Finalize&& finalize)
                        {
                            return [this, counter, object_pointer, finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        ((object_pointer ->* finalize)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
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
                            
                        template <typename Counter, typename ObjectPointer, typename Finalize>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Finalize>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Finalize>())), Parameters...>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Finalize&& finalize)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        ((object_pointer ->* finalize)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
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

                        template <typename Counter, typename ObjectPointer, typename Finalize>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Finalize>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Finalize&& finalize)
                        {
                            return [this, counter, object_pointer, finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        ((object_pointer.get() ->* finalize)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
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

                        template <typename Counter, typename ObjectPointer, typename Finalize>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Finalize>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Finalize>())), Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Finalize&& finalize)
                        {
                            return [this, counter, object_pointer, finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        ((object_pointer ->* finalize)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
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

                        template <typename Counter, typename ObjectPointer, typename Finalize>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Finalize>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Finalize&& finalize)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), finalize]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'finalize' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'finalize'.
                                        flag = ! static_cast<bool>
                                        ((object_pointer.get() ->* finalize)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return ! flag;
                                    }
                                    else
                                    {
                                        return false; 
                                    }
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