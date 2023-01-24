#include <concepts>
#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

#include <Eigen/Core>

using Coordinate3 = Eigen::Vector3f;
using Rotation3 = Eigen::Matrix3f;
using Vector3 = Eigen::Vector3f;

template <typename T>
concept HasPosition = std::is_same_v<decltype(T::position), Coordinate3>;

template <typename T>
concept HasOrientation = std::is_same_v<decltype(T::orientation), Rotation3>;

struct StaticObject
{
    Coordinate3 position{};
    Rotation3 orientation{};
    float radius{};
};

struct Cuboid
{
    Coordinate3 position{};
    Rotation3 orientation{};
    float length{};
    float width{};
    float height{};
};

struct Line
{
    Coordinate3 position{};
    Rotation3 orientation{};
    float length{};
};

struct Translate
{
    Vector3 delta{};

    void operator()(HasPosition auto &value)
    {
        value.position += delta;
    }
};

struct Rotate
{
    Rotation3 delta{};

    void operator()(HasOrientation auto &value)
    {
        value.position += delta;
    }
};

template <HasPosition... Ts>
class Shapes
{
    std::tuple<std::vector<Ts>...> data{};

  public:
    template <typename T>
    auto push_back(T value)
    {
        return std::get<std::vector<T>>(data).push_back(value);
    }

    template <typename T>
    auto begin()
    {
        return std::get<std::vector<T>>(data).begin();
    }

    template <typename T>
    auto end()
    {
        return std::get<std::vector<T>>(data).end();
    }
};

auto main() -> int
{
    auto shapes = Shapes<StaticObject, Cuboid, Line>{};
    shapes.push_back(StaticObject{.position = {0.F, 0.F, 0.F}, .orientation = {}, .radius = 2.F});
    shapes.push_back(
        Cuboid{.position = {1.F, 1.F, 1.F}, .orientation = {}, .length = 2.F, .width = 2.F, .height = 2.F});
    shapes.push_back(Line{.position = {2.F, 2.F, 2.F}, .orientation = {}, .length = 2.F});

    for (auto it = shapes.begin<StaticObject>(); it != shapes.end<StaticObject>(); ++it)
    {
        std::visit([](HasPosition auto &value) { std::cout << value.position << '\n' << '\n'; }, *it);
        std::visit(Translate{.delta = {-1.F, 0.F, 1.F}}, *it);
        std::visit([](HasPosition auto &value) { std::cout << value.position << '\n' << '\n'; }, *it);
    }

    return 0;
}
