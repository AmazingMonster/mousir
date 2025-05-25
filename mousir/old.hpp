#ifndef MOUSIR_ACTIVATOR_H
#define MOUSIR_ACTIVATOR_H

#include <concepts>
#include "conceptrodon/functivore/concepts/same_type_signature_as.hpp"
#include "conceptrodon/functivore/get_type_signature.hpp"
#include "conceptrodon/functivore/get_return_type.hpp"

namespace Coordinatress{

class Executor
{
protected:
    class FullRange;

protected:
    Executor()=default;

    template <typename Key, typename Map, typename...Args>
    bool execute(Map &map, Key const &key, Args&&...args)
    {
        auto [begin, end] = map.equal_range(key);

        for (auto iter {begin}; iter != end; iter++)
        {
            iter -> second(std::forward<Args>(args)...);
        }
    }

    template <typename Key, typename Map, typename...Args>
    requires std::same_as<Key, FullRange>
    void execute(Map &map, Args&&...args)
    {
        for (auto& pair : map)
        {
            pair.second(std::forward<Args>(args)...);
        }
    }

    template <typename Key, typename Map, typename...Args>
    requires
        std::same_as<Key, FullRange> 
    &&  std::same_as<typename Map::mapped_type::result_type, bool>
    bool execute(Map &map, Args&&...args)
    {
        bool result {false};

        for (auto& pair : map)
        {
            result = result || pair.second(std::forward<Args>(args)...);
        }

        return result;
    }

    template <typename Key, typename Map, typename...Args>
    requires std::same_as<typename Map::mapped_type::result_type, bool>
    bool execute(Map &map, Key const &key, Args&&...args)
    {
        auto [begin, end] = map.equal_range(key);

        bool result {false};

        for (auto iter {begin}; iter != end; iter++)
        {
            result |= iter -> second(std::forward<Args>(args)...);
        }

        return result;
    }
};




template <typename Candidate, typename Target>
concept SameParameterListOrExistentialCrisis
=   std::same_as<Candidate, std::nullptr_t>
||  (Conceptuality::IsVariadic_v<Target> && Target::template same_parameters<Candidate>);

template <typename Candidate, typename Target>
struct HasSameParameterListOrExistentialCrisis
{ static constexpr bool value = SameParameterListOrExistentialCrisis<Candidate, Target>; };

template <typename Candidate, typename Target>
concept PredicateSameParameterListOrExistentialCrisis
=   std::same_as<Candidate, std::nullptr_t>
||  (
            Conceptuality::ThreeWayResponse<Candidate>
        &&  Conceptuality::IsVariadic_v<Target>
        &&  Target::template same_parameters<Candidate>
    );

template
<
    typename TheActivationKey,
    typename TheActivationParameterList,
    typename TheReleaseKey,
    typename TheReleaseParameterList
>
requires
    Conceptuality::NoCVRef
    <
        TheActivationKey,
        TheActivationParameterList,
        TheReleaseKey,
        TheReleaseParameterList
    >
&&  Compass::AllHasherable<TheActivationKey, TheReleaseKey>
&&  Conceptuality::AllVariadic<TheActivationParameterList, TheReleaseParameterList>
class Activator : public Executor
{

public:
    using ActivationKey = TheActivationKey;
    using ActivationParameterList = TheActivationParameterList;
    using ActivationSignature = typename ActivationParameterList::template apply_return<bool>;

public:
    using ReleaseKey = TheReleaseKey;
    using ReleaseParameterList = TheReleaseParameterList;
    using ReleaseSignature = typename ReleaseParameterList::template apply_return<void>;

protected:
    using FlagMap = std::unordered_map<int, bool>;
    using ActivationMap = std::unordered_multimap
    <
        ActivationKey,
        std::function<ActivationSignature>,
        Compass::Hasher<ActivationKey>
    >;
    using ReleaseMap = std::unordered_multimap
    <
        ReleaseKey,
        std::function<ReleaseSignature>,
        Compass::Hasher<ReleaseKey>
    >;

public:
    Activator() : Executor{}, counter {0} {}

