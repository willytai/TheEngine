#include "core/renderer/renderer2D.h"
#include "core/renderer/renderCommands.h"

namespace Engine7414
{
	static struct Renderer2D_Data  {
		Ref<Shader>	flatColorShader;
        Ref<Shader>	textureShader;
		Ref<VertexArray> quadVertexArray;
	} *__data;

	void Renderer2D::init() {
		__data = new Renderer2D_Data;

        float plainSquare[] = {
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        };
        uint8_t indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        auto vertexBuffer = Engine7414::VertexBuffer::create(plainSquare, 5 * 4 * sizeof(float));
        vertexBuffer->setLayout({
            { Engine7414::BufferDataType::Float, 3 },
            { Engine7414::BufferDataType::Float, 2 }
            });
        __data->quadVertexArray = Engine7414::VertexArray::create();
        __data->quadVertexArray->addVertexBuffer(vertexBuffer);
        auto indexBuffer = Engine7414::IndexBufferUI8::create(indices, 6);
        __data->quadVertexArray->setIndexBuffer(indexBuffer);
        __data->quadVertexArray->setModelMat(glm::mat4(1.0f));

        __data->flatColorShader = ShaderDict::get().load("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\shader\\flatColor");
        __data->textureShader = ShaderDict::get().load("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\shader\\texture");
        __data->textureShader->bind();
        __data->textureShader->setInt1("u_textureID", 0);
	}

	void Renderer2D::shutdown() {
		delete __data;
	}

	void Renderer2D::beginScene(const Ref<CameraBase>& camera, const glm::vec4& color) {
        RenderCommands::clear(color);

        __data->flatColorShader->bind();
        __data->flatColorShader->setMat4f("u_ProjViewMat", camera->projXview());

        __data->textureShader->bind();
        __data->textureShader->setMat4f("u_ProjViewMat", camera->projXview());
    }

	void Renderer2D::endScene() {
    
    }

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		 Renderer2D::drawQuad({position.x, position.y, 0.0f}, size, color);
	}

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
        Renderer2D::drawQuad({ position.x, position.y, 0.0f }, size, texture);
    }

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        __data->flatColorShader->bind();
        __data->flatColorShader->setVec4f("u_Color", color);

        auto transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        __data->flatColorShader->setMat4f("u_ModelMat", transform);

        __data->quadVertexArray->bind();
        RenderCommands::drawElement(__data->quadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
        texture->bind(0);
        __data->textureShader->bind();

        auto transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        __data->textureShader->setMat4f("u_ModelMat", transform);

        __data->quadVertexArray->bind();
        RenderCommands::drawElement(__data->quadVertexArray);
    }
}