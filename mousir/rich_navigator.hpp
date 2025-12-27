// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RICH_NAVIGATOR_H
#define MOUSIR_RICH_NAVIGATOR_H

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
struct RichNavigator
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
                             
/**** Pointer to Function ****//**** LValue ****/
/**** Copy ****/

                        template <typename Counter, typename Navigate>
                        Function wrap(Counter const & counter, Navigate&& navigate)
                        {
                            return [this, counter, navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        (navigate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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
                    
                        template <typename Counter, typename Navigate>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Navigate>>
                        Function wrap(Counter const & counter, Navigate&& navigate)
                        {
                             
/**** Function Object ****//**** LValue ****/
/**** Copy ****/
                            if constexpr (std::is_lvalue_reference_v<Navigate>)
                            {
                                return [this, counter, navigate]
                                (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = static_cast<bool>
                                            (navigate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                            
                                            return flag;
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
                                return [counter, navigate=std::move(navigate), this]
                                (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = static_cast<bool>
                                            (navigate((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                            
                                            return flag;
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

                        template <typename Counter, typename ObjectPointer, typename Navigate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Navigate>
                        && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Navigate&& navigate)
                        {
                            return [this, counter, object_pointer, navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        ((object_pointer ->* navigate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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
                            
                        template <typename Counter, typename ObjectPointer, typename Navigate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Navigate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Navigate>())), Parameters...>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Navigate&& navigate)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        ((object_pointer ->* navigate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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

                        template <typename Counter, typename ObjectPointer, typename Navigate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Navigate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Navigate&& navigate)
                        {
                            return [this, counter, object_pointer, navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        ((object_pointer.get() ->* navigate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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

                        template <typename Counter, typename ObjectPointer, typename Navigate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Navigate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Navigate>())), Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Navigate&& navigate)
                        {
                            return [this, counter, object_pointer, navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        ((object_pointer ->* navigate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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

                        template <typename Counter, typename ObjectPointer, typename Navigate>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Navigate>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Navigate&& navigate)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), navigate]
                            (Parameters &...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = static_cast<bool>
                                        ((object_pointer.get() ->* navigate)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...));
                                        
                                        return flag;
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