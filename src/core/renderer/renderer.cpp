#include "core/renderer/renderer.h"
#include "core/renderer/rendererData.h"
#include "core/renderer/rendererData2D.h"
#include "core/renderer/renderer2D.h"

#include <glm/gtc/type_ptr.hpp>

namespace Engine7414
{
    static RendererData* __data;

    std::vector<UniformHandle> Renderer::_globalUniformHandle;

    Renderer::sceneData Renderer::__data__;
    bool Renderer::__updateProjViewMat__ = true;

    void Renderer::setUpdateMatFlag() {
        __updateProjViewMat__ = true;
    }

    void Renderer::setMaxTextSlot(const int& maxSlot) {
        RendererData2D::setMaxTextSlot(maxSlot);
    }

    void Renderer::init(RendererBackend backend) {
        CORE_INFO("Renderer Info");
        RenderCommands::init(backend);

        // initialize renderer data
        __data = new RendererData;

        // load shader
#ifdef _WIN64
        __data->phongShader = ShaderLibrary::get().load("C:\\Users\\Willy\\Desktop\\TheEngine\\TheEngine\\resource\\shader\\phong");
#else
        __data->phongShader = ShaderLibrary::get().load("./resource/shader/phong");
#endif

        // global uniform
        Renderer::registerGlobalUniform();

        // initializing this here just for convenience
        // Renderer2D::init();
    }

    void Renderer::shutdown() {
        Renderer2D::shutdown();
        delete __data;
    }

    void Renderer::beginScene(Scene* scene, Ref<EditorCamera>& camera, const Ref<FrameBuffer>& currentFrameBuffer) {
        currentFrameBuffer->bind();
        currentFrameBuffer->clear();
        __data->reset();

        // link the data
        // NOTE: the data has to stay fixed, otherwise this breaks
        //       getPostion() doesn't check, don't change the order of retrieving these values
        _globalUniformHandle[G_UNIFORM_PROJ_VIEW_MAT].data = glm::value_ptr(camera->getViewProjection());
        _globalUniformHandle[G_UNIFORM_CAMERA_POS].data = glm::value_ptr(camera->getPosition());

        _globalUniformHandle[G_UNIFORM_SCENE_AMBIENT].data = &scene->_ambientStrength;
        _globalUniformHandle[G_UNIFORM_DIR_LIGHT_SPECULAR].data = &scene->_specularStrength;
        _globalUniformHandle[G_UNIFORM_DIR_LIGHT_SHININESS].data = &scene->_shininess;

        auto directionalLightEntity = scene->getDirectionalLightEntity();
        if (directionalLightEntity) {
            auto comp = directionalLightEntity.get<DirectionalLightComponent>();
            _globalUniformHandle[G_UNIFORM_DIR_LIGHT_DIR].data = glm::value_ptr(comp.lightDirection);
            _globalUniformHandle[G_UNIFORM_DIR_LIGHT_COLOR].data = glm::value_ptr(comp.lightColor);
        }

        // upload to GPU
        ShaderLibrary::uploadGlobalUniforms(_globalUniformHandle);
    }

    void Renderer::endScene() {
        if (__data->totalIndexCount) Renderer::flush();
    }

    void Renderer::flush() {
        // bind shader
        __data->phongShader->bind();
        // upload data
        __data->vertexBuffer->setData(__data->vertexData,
            (size_t)(__data->vertexDataPtr - __data->vertexData) * sizeof(Vertex3D));
        // draw
        __data->vertexArray->bind();
        RenderCommands::drawElement(__data->vertexArray, __data->totalIndexCount);
        // stats
        __data->stats.drawCalls++;
    }

    void Renderer::drawCube(const glm::mat4& transform, const glm::vec4& color, int enttID) {
        for (const auto& [position, normal] : __data->unitCubeVerticesWithNormals) {
            __data->vertexDataPtr->color = color;
            __data->vertexDataPtr->position = transform * glm::vec4(position, 1.0f);
            __data->vertexDataPtr->normal = glm::mat3(glm::transpose(glm::inverse(transform))) * normal;
            __data->vertexDataPtr->entityID = enttID;
            __data->vertexDataPtr++;
        }

        __data->totalIndexCount += 36;
        __data->stats.vertices += 24;
    }

    void Renderer::drawCube(const glm::mat4& transform, const glm::vec4& color) {

    }

    // just a template for quering the member size/offset for global uniforms
    struct CameraUniform
    {
        glm::mat4 ProjViewMat;
        glm::vec3 ViewPos;

    private:
        CameraUniform();
    };

    // this padding stuff is fucked up
    struct DirectionalLightUniform
    {
        glm::vec3 Direction;
        float padding0;
        glm::vec3 Color;


    private:
        DirectionalLightUniform();
    };

    struct SceneUniform
    {
        float AmbientStrength;
        float SpecularStrength;
        int   Shininess;

    private:
        SceneUniform();
    };

    #define GenerateHandle(uniform, bindingPoint, uOffset, uSize, uName) \
        if (_globalUniformHandle.size() < uniform + 1) { \
            _globalUniformHandle.resize(uniform + 1); \
        } \
        { \
            auto& handle = _globalUniformHandle[uniform]; \
            handle.name = uName; \
            handle.bindingIndex = bindingPoint; \
            handle.offset = uOffset; \
            handle.size = uSize; \
            CORE_INFO("offset of {} is {}", uName, uOffset); \
        }

    void Renderer::registerGlobalUniform() {
        // the view projection matrix, binding point: 0, uniform block: Camera
        GenerateHandle(G_UNIFORM_PROJ_VIEW_MAT, 0, offsetof(CameraUniform, ProjViewMat), sizeof(CameraUniform::ProjViewMat), "Camera::ProjViewMat");
        GenerateHandle(G_UNIFORM_CAMERA_POS,    0, offsetof(CameraUniform, ViewPos), sizeof(CameraUniform::ViewPos), "Camera::ViewPos");
        
        GenerateHandle(G_UNIFORM_DIR_LIGHT_DIR,       1, offsetof(DirectionalLightUniform, Direction), sizeof(DirectionalLightUniform::Direction), "DirLight::Direction");
        GenerateHandle(G_UNIFORM_DIR_LIGHT_COLOR,     1, offsetof(DirectionalLightUniform, Color),     sizeof(DirectionalLightUniform::Color),     "DirLight::Color");
        GenerateHandle(G_UNIFORM_SCENE_AMBIENT,       2, offsetof(SceneUniform, AmbientStrength),      sizeof(SceneUniform::AmbientStrength),      "Scene::Ambient");
        GenerateHandle(G_UNIFORM_DIR_LIGHT_SPECULAR,  2, offsetof(SceneUniform, SpecularStrength),     sizeof(SceneUniform::SpecularStrength),     "Scene::SpecularStrength");
        GenerateHandle(G_UNIFORM_DIR_LIGHT_SHININESS, 2, offsetof(SceneUniform, Shininess),            sizeof(SceneUniform::Shininess),            "Scene::Shininess");

        // register and submit
        for (auto& handle : _globalUniformHandle)
            ShaderLibrary::registerGlobalUniform(handle);
        ShaderLibrary::submitGlobalUniforms();
    }

    RendererData::statistics Renderer::stat() {
        return __data->stats;
    }
}
