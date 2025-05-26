#ifndef MOUSIR_CHEESENTIAL_ACTIVATOR_H
#define MOUSIR_CHEESENTIAL_ACTIVATOR_H

#include "conceptrodon/functivore/concepts/invoke_result_in.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <type_traits>
#include "mousir/cheesential/executor.hpp"
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <utility>

namespace Mousir {
namespace Cheesential {

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
                    using AncestorTemplate = Executor<FunctionWrapper, TheMap>
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

                        ProtoMold(Correspondence const & the_correspondence)
                        : correspondence{the_correspondence} {}

                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::InvokeResultIn<Activate, bool, Parameters...>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, this]
                            (Parameters&...args) -> bool
                            { return correspondence.at(counter) = activate(std::forward<Parameters>(args)...); };
                        }

                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::InvokeResultIn<Activate, bool, Parameters...>
                        && Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, this]
                            (Parameters&...args) -> bool
                            { return correspondence.at(counter) = derived ->* activate(std::forward<Parameters>(args)...); };
                        }
                    
                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::InvokeResultIn<Activate, bool, Parameters...>
                        && Conceptrodon::Mouldivore::Confess<std::is_class, Activate>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Activate>)
                            {
                                return [counter, &activate, derived = static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                { return derived -> correspondence.at(counter) = activate(std::forward<Parameters>(args)...); };
                            }
                    
                            else
                            {
                                return [counter, activate=std::move(activate), derived = static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                { return derived -> correspondence.at(counter) = activate(std::forward<Parameters>(args)...); };
                            }
                        }

                        template <typename Activate, typename Counter>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, derived = static_cast<Derived*>(this)]
                            (Parameters&...args) -> bool
                            {
                                activate(activate(std::forward<Parameters>(args)...));
                                return derived -> correspondence.at(counter) = true;
                            };
                        }

                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Activate>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            return [counter, activate, derived = static_cast<Derived*>(this)]
                            (Parameters&...args) -> bool
                            {
                                derived ->* activate(std::forward<Parameters>(args)...);
                                return derived -> correspondence.at(counter) = true;
                            };
                        }
                    
                        template <typename Activate, typename Counter>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, Activate>
                        Function wrap(Activate&& activate, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Activate>)
                            {
                                return [counter, &activate, derived = static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                {
                                    activate(std::forward<Parameters>(args)...);
                                    return derived -> correspondence.at(counter) = true;
                                };
                            }
                    
                            else
                            {
                                return [counter, activate=std::move(activate), derived = static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                {
                                    activate(std::forward<Parameters>(args)...);
                                    return derived -> correspondence.at(counter) = true;
                                };
                            }
                        }
                    
                        template <typename Counter>
                        Function wrap(std::nullptr_t, Counter const & counter)
                        {
                            return [counter, derived = static_cast<Derived*>(this)]
                            (Parameters&...) -> bool
                            { return derived -> correspondence.at(counter) = true; };
                        }

                        Correspondence const & correspondence;
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