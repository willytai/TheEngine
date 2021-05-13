#ifndef __DRAW_UTIL_H__
#define __DRAW_UTIL_H__

#include <glm/glm.hpp>

namespace Engine7414 {
	class DrawUtil {
	public:
		// returns true if any of the values are modified
		static bool drawVec3Control(const char* label, glm::vec3& values, float resetVal = 0.0f, float columnWidth = 90.0f);
	};
}

#endif