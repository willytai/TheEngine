#include "core/renderer/rendererData.h"

namespace Engine7414
{
	RendererData2D::RendererData2D() {
		vertexData = new Vertex2D[maxVertexCount];
		vertexDataPtr = vertexData;
		curIndexCount = 0;
	}

	RendererData2D::~RendererData2D() {
		delete[] vertexData;
	}

	void RendererData2D::reset() {
		vertexDataPtr = vertexData;
		curIndexCount = 0;
	}
}