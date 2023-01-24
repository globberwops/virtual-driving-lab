#pragma once

#include <iostream>

namespace vdlab
{

/// @brief <a href="https://en.cppreference.com/w/cpp/language/crtp">CRTP</a>  base class for errors
/// @tparam T The derived error class
template <typename T>
struct Error
{
    /// @brief Get the error message
    /// @return The error message
    [[nodiscard]] constexpr auto what() const noexcept
    {
        return T::m_what;
    }

    /// @brief Write the error message to the ostream
    /// @param os
    /// @param error
    /// @return The ostream reference
    friend auto operator<<(std::ostream &os, const Error &error) -> std::ostream &
    {
        os << error.what();
        return os;
    }
};

} // namespace vdlab
