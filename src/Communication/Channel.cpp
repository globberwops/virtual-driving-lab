
#include "VirtualDrivingLab/Communication/Channel.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>

#include <cstring>
#include <iostream>
#include <memory>
#include <string_view>

namespace vdlab::com
{

namespace bi = boost::interprocess;

Channel::Channel(std::string_view name, Flags shm_flags) noexcept : m_name{name}, m_shm_flags{shm_flags}
{

    if (test(m_shm_flags, Flags::CreateOnly))
    {
        boost::interprocess::shared_memory_object::remove(m_name.c_str());
        m_managed_shm =
            ShmPtr{new bi::managed_shared_memory{bi::create_only, m_name.c_str(), 65536}, ShmRemover{.m_name{m_name}}};
    }
    if (test(m_shm_flags, Flags::OpenOrCreate))
    {
        m_managed_shm = ShmPtr{new bi::managed_shared_memory{bi::open_or_create, m_name.c_str(), 65536},
                               ShmRemover{.m_name{m_name}}};
    }
    if (test(m_shm_flags, Flags::OpenOnly))
    {
        m_managed_shm =
            ShmPtr{new bi::managed_shared_memory{bi::open_only, m_name.c_str()}, ShmRemover{.m_name{m_name}}};
    }
}

} // namespace vdlab::com
