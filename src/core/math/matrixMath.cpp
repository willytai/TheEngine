#include "core/math/matrixMath.h"

namespace Engine7414 {
	namespace math {
		void decomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale) {
			// translation is the last column
			translation = glm::vec3(transform[3]);

			// sacle is the length of the first 3 columns' vector
			scale.x = glm::length(glm::vec3(transform[0]));
			scale.y = glm::length(glm::vec3(transform[1]));
			scale.z = glm::length(glm::vec3(transform[2]));

			// dividing the first 3 columns by the scale gets the rotation matrix
			glm::mat4 ret(0.0f);
			ret[3][3] = 1.0f;
			for (int i = 0; i < 3; ++i) {
				ret[0][i] = transform[0][i] / scale.x;
				ret[1][i] = transform[1][i] / scale.y;
				ret[2][i] = transform[2][i] / scale.z;
			}
			// and then retrieve the euler angles in degree
			// (copied from glm/gtx/matrix_decompose.inl)
			rotation.y = asin(-ret[0][2]);
			if (cos(rotation.y) != 0) {
				rotation.x = atan2(ret[1][2], ret[2][2]);
				rotation.z = atan2(ret[0][1], ret[0][0]);
			} else {
			    rotation.x = atan2(-ret[2][0], ret[1][1]);
			    rotation.z = 0;
			}
			rotation.x = glm::degrees(rotation.x);
			rotation.y = glm::degrees(rotation.y);
			rotation.z = glm::degrees(rotation.z);
		}
	}
}
