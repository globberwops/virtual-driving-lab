
#include "VirtualDrivingLab/FiniteStateMachine.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <memory>

struct OnPrint : public State
{
    OnPrint()
    {
        m_name = typeid(OnPrint).name();
    }

    virtual ~OnPrint() = default;

    void operator()(float frame_time) override
    {
        std::cout << "OnPrint"
                  << " : " << frame_time << '\n';
    }
};

class FiniteStateMachineTest : public FiniteStateMachine
{
    void OnEntry(float frame_time) override
    {

        SetNextState(OnPrint(), [](float frame_time) { return frame_time > 3.0F; });
    }

    // void OnPrint(float frame_time)
    // {

    //     SetNextState(
    //         "Exit", [this](float frame_time) { Exit(frame_time); }, [](float frame_time) { return frame_time > 6.0F;
    //         });
    // }

    void OnExit(float frame_time) override
    {
    }

  public:
    ~FiniteStateMachineTest() override = default;
    FiniteStateMachineTest() = default;
    FiniteStateMachineTest(const FiniteStateMachineTest &) = delete;
    auto operator=(const FiniteStateMachineTest &) -> FiniteStateMachineTest & = delete;
    FiniteStateMachineTest(FiniteStateMachineTest &&) = delete;
    auto operator=(FiniteStateMachineTest &&) -> FiniteStateMachineTest & = delete;
};

TEST(VirtualDrivingLabTest, FiniteStateMachineTest)
{
    std::unique_ptr<FiniteStateMachine> fsm = std::make_unique<FiniteStateMachineTest>();

    for (auto frame_time = 1U; frame_time < 10U; ++frame_time)
    {
        fsm->Tick(static_cast<float>(frame_time));
        std::cout << fsm->GetCurrentState() << ": " << frame_time << '\n';
    }
}
