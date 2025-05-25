#ifndef MOUSIR_CHEESENTIAL_EXECUTE_H
#define MOUSIR_CHEESENTIAL_EXECUTE_H

#include <concepts>
#include "conceptrodon/functivore/concepts/invoke_result_in.hpp"
#include "mousir/configuration.hpp"

namespace Mousir{
namespace Cheesential {

template <typename Key, typename Map, typename...Args>
void execute(Map &map, Key const &key, Args&&...args)
{
    auto [begin, end] = map.equal_range(key);
    for (auto iter {begin}; iter != end; iter++)
    {
        iter -> second(std::forward<Args>(args)...);
    }
}

template <typename Key, typename Map, typename...Args>
requires std::same_as<Key, All>
void execute(Map &map, Args&&...args)
{
    for (auto& pair : map)
    {
        pair.second(std::forward<Args>(args)...);
    }
}

template <typename Key, typename Map, typename...Args>
requires
    std::same_as<Key, All> 
    && Conceptrodon::Functivore::InvokeResultIn<typename Map::mapped_type, bool, Args...>
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
requires Conceptrodon::Functivore::InvokeResultIn<typename Map::mapped_type, bool, Args...>
bool execute(Map &map, Key const &key, Args&&...args)
{
    auto [begin, end] = map.equal_range(key);
    bool result {false};
    for (auto iter {begin}; iter != end; iter++)
    {
        result = result || iter -> second(std::forward<Args>(args)...);
    }
    return result;
}

}}

#endif