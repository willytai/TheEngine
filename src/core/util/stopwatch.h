#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__

#include "core/util/timeStep.h"

namespace Engine7414
{
    // 8 bytes
    class StopWatch
    {
    public:
        StopWatch() {}

        void reset() {
            _lastTimePoint = std::chrono::high_resolution_clock::now();
        }

        TimeStep deltaTime() {
            auto now = std::chrono::high_resolution_clock::now();
            auto deltaTime = now - _lastTimePoint;
            _lastTimePoint = now;
            return deltaTime;
        }

    private:
        std::chrono::high_resolution_clock::time_point  _lastTimePoint;
    };
}

#endif /* __STOP_WATCH_H__ */
