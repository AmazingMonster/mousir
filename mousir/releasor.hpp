// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_RELEASOR_H
#define MOUSIR_RELEASOR_H

#include "mousir/cheesential/executor.hpp"
#include "conceptrodon/functivore/concepts/invoke_return_as.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <cstddef>
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
            template<typename...Parameters>
            struct ProtoMold
            {
                struct Detail
                {
                    template<typename...Args>
                    using AncestorTemplate = Cheesential::Executor<FunctionWrapper, TheMap>
                        ::template Mold<TheKey>
                        ::template Mold<Parameters...>
                        ::template Mold<Args...>;

                    template<typename Correspondence>
                    struct ProtoMold
                    : public AncestorTemplate<ProtoMold<Correspondence>>
                    {
                        using Ancestor = AncestorTemplate<ProtoMold>;
                        using typename Ancestor::Key;
                        using typename Ancestor::TypeSignature;
                        using typename Ancestor::Function;
                        using typename Ancestor::Map;
                        ProtoMold(Correspondence & the_correspondence)
                        : correspondence{the_correspondence} {}

                        template <typename Release, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            return [counter, release, this]
                            (std::remove_reference_t<Parameters>&...args) mutable -> bool
                            { 
                                bool& flag {(*correspondence.find(counter)).second};
                                if (flag)
                                {
                                    flag = false;
                                    // It is possible for 'release' to check whether all flags are down.
                                    // Thus assign false to the flag before calling 'release'.
                                    flag = !release(std::forward<Parameters>(args)...);
                                    return !flag;
                                }
                                return false; 
                            };
                        }

                        template <typename Release, typename ObjectPointer, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        Function wrap(ObjectPointer&& object_pointer, Release&& release, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [counter, release, object_pointer, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { 
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = !(object_pointer ->* release)(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                            
                            else
                            {
                                return [counter, release, object_pointer = std::move(object_pointer), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { 
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = !(object_pointer ->* release)(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                        }
                    
                        template <typename Release, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Release, bool, Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Release>>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Release>)
                            {
                                return [counter, &release, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = !release(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                    
                            else
                            {
                                return [counter, release=std::move(release), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { 
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        flag = !release(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                        }

                        template <typename Release, typename Counter>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            return [counter, release, this]
                            (std::remove_reference_t<Parameters>&...args) mutable -> bool
                            {
                                bool& flag {(*correspondence.find(counter)).second};
                                if (flag)
                                {
                                    flag = false;
                                    // It is possible for 'release' to check whether all flags are down.
                                    // Thus assign false to the flag before calling 'release'.
                                    release(std::forward<Parameters>(args)...);
                                    return !flag;
                                }
                                return false;
                            };
                        }

                        template <typename Release, typename ObjectPointer, typename Counter>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        Function wrap(ObjectPointer&& object_pointer, Release&& release, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [counter, release, object_pointer, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { 
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer ->* release)(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                            
                            else
                            {
                                return [counter, release, object_pointer = std::move(object_pointer), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { 
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        (object_pointer ->* release)(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                        }
                    
                        template <typename Release, typename Counter>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Release>>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Release>)
                            {
                                return [counter, &release, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        release(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                    
                            else
                            {
                                return [counter, release=std::move(release), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    bool& flag {(*correspondence.find(counter)).second};
                                    if (flag)
                                    {
                                        flag = false;
                                        // It is possible for 'release' to check whether all flags are down.
                                        // Thus assign false to the flag before calling 'release'.
                                        release(std::forward<Parameters>(args)...);
                                        return !flag;
                                    }
                                    return false;
                                };
                            }
                        }
                    
                        template <typename Counter>
                        Function wrap(std::nullptr_t, Counter const & counter)
                        {
                            return [counter, this]
                            (std::remove_reference_t<Parameters>&...) mutable -> bool
                            {
                                bool& flag {(*correspondence.find(counter)).second};
                                if (flag)
                                {
                                    flag = false;
                                    return true;
                                }
                                return false;
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