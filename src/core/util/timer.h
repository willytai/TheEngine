#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

namespace Engine7414
{
	class Timer
	{
	public:
		Timer() : start(std::chrono::high_resolution_clock::now()) {}

		float elapsed_ms() const {
			auto now = std::chrono::high_resolution_clock::now();
			return (now - start).count() * 1e-6;
		}

	private:
		std::chrono::high_resolution_clock::time_point start;
	};
}

#endif