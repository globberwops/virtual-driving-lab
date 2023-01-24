#pragma once

#include <bitset>
#include <climits>
#include <cstddef>
#include <functional>
#include <type_traits>

namespace vdlab
{

template <class T>
concept Enum = std::is_enum_v<T>;

namespace details
{

template <Enum T>
constexpr auto ToUnderlyingType(T lhs)
{
    return static_cast<std::underlying_type_t<T>>(lhs);
}

} // namespace details

template <Enum T>
constexpr auto operator~(T lhs)
{
    return static_cast<T>(~details::ToUnderlyingType(lhs));
}

template <Enum T>
constexpr auto operator|(T lhs, T rhs)
{
    return static_cast<T>(details::ToUnderlyingType(lhs) | details::ToUnderlyingType(rhs));
}

template <Enum T>
constexpr auto operator&(T lhs, T rhs)
{
    return static_cast<T>(details::ToUnderlyingType(lhs) & details::ToUnderlyingType(rhs));
}

template <Enum T>
constexpr auto operator^(T lhs, T rhs)
{
    return static_cast<T>(details::ToUnderlyingType(lhs) ^ details::ToUnderlyingType(rhs));
}

template <Enum T>
constexpr auto operator|=(T &lhs, T rhs)
{
    auto lhs_underlying = details::ToUnderlyingType(lhs);
    lhs_underlying |= details::ToUnderlyingType(rhs);
    return lhs = static_cast<T>(lhs_underlying);
}

template <Enum T>
constexpr auto operator&=(T &lhs, T rhs)
{
    auto lhs_underlying = details::ToUnderlyingType(lhs);
    lhs_underlying &= details::ToUnderlyingType(rhs);
    return lhs = static_cast<T>(lhs_underlying);
}

template <Enum T>
constexpr auto operator^=(T &lhs, T rhs)
{
    auto lhs_underlying = details::ToUnderlyingType(lhs);
    lhs_underlying ^= details::ToUnderlyingType(rhs);
    return lhs = static_cast<T>(lhs_underlying);
}

template <Enum T>
constexpr auto test(T lhs, T rhs)
{
    return static_cast<bool>(lhs & rhs);
}

template <Enum T>
inline auto operator<<(std::ostream &os, T lhs) -> std::ostream &
{
    os << std::bitset<CHAR_BIT * sizeof(lhs)>(details::ToUnderlyingType(lhs));
    return os;
}

} // namespace vdlab
