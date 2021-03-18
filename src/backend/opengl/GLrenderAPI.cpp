#include "backend/OpenGL/GLrenderAPI.h"
#include "backend/OpenGL/GLdataType.h"

#include "core/core.h"

namespace Engine7414
{

    void GLRenderAPI::setClearColor(const glm::vec4& color) const {
        GLCall( glClearColor( color.r, color.g, color.b, color.a ) );
    }

    void GLRenderAPI::clear() const {
        GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
    }

    void GLRenderAPI::drawElement(const Ref<VertexArray>& vertexArray) const {
        GLCall( glDrawElements( GL_TRIANGLES, vertexArray->getIndexBuffer()->count(),
                                toOpenGLDataType( vertexArray->getIndexBuffer()->type() ), nullptr ) );
    }

}
