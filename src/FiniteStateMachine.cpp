#include <utility>

#include "VirtualDrivingLab/FiniteStateMachine.hpp"

FiniteStateMachine::FiniteStateMachine()
{
    SetNextState([this](float frame_time) { OnEntry(frame_time); });
}

void FiniteStateMachine::SetNextState(State next_state, Condition condition)
{
    m_next_state = std::move(next_state);
    m_condition = std::move(condition);
}

void FiniteStateMachine::Tick(float frame_time)
{
    if (m_condition)
    {
        if (m_condition(frame_time))
        {
            m_condition = nullptr;
            m_current_state = m_next_state;
            if (m_current_state)
            {
                m_current_state(frame_time);
            }
        }
    }
    else
    {
        if (m_current_state)
        {
            m_current_state(frame_time);
        }
    }
}

void FiniteStateMachine::Exit(float frame_time)
{
    m_current_state = nullptr;
    m_next_state = nullptr;

    m_condition = nullptr;

    OnExit(frame_time);
}
