#ifndef __IMGUI_CLASS_EXTRA__
#define __IMGUI_CLASS_EXTRA__

#include <glm/glm.hpp>

#ifndef IM_VEC2_CLASS_EXTRA
#define IM_VEC2_CLASS_EXTRA                                                 \
        ImVec2(const glm::vec2& f) { x = f.x; y = f.y; }                    \
        operator glm::vec2() const { return glm::vec2(x,y); }
#endif

#ifndef IM_VEC4_CLASS_EXTRA
#define IM_VEC4_CLASS_EXTRA                                                 \
        ImVec4(const glm::vec4& f) { x = f.x; y = f.y; z = f.z; w = f.w; }  \
        operator glm::vec4() const { return glm::vec4(x,y,z,w); }
#endif

#endif