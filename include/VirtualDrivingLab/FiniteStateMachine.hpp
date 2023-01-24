#pragma once

#include <functional>
#include <string>

class FiniteStateMachine
{
    using State = std::function<void(float frame_time)>;
    using Condition = std::function<bool(float frame_time)>;

    State m_current_state;
    State m_next_state;

    Condition m_condition;

    virtual void OnEntry(float frame_time) = 0;
    virtual void OnExit(float frame_time) = 0;

  protected:
    void SetNextState(
        State next_state, Condition condition = [](float /*frame_time*/) { return true; });

  public:
    virtual ~FiniteStateMachine() = default;
    FiniteStateMachine();
    FiniteStateMachine(const FiniteStateMachine &) = delete;
    auto operator=(const FiniteStateMachine &) -> FiniteStateMachine & = delete;
    FiniteStateMachine(FiniteStateMachine &&) = delete;
    auto operator=(FiniteStateMachine &&) -> FiniteStateMachine & = delete;

    void Tick(float frame_time);

    void Exit(float frame_time);

    inline auto GetCurrentState()
    {
        return m_current_state;
    }

    inline auto GetNextState()
    {
        return m_next_state;
    }
};

struct State
{
    virtual ~State() = default;

    std::string m_name;
    virtual void operator()(float frame_time) = 0;
};

struct Condition
{
    virtual ~Condition() = default;

    virtual void operator()(float frame_time) = 0;
};
