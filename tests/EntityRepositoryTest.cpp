#include "VirtualDrivingLab/EntityRepository.hpp"

#include <doctest/doctest.h>

#include <iostream>
#include <ranges>
#include <sstream>
#include <string_view>
#include <variant>

using vdlab::EntityRepository;
using vdlab::EntityType;

struct Position
{
};

struct Velocity
{
};

struct Acceleration
{
};

using Repository = EntityRepository<Position, Velocity, Acceleration>;

TEST_SUITE("EntityRepositoryTest")
{
    TEST_CASE("EntityRepository::reserve, EntityRepository::capacity")
    {
        auto repository{Repository{}};
        WARN_EQ(repository.capacity(), 0U);

        repository.reserve(1U);
        REQUIRE_EQ(repository.capacity(), 1U);
    }

    TEST_CASE("EntityRepository::size, EntityRepository::empty")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());
        WARN_EQ(repository.size(), 0U);

        repository.addEntity();
        REQUIRE_UNARY_FALSE(repository.empty());
        REQUIRE_EQ(repository.size(), 1U);
    }

    TEST_CASE("EntityRepository::addEntity, EntityRepository::hasEntity")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        REQUIRE_EQ(repository.size(), 1U);
        REQUIRE_UNARY(repository.hasEntity(entity));
    }

    TEST_CASE("EntityRepository::removeEntity")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        REQUIRE_UNARY(repository.removeEntity(entity));
        REQUIRE_UNARY_FALSE(repository.hasEntity(entity));
    }

    TEST_CASE("EntityRepository::addComponent")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        SUBCASE("with a single component")
        {
            auto [position] = repository.addComponent<Position>(entity, {});
            REQUIRE_UNARY(position);
        }

        SUBCASE("with multiple components")
        {
            auto [position, velocity, acceleration] =
                repository.addComponent(entity, Position{}, Velocity{}, Acceleration{});
            REQUIRE_UNARY(position);
            REQUIRE_UNARY(velocity);
            REQUIRE_UNARY(acceleration);
        }

        SUBCASE("with an invalid entity")
        {
            auto [position, velocity, acceleration] =
                repository.addComponent(42U, Position{}, Velocity{}, Acceleration{});
            REQUIRE_UNARY_FALSE(position);
            REQUIRE_UNARY_FALSE(velocity);
            REQUIRE_UNARY_FALSE(acceleration);
        }
    }

    TEST_CASE("EntityRepository::getComponent")
    {
        auto ostream{std::ostringstream{}};

        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        repository.addComponent(entity, Position{}, Velocity{});

        SUBCASE("with a single component")
        {
            auto [position] = repository.getComponent<Position>(entity);
            REQUIRE_UNARY(position);
        }

        SUBCASE("with a const repository")
        {
            const auto &const_repository{repository};
            auto [position] = const_repository.getComponent<Position>(entity);
            REQUIRE_UNARY(position);
        }

        SUBCASE("with multiple components")
        {
            auto [position, velocity] = repository.getComponent<Position, Velocity>(entity);
            REQUIRE_UNARY(position);
            REQUIRE_UNARY(velocity);
        }

        SUBCASE("with an invalid entity")
        {
            auto [position] = repository.getComponent<Position>(42U);
            REQUIRE_UNARY_FALSE(position);
            REQUIRE_UNARY(std::holds_alternative<Repository::EntityNotFound>(position.error()));

            ostream << std::get<Repository::EntityNotFound>(position.error());
            REQUIRE(ostream.str() == "EntityRepository::EntityNotFound");
        }

        SUBCASE("with an invalid component")
        {
            auto [acceleration] = repository.getComponent<Acceleration>(entity);
            REQUIRE_UNARY_FALSE(acceleration);
            REQUIRE_UNARY(std::holds_alternative<Repository::ComponentNotFound>(acceleration.error()));

            ostream << std::get<Repository::ComponentNotFound>(acceleration.error());
            REQUIRE(ostream.str() == "EntityRepository::ComponentNotFound");
        }
    }

    TEST_CASE("EntityRepository::removeComponent")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        repository.addComponent(entity, Position{}, Velocity{});

        SUBCASE("with a single component")
        {
            REQUIRE_UNARY(repository.removeComponent<Position>(entity));
        }

        SUBCASE("with multiple components")
        {
            REQUIRE_UNARY(repository.removeComponent<Position, Velocity>(entity));
        }

        SUBCASE("with an invalid entity")
        {
            REQUIRE_UNARY_FALSE(repository.removeComponent<Position>(42U));
        }

        SUBCASE("with an invalid component")
        {
            REQUIRE_UNARY_FALSE(repository.removeComponent<Acceleration>(entity));
        }
    }

    TEST_CASE("EntityRepository::removeEntity")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        SUBCASE("without components")
        {
            REQUIRE_UNARY(repository.removeEntity(entity));
        }

        SUBCASE("with some components")
        {
            repository.addComponent(entity, Position{}, Velocity{});
            REQUIRE_UNARY(repository.removeEntity(entity));
        }

        SUBCASE("with all components")
        {
            repository.addComponent(entity, Position{}, Velocity{}, Acceleration{});
            REQUIRE_UNARY(repository.removeEntity(entity));
        }

        SUBCASE("with an invalid entity")
        {
            REQUIRE_UNARY_FALSE(repository.removeEntity(42U));
        }
    }

    TEST_CASE("EntityRepository::operator<<") // revise
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        auto entity = repository.addEntity();
        WARN_UNARY(repository.hasEntity(entity));

        auto ostream{std::ostringstream{}};

        SUBCASE("without components")
        {
            constexpr std::string_view result = R"(EntityRepository:
  8Position: 0
  8Velocity: 0
  12Acceleration: 0
  )";
            ostream << repository;
            REQUIRE(ostream.str() == result);
        }

        SUBCASE("with some components")
        {
            repository.addComponent(entity, Position{}, Velocity{});
            constexpr std::string_view result = R"(EntityRepository:
  8Position: 1
  8Velocity: 1
  12Acceleration: 0
  )";
            ostream << repository;
            REQUIRE(ostream.str() == result);
        }

        SUBCASE("with all components")
        {
            repository.addComponent(entity, Position{}, Velocity{}, Acceleration{});
            constexpr std::string_view result = R"(EntityRepository:
  8Position: 1
  8Velocity: 1
  12Acceleration: 1
  )";
            ostream << repository;
            REQUIRE(ostream.str() == result);
        }
    }

    TEST_CASE("EntityRepository::view")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        constexpr auto count = 5U;
        repository.reserve(count);
        for (auto i = 0U; i < count; ++i)
        {
            auto entity = repository.addEntity();
            WARN_UNARY(repository.hasEntity(entity));
            repository.addComponent(entity, Position{}, Velocity{}, Acceleration{});
        }
        WARN_EQ(repository.size(), count);

        SUBCASE("with all components")
        {
            for (auto [position, velocity, acceleration] : repository.view<Position, Velocity, Acceleration>())
            {
                REQUIRE_UNARY(position);
                REQUIRE_UNARY(velocity);
                REQUIRE_UNARY(acceleration);
            }
        }

        SUBCASE("with a const repository")
        {
            const auto &const_repository{repository};
            for (auto [position, velocity, acceleration] : const_repository.view<Position, Velocity, Acceleration>())
            {
                REQUIRE_UNARY(position);
                REQUIRE_UNARY(velocity);
                REQUIRE_UNARY(acceleration);
            }
        }
    }

    TEST_CASE("EntityRepository: container interface")
    {
        auto repository{Repository{}};
        WARN_UNARY(repository.empty());

        constexpr auto count = 50U;
        repository.reserve(count);
        for (auto i = 0U; i < count; ++i)
        {
            repository.addEntity();
        }
        WARN_EQ(repository.size(), count);

        SUBCASE("range-based for loop")
        {
            for (auto entity : repository)
            {
                REQUIRE_UNARY(repository.hasEntity(entity));
            }
        }

        SUBCASE("range-based for loop with a const repository")
        {
            const auto &const_repository{repository};
            for (const auto entity : const_repository)
            {
                REQUIRE_UNARY(repository.hasEntity(entity));
            }
        }

        SUBCASE("ranges")
        {
            for (auto entity : repository)
            {
                repository.addComponent(entity, Position{});
            }

            auto even = [](auto entity) { return 0 == entity % 2; };
            auto position = [&repository](auto entity) { return repository.getComponent<Position>(entity); };

            for (auto [position] : repository | std::views::filter(even) | std::views::transform(position))
            {
                REQUIRE_UNARY(position);
            }
        }
    }
}
