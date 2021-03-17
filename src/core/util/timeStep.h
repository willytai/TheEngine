#ifndef __TIME_STEP_H__
#define __TIME_STEP_H__

#include <chrono>

namespace Engine7414
{
    class TimeStep
    {
    public:
        TimeStep(const std::chrono::high_resolution_clock::duration& step) : _timeStep(step) {}

        operator float() const { return this->seconds(); }

        float seconds() const { return (float)_timeStep.count() * 1e-9f; }
        float milliseconds() const { return (float)_timeStep.count() * 1e-6f; }
    private:
        std::chrono::high_resolution_clock::duration    _timeStep;
    };
}

#endif /* __TIME_STEP_H__ */
