#pragma once

#include "VirtualDrivingLab/Flags.hpp"

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <cstddef>
#include <memory>
#include <string_view>
#include <type_traits>

namespace vdlab::com
{

template <class T>
concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

struct CreateOnly
{
};

struct OpenOrCreate
{
};

struct OpenOnly
{
};

template <class CreationTag>
class Channel
{
  public:
    enum class Flags : std::uint8_t
    {
        CreateOnly = 1 << 0,
        OpenOrCreate = 1 << 1,
        OpenOnly = 1 << 2,
        ReadOnly = 1 << 3,
        ReadWrite = 1 << 4
    };

    ~Channel() noexcept = default;
    Channel(const Channel &other) = delete;
    auto operator=(const Channel &other) = delete;
    Channel(Channel &&other) noexcept = default;
    auto operator=(Channel &&other) noexcept -> Channel & = default;

    explicit Channel(std::string_view name) noexcept : m_name{name}

    {
        namespace bi = boost::interprocess;
        if constexpr (std::is_same_v<CreationTag, CreateOnly>)
        {
            m_shm_remover = ShmRemover{m_name};
            m_managed_shm = bi::managed_shared_memory{bi::create_only, m_name.c_str(), 65536};
        }
        else if constexpr (std::is_same_v<CreationTag, OpenOrCreate>)
        {
            m_shm_remover = ShmRemover{m_name};
            m_managed_shm = bi::managed_shared_memory{bi::open_or_create, m_name.c_str(), 65536};
        }
        else if constexpr (std::is_same_v<CreationTag, OpenOnly>)
        {
            m_managed_shm = bi::managed_shared_memory{bi::open_only, m_name.c_str()};
        }
    };

    [[nodiscard]] auto GetName() const noexcept
    {
        return m_name;
    }

    template <TriviallyCopyable Type>
    void Write(Type value) noexcept
    {
        m_managed_shm.construct<Type>("value")(value);
    }

    template <TriviallyCopyable Type>
    auto Read() noexcept -> Type
    {
        auto [ptr, count] = m_managed_shm.find<Type>("value");
        if (ptr != nullptr && count == 1U)
        {
            return *ptr;
        }

        return {};
    }

  private:
    struct ShmRemover
    {
        ~ShmRemover() noexcept
        {
            if (!m_name.empty())
            {
                boost::interprocess::shared_memory_object::remove(m_name.c_str());
            }
        }

        explicit ShmRemover(std::string_view name = "") noexcept : m_name{name}
        {
            if (!m_name.empty())
            {
                boost::interprocess::shared_memory_object::remove(m_name.c_str());
            }
        }

        std::string m_name;
    };

    std::string m_name;
    // Flags m_shm_flags;
    ShmRemover m_shm_remover;
    boost::interprocess::managed_shared_memory m_managed_shm;
};

} // namespace vdlab::com