    virtual ~Activator()=default;

public:
    template <typename Derived, typename Activate, typename Release>
    requires
        std::derived_from<Derived, Activator>
    &&  PredicateSameParameterListOrExistentialCrisis<Activate, ActivationParameterList>
    &&  SameParameterListOrExistentialCrisis<Release, ReleaseParameterList>
    int insert
    (
        ActivationKey const &activation_key,
        Activate&& activate,
        ReleaseKey const &release_key,
        Release&& release
    )
    {
        counter ++;
        flag_map.insert_or_assign(counter, false);
        activation_map.insert
        (
            std::make_pair
            (
                activation_key,
                getActivate<Derived>
                (
                    std::forward<Activate>(activate),
                    counter,
                    ActivationParameterList{}
                )
            )
        );
        release_map.insert
        (
            std::make_pair
            (
                release_key,
                getRelease<Derived>
                (
                    std::forward<Release>(release),
                    counter,
                    ReleaseParameterList{}
                )
            )
        );
        return counter;
    }

protected:




protected:
    template <typename Derived, typename Release, typename...Args>
    requires Conceptuality::FunctionPotential<Release>
    std::function<ReleaseSignature> getRelease (Release&& release, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, release, derived=static_cast<Derived* >(this)]
        (Args&...args) -> bool
        {
            bool& flag {derived -> flag_map.at(key)};
            if (flag)
            {
                flag = false;
                // It is possible for 'release' to check whether all flags are down.
                // Thus assign false to the flag before calling 'release'.
                release(std::forward<Args>(args)...);
                return true;
            }
            return false;
        };
    }



    template <typename Derived, typename Release, typename...Args>
    requires std::is_member_function_pointer_v<Release>
    std::function<ReleaseSignature> getRelease (Release&& release, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, release, derived=static_cast<Derived* >(this)]
        (Args&...args) -> bool
        {
            bool& flag {derived -> flag_map.at(key)};
            if (flag)
            {
                flag = false;
                // It is possible for 'release' to check whether all flags are down.
                // Thus assign false to the flag before calling 'release'.
                (derived ->* release)(std::forward<Args>(args)...);
                return true;
            }
            return false;
        };
    }


    template <typename Derived, typename Release, typename...Args>
    requires std::is_class_v<Derived>
    std::function<ReleaseSignature> getRelease (Release&& release, int key, Conceptuality::Variadic<Args...>)
    {
        if constexpr (std::is_lvalue_reference_v<Release>)
        {
            return [key, &release, derived=static_cast<Derived* >(this)]
            (Args&...args) -> bool
            {
                bool& flag {derived -> flag_map.at(key)};
                if (flag)
                {
                    flag = false;
                    // It is possible for 'release' to check whether all flags are down.
                    // Thus assign false to the flag before calling 'release'.
                    release(std::forward<Args>(args)...);
                    return true;
                }
                return false;
            };
        }

        else
        {
            return [key, release=std::move(release), derived=static_cast<Derived* >(this)]
            (Args&...args) -> bool
            {
                bool& flag {derived -> flag_map.at(key)};
                if (flag)
                {
                    flag = false;
                    // It is possible for 'release' to check whether all flags are down.
                    // Thus assign false to the flag before calling 'release'.
                    release(std::forward<Args>(args)...);
                    return true;
                }
                return false;
            };
        }
    }


    template <typename Derived, typename...Args>
    std::function<ReleaseSignature> getRelease (std::nullptr_t, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, derived=static_cast<Derived* >(this)]
        (Args&...) -> bool
        {
            bool& flag {derived -> flag_map.at(key)};
            if (flag)
            {
                flag = false;
                return true;
            }
            return false;
        };
    }




public:
    template <typename...Args>
    requires std::invocable<ActivationSignature, Args...>
    bool directActivation(ActivationKey const &key, Args&&...args)
    { return direct(activation_map, key, std::forward<Args>(args)...); }


    template <typename...Args>
    requires std::invocable<ReleaseSignature, Args...>
    bool directRelease(ReleaseKey const &key, Args&&...args)
    { return direct(release_map, key, std::forward<Args>(args)...); }

protected:
    bool anyFlagUp()
    {
        return std::any_of
        (
            flag_map.begin(),
            flag_map.end(),
            [](const FlagMap::value_type &flag){return flag.second;}
        );
    }

protected:
    FlagMap flag_map;

protected:
    ActivationMap activation_map;
    ReleaseMap release_map;

protected:
    int counter;
};






