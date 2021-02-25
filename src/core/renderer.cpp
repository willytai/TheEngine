#include "renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::clear() const {
    GLCall( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
    GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
}

void Renderer::draw(const VertexArray& va, const IndexBufferUI& ib, const Shader& shader) const {
    va.bind();
    ib.bind();
    shader.bind();
    GLCall( glDrawElements( GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr ) );
}
