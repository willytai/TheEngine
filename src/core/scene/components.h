#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine7414
{
    struct TagComponent
    {
        const char* tag;
    };

    struct TransformComponent
    {
        glm::vec3  translation = {0.0f, 0.0f, 0.0f};
        glm::vec3  scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 transform() const {
            return glm::translate( glm::mat4(1.0f), translation ) *
                   // glm::rotate( glm::mat4(1.0f), ... ) *
                   glm::scale( glm::mat4(1.0f), scale );
        }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    };
}

#endif /* __COMPONENTS_H__ */