template <typename TheKey, typename...Args>
requires Conceptuality::NoCVRef<TheKey> && Compass::Hasherable<TheKey>
class Roamer : public Executor
{

public:
    using Key = std::remove_cvref_t<TheKey>;
    using RoamSignature = bool(Args...);

protected:
    using RoamMap = std::unordered_multimap
    <
        Key,
        std::function<RoamSignature>,
        Compass::Hasher<Key>
    >;

public:
    Roamer()=default;
    virtual ~Roamer()=default;

protected:
    template <typename Derived, typename Roam>
    requires
    std::derived_from<Derived, Roamer>
    && Conceptuality::BooleanResponse<Roam>
    && Conceptuality::SameParameters<Roam, Args...>
    void insert(Key const &key, Roam&& roam)
    { roam_map.insert(std::make_pair(key, getRoam<Derived>(std::forward<Roam>(roam)))); }



protected:
    template <typename, typename Roam>
    requires Conceptuality::FunctionPotential<Roam>
    std::function<RoamSignature> getRoam (Roam&& roam)
    {
        return [roam]
        (Args&...args) -> bool
        { return roam(std::forward<Args>(args)... ); };
    }

    template <typename Derived, typename Roam>
    requires std::is_member_function_pointer_v<Roam>
    std::function<RoamSignature> getRoam (Roam&& roam)
    {
        return [roam, derived=static_cast<Derived>(this)]
        (Args&...args) -> bool
        { return (derived ->* roam)(std::forward<Args>(args)...); };
    }

    template <typename Derived, typename Roam>
    requires std::is_class_v<Roam>
    std::function<RoamSignature> getRoam (Roam&& roam)
    {
        if constexpr (std::is_lvalue_reference_v<Roam>)
        {
            return [&roam]
            (Args&...args) -> bool
            { return roam(std::forward<Args>(args)...); };
        }
        else
        {
            return [roam=std::move(roam)]
            (Args&...args) -> bool
            { return roam(std::forward<Args>(args)...); };
        }
    }



protected:
    template <typename...Agreements>
    requires std::invocable<RoamSignature, Agreements...>
    bool directRoam(Key const &key, Agreements&&...agreements)
    { return direct(roam_map, key, std::forward<Agreements>(agreements)...); }


protected:
    RoamMap roam_map;
};


template<typename Derived>
concept DerivedFromActivator = requires
{
    typename Derived::ActivationKey;
    typename Derived::ActivationParameterList;
    typename Derived::ReleaseKey;
    typename Derived::ReleaseParameterList;
    typename Activator
    <
        typename Derived::ActivationKey,
        typename Derived::ActivationParameterList,
        typename Derived::ReleaseKey,
        typename Derived::ReleaseParameterList
    >;

    requires std::derived_from
    <
        Derived,
        Activator
        <
            typename Derived::ActivationKey,
            typename Derived::ActivationParameterList,
            typename Derived::ReleaseKey,
            typename Derived::ReleaseParameterList
        >
    >;
};


template<typename ActivatorLike, typename...TheRoamParameterLists>
requires
    Conceptuality::NoCVRef<ActivatorLike, TheRoamParameterLists...>
&&  DerivedFromActivator<ActivatorLike>
&&  Conceptuality::AllVariadic<TheRoamParameterLists...>
class ActiveRoamer : public ActivatorLike
{

public:
    using ActivatorBase = ActivatorLike;

public:
    using typename ActivatorBase::ActivationParameterList;
    using typename ActivatorBase::ReleaseParameterList;
    using RoamParameterListPack = Conceptuality::Variadic<TheRoamParameterLists...>;
    using RoamSignaturePack = RoamParameterListPack:: template polish<Conceptuality::MakePredicate>;

