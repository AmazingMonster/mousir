#ifndef MOUSIR_CHEESENTIAL_RELEASOR_H
#define MOUSIR_CHEESENTIAL_RELEASOR_H

#include "mousir/cheesential/executor.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
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
                    using AncestorTemplate = Executor<FunctionWrapper, TheMap>
                        ::template Mold<TheKey>
                        ::template Mold<Parameters...>
                        ::template Mold<Args...>;

                    template<typename Derived>
                    struct ProtoMold
                    : public AncestorTemplate<Derived>
                    {
                        using Ancestor = AncestorTemplate<Derived>;
                        using typename Ancestor::Key;
                        using typename Ancestor::TypeSignature;
                        using typename Ancestor::Function;
                        using typename Ancestor::Map;

                        template <typename Release, typename Counter>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            return [counter, release, derived=static_cast<Derived*>(this)]
                            (Parameters&...args) -> bool
                            {
                                bool& flag {derived -> correspondence.at(counter)};
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

                        template <typename Release, typename Counter>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Release>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            return [counter, release, derived=static_cast<Derived*>(this)]
                            (Parameters&...args) -> bool
                            {
                                bool& flag {derived -> correspondence.at(counter)};
                                if (flag)
                                {
                                    flag = false;
                                    // It is possible for 'release' to check whether all flags are down.
                                    // Thus assign false to the flag before calling 'release'.
                                    (derived ->* release)(std::forward<Parameters>(args)...);
                                    return !flag;
                                }
                                return false;
                            };
                        }
                    
                        template <typename Release, typename Counter>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, Release>
                        Function wrap(Release&& release, Counter const & counter)
                        {
                            if constexpr (std::is_lvalue_reference_v<Release>)
                            {
                                return [counter, &release, derived=static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                {
                                    bool& flag {derived -> correspondence.at(counter)};
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
                                return [counter, release=std::move(release), derived=static_cast<Derived*>(this)]
                                (Parameters&...args) -> bool
                                {
                                    bool& flag {derived -> correspondence.at(counter)};
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
                            return [counter, derived=static_cast<Derived*>(this)]
                            (Parameters&...) -> bool
                            {
                                bool& flag {derived -> flag_map.at(counter)};
                                if (flag)
                                {
                                    flag = false;
                                    return true;
                                }
                                return false;
                            };
                        }
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