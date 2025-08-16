// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RELEASOR_H
#define MOUSIR_RELEASOR_H

#include "mousir/cheesential/executor.hpp"
#include "conceptrodon/functivore/concepts/invoke_return_as.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <functional>
#include <unordered_map>
#include <utility>

namespace Mousir {

template
<
    template<typename...> class FunctionWrapper=std::function,
    template<typename...> class TheMap=std::unordered_multimap
>
struct Releasor
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

                        template <typename Counter, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        Function wrap(Counter const & counter, Release&& release)
                        {
                            return [this, counter, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                    
                        template <typename Counter, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Release>>
                        Function wrap(Counter const & counter, Release&& release)
                        {
                            if constexpr (std::is_lvalue_reference_v<Release>)
                            {
                                return [this, counter, release]
                                (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'release' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'release'.
                                            flag = ! release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                    
                            else
                            {
                                return [counter, release=std::move(release), this]
                                (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'release' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'release'.
                                            flag = ! release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename Release>
                        Function wrap(Counter const & counter, Release&& release)
                        {
                            return [this, counter, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                    
                        template <typename Counter, typename Release>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Release>>
                        Function wrap(Counter const & counter, Release&& release)
                        {
                            if constexpr (std::is_lvalue_reference_v<Release>)
                            {
                                return [this, counter, release]
                                (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'release' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'release'.
                                            release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                    
                            else
                            {
                                return [counter, release=std::move(release), this]
                                (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                                {
                                    auto iter = correspondence.find(counter);
                                    if (iter != correspondence.end())
                                    {
                                        bool& flag {(*correspondence.find(counter)).second};
                                        if (flag)
                                        {
                                            flag = false;
                                            // It is possible for 'release' to check whether all flags are down.
                                            // Thus assign false to the flag before calling 'release'.
                                            release((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                    
                        template <typename Counter>
                        Function wrap(Counter const & counter)
                        {
                            return [counter, this]
                            (std::remove_reference_t<Parameters>&..., Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
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

/**** Member Function Pointer ****/
/**** Return Boolean ****/
                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                            
                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Release>())), Parameters...>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! (object_pointer.get() ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Release>())), Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = ! (object_pointer.get() ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

/**** Return Others ****/
                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Confess<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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
                            
                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Release>())), Parameters...>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer.get() ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        && std::invocable<decltype(std::declval<ObjectPointer>().operator->*(std::declval<Release>())), Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_lvalue_reference, ObjectPointer>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer, release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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

                        template <typename Counter, typename ObjectPointer, typename Release>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        && Conceptrodon::Mouldivore::Deceive<std::is_pointer, std::remove_cvref_t<ObjectPointer>>
                        Function wrap(Counter const & counter, ObjectPointer&& object_pointer, Release&& release)
                        {
                            return [this, counter, object_pointer = std::move(object_pointer), release]
                            (std::remove_reference_t<Parameters>&...args, Cheesential::Decipher<Parameters>...deciphers) mutable -> bool
                            {
                                auto iter = correspondence.find(counter);
                                if (iter != correspondence.end())
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer.get() ->* release)((deciphers.is_forward_safe() ? std::forward<Parameters>(args) : args)...);
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