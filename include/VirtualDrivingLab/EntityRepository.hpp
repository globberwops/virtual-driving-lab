#pragma once

#include "VirtualDrivingLab/Concepts.hpp"
#include "VirtualDrivingLab/Error.hpp"

#include <expected>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

namespace vdlab
{

using EntityType = std::uint64_t;

// TODO:
// * customize EntityType
// * revise m_entities
template <typename... Components>
class EntityRepository
{
  public:
    /// @brief Error for EntityNotFound
    struct EntityNotFound : public Error<EntityNotFound>
    {
        /// @brief The error message
        static constexpr auto m_what = "EntityRepository::EntityNotFound";
    };

    /// @brief Error for ComponentNotFound
    struct ComponentNotFound : public Error<ComponentNotFound>
    {
        /// @brief The error message
        static constexpr auto m_what = "EntityRepository::ComponentNotFound";
    };

    /// @brief The error types for EntityRepository
    using ErrorType = std::variant<EntityNotFound, ComponentNotFound>;

    /// @brief The result type for EntityRepository
    /// @tparam T
    template <typename T>
    using ResultType = std::expected<std::reference_wrapper<T>, ErrorType>;

    using IndexType = std::vector<EntityType>;
    using DataType = std::tuple<std::map<EntityType, Components>...>;

    /// @brief Add an entity to the repository
    /// @return The entity
    constexpr auto addEntity() noexcept
    {
        // NOTE(globberwops): revise
        m_entities.push_back(std::size(m_entities));
        return m_entities.back();
    }

    /// @brief Check if an entity exists in the repository
    /// @param entity
    /// @return
    constexpr auto hasEntity(EntityType entity) const noexcept
    {
        return std::find(std::begin(m_entities), std::end(m_entities), entity) != std::end(m_entities);
    }

    /// @brief Remove an entity and its components from the repository
    /// @param entity
    /// @return
    constexpr auto removeEntity(EntityType entity)
    {
        removeComponent<Components...>(entity);
        auto erased = std::erase_if(m_entities, [entity](const auto &item) { return item == entity; });
        return erased == 1U;
    }

    /// @brief Add components to an entity
    /// @tparam ...Subset The types of the components to add (will be derived from the args)
    /// @param entity
    /// @param ...component The components to add to the entity
    /// @return The components added to the entity
    template <typename... Subset>
    constexpr auto addComponent(EntityType entity, Subset... component) noexcept -> std::tuple<ResultType<Subset>...>
    {
        return {addComponentImpl<Subset>(entity, component)...};
    }

    /// @brief Remove components from an entity
    /// @tparam ...Subset The components to remove from the entity
    /// @param entity
    /// @return
    template <typename... Subset>
    constexpr auto removeComponent(EntityType entity) noexcept
    {
        return (removeComponentImpl<Subset>(entity) && ...);
    }

    /// @brief Get components of an entity
    /// @tparam ...Subset The types of components to get from the entity
    /// @param entity The entity to get the components from
    /// @return The components of the entity
    template <typename... Subset>
    [[nodiscard]] constexpr auto getComponent(EntityType entity) noexcept -> std::tuple<ResultType<Subset>...>
    {
        return {getComponentImpl<Subset>(entity)...};
    }

    /// @brief Get components of an entity
    /// @tparam ...Subset The types of components to get from the entity
    /// @param entity The entity to get the components from
    /// @return The components of the entity
    template <typename... Subset>
    [[nodiscard]] constexpr auto getComponent(EntityType entity) const noexcept
        -> std::tuple<ResultType<const Subset>...>
    {
        return {getComponentImpl<Subset>(entity)...};
    }

    template <typename... Subset>
    [[nodiscard]] constexpr auto view() noexcept -> std::vector<std::tuple<ResultType<Subset>...>>
    {
        auto view{std::vector<std::tuple<ResultType<Subset>...>>()};
        view.reserve(m_entities.size());

        std::for_each(std::begin(m_entities), std::end(m_entities),
                      [this, &view](auto entity) { view.push_back(getComponent<Subset...>(entity)); });
        return view;
    }

    template <typename... Subset>
    [[nodiscard]] constexpr auto view() const noexcept -> std::vector<std::tuple<ResultType<const Subset>...>>
    {
        auto view{std::vector<std::tuple<ResultType<const Subset>...>>()};
        view.reserve(m_entities.size());

        std::for_each(std::begin(m_entities), std::end(m_entities),
                      [this, &view](auto entity) { view.push_back(getComponent<Subset...>(entity)); });
        return view;
    }

    constexpr auto capacity() const noexcept
    {
        return m_entities.capacity();
    }

    constexpr auto reserve(std::size_t size) noexcept
    {
        m_entities.reserve(size);
    }

    constexpr auto size() const noexcept
    {
        return m_entities.size();
    }

    constexpr auto empty() const noexcept
    {
        return m_entities.empty();
    }

    constexpr auto begin() noexcept
    {
        return m_entities.begin();
    }

    constexpr auto begin() const noexcept
    {
        return m_entities.begin();
    }

    constexpr auto end() noexcept
    {
        return m_entities.end();
    }

    constexpr auto end() const noexcept
    {
        return m_entities.end();
    }

    constexpr auto cbegin() noexcept
    {
        return m_entities.cbegin();
    }

    constexpr auto cend() noexcept
    {
        return m_entities.cend();
    }

    friend auto operator<<(std::ostream &os, const EntityRepository &entity_repository) noexcept -> std::ostream &
    {
        os << "EntityRepository:\n  ";
        (os << ...
            << (std::string{typeid(Components).name()} + ": " +
                std::to_string(std::get<std::map<EntityType, Components>>(entity_repository.m_components).size()) +
                "\n  "));
        return os;
    }

  private:
    IndexType m_entities{};
    DataType m_components{};

    template <OneOf<Components...> Component>
    constexpr auto addComponentImpl(EntityType entity, Component component) noexcept -> ResultType<Component>
    {
        if (std::find(std::begin(m_entities), std::end(m_entities), entity) == std::end(m_entities))
        {
            return std::unexpected<ErrorType>{EntityNotFound{}};
        }

        return std::get<std::map<EntityType, Component>>(m_components).emplace(entity, component).first->second;
    }

    template <OneOf<Components...> Component>
    constexpr auto removeComponentImpl(EntityType entity) noexcept
    {
        return std::get<std::map<EntityType, Component>>(m_components).erase(entity) == 1U;
    }

    template <OneOf<Components...> Component>
    [[nodiscard]] constexpr auto getComponentImpl(EntityType entity) noexcept -> ResultType<Component>
    {
        if (std::find(std::begin(m_entities), std::end(m_entities), entity) == std::end(m_entities))
        {
            return std::unexpected<ErrorType>{EntityNotFound{}};
        }

        auto &map = std::get<std::map<EntityType, Component>>(m_components);
        if (auto iter = map.find(entity); iter != std::end(map))
        {
            return iter->second;
        }

        return std::unexpected<ErrorType>{ComponentNotFound{}};
    }

    template <OneOf<Components...> Component>
    [[nodiscard]] constexpr auto getComponentImpl(EntityType entity) const noexcept -> ResultType<const Component>
    {
        if (std::find(std::begin(m_entities), std::end(m_entities), entity) == std::end(m_entities))
        {
            return std::unexpected<ErrorType>{EntityNotFound{}};
        }

        auto &map = std::get<std::map<EntityType, Component>>(m_components);
        if (auto iter = map.find(entity); iter != std::end(map))
        {
            return iter->second;
        }

        return std::unexpected<ErrorType>{ComponentNotFound{}};
    }
};

} // namespace vdlab
