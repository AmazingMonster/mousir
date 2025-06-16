// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef MOUSIR_ACTIVATOR_H
#define MOUSIR_ACTIVATOR_H

#include "conceptrodon/functivore/concepts/invoke_return_as.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <type_traits>
#include "mousir/cheesential/executor.hpp"
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
struct Activator
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

                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Activate, bool, Parameters...>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, this]
                            (std::remove_reference_t<Parameters>&...args) mutable -> bool
                            { return (*correspondence.find(counter)).second = activate(std::forward<Parameters>(args)...); };
                        }

                        template <typename Activate, typename ObjectPointer, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Activate, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        Function wrap(ObjectPointer&& object_pointer, Activate&& activate, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [counter, activate, object_pointer, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { return (*correspondence.find(counter)).second = (object_pointer ->* activate)(std::forward<Parameters>(args)...); };
                            }
                            
                            else
                            {
                                return [counter, activate, object_pointer = std::move(object_pointer), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { return (*correspondence.find(counter)).second = (object_pointer ->* activate)(std::forward<Parameters>(args)...); };
                            }
                        }
                    
                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::InvokeReturnAs<Activate, bool, Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Activate>>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            
                            if constexpr (std::is_lvalue_reference_v<Activate>)
                            {
                                return [counter, &activate, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { return (*correspondence.find(counter)).second = activate(std::forward<Parameters>(args)...); };
                            }
                    
                            else
                            {
                                return [counter, activate=std::move(activate), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                { return (*correspondence.find(counter)).second = activate(std::forward<Parameters>(args)...); };
                            }
                        }

                        template <typename Activate, typename Counter>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, this]
                            (std::remove_reference_t<Parameters>&...args) mutable -> bool
                            {
                                activate(activate(std::forward<Parameters>(args)...));
                                return (*correspondence.find(counter)).second = true;
                            };
                        }

                        template <typename Activate, typename ObjectPointer, typename Counter>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        Function wrap(ObjectPointer&& object_pointer, Activate&& activate, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<ObjectPointer>)
                            {
                                return [counter, activate, object_pointer, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    (object_pointer ->* activate)(std::forward<Parameters>(args)...);
                                    return (*correspondence.find(counter)).second = true;
                                };
                            }
                            
                            else
                            {
                                return [counter, activate, object_pointer, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    (object_pointer ->* activate)(std::forward<Parameters>(args)...);
                                    return (*correspondence.find(counter)).second = true;
                                };
                            }
                        }
                    
                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, std::remove_cvref_t<Activate>>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Activate>)
                            {
                                return [counter, &activate, this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    activate(std::forward<Parameters>(args)...);
                                    return (*correspondence.find(counter)).second = true;
                                };
                            }
                    
                            else
                            {
                                return [counter, activate=std::move(activate), this]
                                (std::remove_reference_t<Parameters>&...args) mutable -> bool
                                {
                                    activate(std::forward<Parameters>(args)...);
                                    return (*correspondence.find(counter)).second = true;
                                };
                            }
                        }
                    
                        template <typename Counter>
                        Function wrap(std::nullptr_t, Counter const & counter)
                        {
                            return [counter, this]
                            (std::remove_reference_t<Parameters>&...) mutable -> bool
                            { return (*correspondence.find(counter)).second = true; };
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