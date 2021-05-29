#ifndef __MATRIX_MATH_H__
#define __MATRIX_MATH_H__

#include <glm/glm.hpp>

namespace Engine7414 {
	namespace math {
		void decomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}
}

#endif
