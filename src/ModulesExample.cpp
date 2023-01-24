#include <iostream>
#include <source_location>
#include <variant>
#include <vector>

struct ModuleA
{
    void Init()
    {
        std::cout << std::source_location::current().function_name() << '\n';
    };

    void Tick(float alpha)
    {
        std::cout << std::source_location::current().function_name() << ": " << alpha << '\n';
    };

    void Exit()
    {
        std::cout << std::source_location::current().function_name() << '\n';
    };
};

struct ModuleB
{
    void Init()
    {
        std::cout << std::source_location::current().function_name() << '\n';
    };

    void Tick(float alpha)
    {
        std::cout << std::source_location::current().function_name() << ": " << alpha << '\n';
    };

    void Exit()
    {
        std::cout << std::source_location::current().function_name() << '\n';
    };
};

struct ModuleC
{
    void Init()
    {
        std::cout << std::source_location::current().function_name() << '\n';
    };

    void Tick(float alpha)
    {
        std::cout << std::source_location::current().function_name() << ": " << alpha << '\n';
    };

    // void Exit()
    // {
    //     std::cout << std::source_location::current().function_name() << '\n';
    // };
};

// requires expressions
template <typename T>
concept HasInit = requires(T value) { value.Init(); };

template <typename T>
concept HasTick = requires(T value) { value.Tick(0.F); };

template <typename T>
concept HasExit = requires(T value) { value.Exit(); };

template <typename T>
concept IsModule = HasInit<T> && HasTick<T> && HasExit<T>;

template <typename... Args>
concept IsModules = (IsModule<Args> && ...);

using modules_t = std::vector<std::variant<ModuleA, ModuleB, ModuleC>>;

void InitAllModules(modules_t &modules)
{
    for (auto &module : modules)
    {
        std::visit([](IsModule auto &module) { module.Init(); }, module);
    }
}

void TickAllModules(modules_t &modules, float alpha)
{
    for (auto &module : modules)
    {
        std::visit([alpha](IsModule auto &module) { module.Tick(alpha); }, module);
    }
}

void ExitAllModules(modules_t &modules)
{
    for (auto &module : modules)
    {
        std::visit([](IsModule auto &module) { module.Exit(); }, module);
    }
}

auto main() -> int
{

    auto modules = modules_t{};
    modules.emplace_back(ModuleA{});
    modules.emplace_back(ModuleB{});
    modules.emplace_back(ModuleC{});

    InitAllModules(modules);

    for (int alpha = 0; alpha < 3; ++alpha)
    {
        TickAllModules(modules, static_cast<float>(alpha));
    }

    ExitAllModules(modules);

    return 0;
}
