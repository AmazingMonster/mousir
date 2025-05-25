#ifndef MOUSIR_CHEESENTIAL_PRACTICER_H
#define MOUSIR_CHEESENTIAL_PRACTICER_H

#include "conceptrodon/functivore/apply_return_type.hpp"
#include "conceptrodon/functivore/concepts/member_function_pointer_probe.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"
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
struct Practicer
{
    template<typename TheCorrespondenceKey>
    struct ProtoMold
    {
        struct Detail
        {
            template<typename...Parameters>
            struct ProtoMold
            {
                struct Detail
                {
                    template<typename Derived>
                    struct ProtoMold
                    {
                        using Key = TheCorrespondenceKey;
                        using TypeSignature
                        = Conceptrodon::Functivore::ApplyReturnType<void>
                        ::Mold<Parameters&&...>;
                        using Function = FunctionWrapper<TypeSignature>;
                        using Map = TheMap<Key, Function>;
                        
                        template <typename Counter, typename Practice>
                        requires std::invocable<Practice, Parameters...>
                        void insert
                        (
                            Counter const & counter,
                            Key const & key,
                            Practice&& practice
                        )
                        {
                            map.insert
                            (
                                std::make_pair
                                (
                                    key,
                                    static_cast<Derived*>(this) -> wrap
                                    (std::forward<Practice>(practice))
                                )
                            );
                        }

                        template <typename Practice, typename Counter>
                        Function wrap(Practice&& practice)
                        {
                            return [practice]
                            (Parameters&...args) -> void
                            {
                                practice(std::forward<Parameters>(args)...);
                                return;
                            };
                        }

                        template <typename Practice, typename Counter>
                        requires Conceptrodon::Functivore::MemberFunctionPointerProbe<Practice>
                        Function wrap(Practice&& practice)
                        {
                            return [practice, derived=static_cast<Derived* >(this)]
                            (Parameters&...args) -> void
                            {
                                (derived ->* practice)(std::forward<Parameters>(args)...);
                                return;
                            };
                        }
                    
                        template <typename Practice, typename Counter>
                        requires Conceptrodon::Mouldivore::Confess<std::is_class, Practice>
                        Function wrap(Practice&& practice)
                        {
                            if constexpr (std::is_lvalue_reference_v<Practice>)
                            {
                                return [&practice, derived=static_cast<Derived*>(this)]
                                (Parameters&...args) -> void
                                {
                                    practice(std::forward<Parameters>(args)...);
                                    return;
                                };
                            }
                    
                            else
                            {
                                return [practice=std::move(practice), derived=static_cast<Derived*>(this)]
                                (Parameters&...args) -> void
                                {
                                    practice(std::forward<Parameters>(args)...);
                                    return;
                                };
                            }
                        }

                        template<typename GivenCorrespondenceKey, typename...Args>
                        requires std::invocable<Function, Args...>
                        && std::convertible_to<GivenCorrespondenceKey, Key>
                        bool execute(GivenCorrespondenceKey const & the_key, Args&&...args)
                        {
                            if (static_cast<Derived*>(this) -> correspondence[the_key])
                            {
                                auto [begin, end] = map.equal_range(the_key);
                                for (auto iter {begin}; iter != end; iter++)
                                {
                                    iter -> second(std::forward<Args>(args)...);
                                }
                                return true;
                            }
                            return false;
                        }

                        Map map;
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