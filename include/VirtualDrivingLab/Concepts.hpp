#pragma once

#include <cstdint>
#include <string>
#include <type_traits>

namespace vdlab
{

template <typename T>
concept Identifiable = std::is_same_v<decltype(T::identifier), std::uint64_t>;

template <typename T>
concept Nameable = std::is_same_v<decltype(T::name), std::string>;

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <typename T0, typename... Ts>
concept OneOf = std::disjunction_v<std::is_same<T0, Ts>...>;

} // namespace vdlab