    template <size_t I>
    using RoamSignatureAt = RoamSignaturePack::template at<I>;

public:
    using typename ActivatorBase::ActivationKey;
    using typename ActivatorBase::ReleaseKey;

protected:
    using RoamMapTuple
    = RoamSignaturePack ::
    template polish<std::function> ::
    template polish
    <
        Conceptuality::Binder
        <
            std::unordered_map,
            int,
            Conceptuality::PlaceHolder<1>
        >
    > ::
    template container<std::tuple>;

protected:
    using Executor::FullRange;

public:
    using ActivatorBase::ActivatorBase;

public:
    template <typename Derived, typename Activate, typename Release, typename...Roams>
    requires
        std::derived_from<Derived, ActiveRoamer>
    &&  RoamParameterListPack::template compare<HasSameParameterListOrExistentialCrisis, Roams...>
    void insert
    (
        ActivationKey const &activation_key,
        Activate&& activate,
        ReleaseKey const &release_key,
        Release&& release,
        Roams&&...roams
    )
    {
        int key {ActivatorBase::template insert<Derived>(activation_key, activate, release_key, release)};
        [key, this, &roams...]<size_t...I>(std::index_sequence<I...>)
        {
            (..., (
            std::get<I>(roam_map_tuple).insert_or_assign
            (
                std::make_pair
                (
                    key,
                    getRoam<I, Derived>
                    (
                        std::forward<Roams>(roams),
                        key,
                        typename RoamParameterListPack::template at<I> {}
                    )
                )
            )));

        }(std::make_index_sequence<RoamParameterListPack::size>{});
    }

protected:
    template <size_t I, typename Derived, typename Roam, typename...Args>
    requires Conceptuality::FunctionPotential<Roam>
    std::function<RoamSignatureAt<I>> getRoam (Roam&& roam, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, roam, derived=static_cast<Derived* >(this)]
        (Args&...args) -> bool
        {
            if (derived -> flag_map.at(key))
            {
                roam(std::forward<Args>(args)...);
                return true;
            }
            return false;
        };
    }

    template <size_t I, typename Derived, typename Roam, typename...Args>
    requires std::is_member_function_pointer_v<Roam>
    std::function<RoamSignatureAt<I>> getRoam (Roam&& roam, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, roam, derived=static_cast<Derived* >(this)]
        (Args&...args) -> bool
        {
            if (derived -> flag_map.at(key))
            {
                (derived ->* roam)(std::forward<Args>(args)...);
                return true;
            }
            return false;
        };

    }

    template <size_t I, typename Derived, typename Roam, typename...Args>
    requires std::is_class_v<Roam>
    std::function<RoamSignatureAt<I>> getRoam (Roam&& roam, int key, Conceptuality::Variadic<Args...>)
    {
        if constexpr (std::is_lvalue_reference_v<Roam>)
        {
            return [key, &roam, derived=static_cast<Derived* >(this)]
            (Args&...args) -> bool
            {
                if (derived -> flag_map.at(key))
                {
                    roam(std::forward<Args>(args)...);
                    return true;
                }
                return false;
            };
        }

        else
        {
            return [key, roam=std::move(roam), derived=static_cast<Derived* >(this)]
            (Args&...args) -> bool
            {
                if (derived -> flag_map.at(key))
                {
                    roam(std::forward<Args>(args)...);
                    return true;
                }
                return false;
            };
        }
    }


    template <size_t I, typename Derived, typename...Args>
    std::function<RoamSignatureAt<I>> getRoam (std::nullptr_t, int key, Conceptuality::Variadic<Args...>)
    {
        return [key, derived=static_cast<Derived* >(this)]
        (Args&...) -> bool
        { return derived -> flag_map.at(key);};
    }

public:
    template <size_t I, typename...Args>
    requires std::invocable<RoamSignatureAt<I>, Args...>
    bool directRoam(Args&&...args)
    { return direct<FullRange>(std::get<I>(roam_map_tuple), std::forward<Args>(args)...); }

protected:
    RoamMapTuple roam_map_tuple;

};

template
<
    typename TheActivationKey,
    typename TheActivationParameterList,
    typename TheReleaseKey,
    typename TheReleaseParameterList,
    typename...TheRoamParameterLists
>
using MakeActiveRoamer = ActiveRoamer
<
    Activator
    <   TheActivationKey,
        TheActivationParameterList,
        TheReleaseKey,
        TheReleaseParameterList
    >,
    TheRoamParameterLists...
>;

template<typename Derived>
concept DerivedFromActiveRoamer = requires
{
    typename Derived::ActivatorBase;
    typename Derived::RoamParameterListPack;
    requires Conceptuality::IsVariadic_v<typename Derived::RoamParameterListPack>;
    typename Derived::RoamParameterListPack::
        template container
        <
            Conceptuality::Fastener
            <
                ActiveRoamer,
                typename Derived::ActivatorBase,
                Conceptuality::PlaceHolder<0>
            >
        >;
    requires std::derived_from
    <
        Derived,
        typename Derived::RoamParameterListPack::
            template container
            <
                Conceptuality::Fastener
                <
                    ActiveRoamer,
                    typename Derived::ActivatorBase,
                    Conceptuality::PlaceHolder<0>
                >
            >
    >;
};

}
#endif // COMMANDER_H
