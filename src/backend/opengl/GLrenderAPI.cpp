#include "backend/OpenGL/GLrenderAPI.h"
#include "backend/OpenGL/GLdataType.h"

#include "core/core.h"
#include "core/renderer/renderer.h"

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

        // check for maximum texture slots;
        int maxTexSlot;
        glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTexSlot );
        CORE_INFO( "\tMax Texture Slots: {}", maxTexSlot );
        Renderer::setMaxTextSlot( maxTexSlot );
    }

    void GLRenderAPI::setViewPort(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) const {
#ifdef __APPLE__
        GLCall( glViewport( (GLint)x, (GLint)y, (GLint)width*2, (GLint)height*2 ) );
#else
        GLCall( glViewport( (GLint)x, (GLint)y, (GLint)width, (GLint)height ) );
#endif
    }

    void GLRenderAPI::setClearColor(const glm::vec4& color) const {
        GLCall( glClearColor( color.r, color.g, color.b, color.a ) );
    }

    void GLRenderAPI::clear() const {
        GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
    }

    void GLRenderAPI::drawElement(const Ref<VertexArray>& vertexArray, const uint32_t& indexCount) const {
        GLCall( glDrawElements( GL_TRIANGLES, indexCount ? (GLsizei)indexCount : vertexArray->getIndexBuffer()->count(),
                                toOpenGLDataType( vertexArray->getIndexBuffer()->type() ), nullptr ) );
    }

}
