#include "backend/OpenGL/GLrenderAPI.h"
#include "backend/OpenGL/GLdataType.h"

#include "core/core.h"

namespace Engine7414
{
    void GLRenderAPI::init() const {
        // z-buffer
        glEnable( GL_DEPTH_TEST );
        CORE_INFO( "\tz-buffer: Enabled (default)" );

        // blending
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        CORE_INFO( "\tblending: Enabled (default)" );
    }

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
