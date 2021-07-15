#include "backend/MTL/MTLshader.h"
#include "backend/MTL/MetalShaderTypes.h"
#include <filesystem>

#import "backend/MTL/MTLrenderAPI.h"

namespace Engine7414
{
    MTLShader::MTLShader(const std::string& name, const char* shaderDir) :
        Shader(name),
        _handle(nil)
    {
        std::string shaderPath;
        for (const auto& file : std::filesystem::directory_iterator( shaderDir ) ) {
            if ( file.is_directory() ) continue;
            auto path = file.path().string();
            if ( file.path().extension() == ".metal" ) {
                shaderPath.swap( path );
            }
            else CORE_WARN( "got unrecognized file \'{}\' while loading shader", path );
        }

        CORE_INFO("readinng from shader path: {}", shaderPath.c_str());
        _handle = [[MTLShaderHandle alloc] initWithCSourcePath:shaderPath.c_str()];

        this->genUniformPosMap();
    }

    MTLShader::~MTLShader() {
    }

    void MTLShader::setVec4f(const char* name, const glm::vec4& value) {
        CORE_ASSERT( false, "" );
    }

    void MTLShader::setMat4f(const char* name, const glm::mat4& value) {
        size_t size = sizeof(float)*4*4;
        size_t offset = this->getUniformPos(name);
        [_handle setUniformFrom:(void*)&value[0] Size:size Offset:offset];
    }

    void MTLShader::setInt1(const char* name, const int& value) {
        size_t size = sizeof(int);
        size_t offset = this->getUniformPos(name);
        [_handle setUniformFrom:(void*)&value Size:size Offset:offset];
    }

    void MTLShader::setIntArray(const char* name, const int* values, const int& count) {
        size_t size = sizeof(int)*(size_t)count;
        size_t offset = this->getUniformPos(name);
        [_handle setUniformFrom:(void*)values Size:size Offset:offset];

        // for (int i = 0; i < count; ++i) {
        //     CORE_INFO( "check {}", *((int*)((char*)_handle.uniformBuffer.contents+offset)+i) );
        // }
        // CORE_ASSERT( false, "" );
    }

    void MTLShader::bind() const {
        auto* vFunc = [_handle getFunctionWithName:@"vertexMain"];
        auto* fFunc = [_handle getFunctionWithName:@"fragmentMain"];
        auto* renderHandle = MTLRenderAPI::getRenderHandle();
        renderHandle.rpsCacheKey.vertexFunc = vFunc;
        renderHandle.rpsCacheKey.fragmentFunc = fFunc;
        [renderHandle bindUniformBuffer:_handle.uniformBuffer];
        // CORE_ASSERT( false, "need to also bind the uniform buffer to the render encoder (needs an index)"
        //                     ", if this is statically bounded, cache it inside renderAPI!");
    }

    void MTLShader::unbind() const {
        CORE_ASSERT( false, "" );
    }

    void MTLShader::genUniformPosMap() {
        _uniformPosMap.clear();
        _uniformPosMap[std::string("u_ProjViewMat")] = offsetof(Uniforms, u_ProjViewMat);
        _uniformPosMap[std::string("u_Samplers")] = offsetof(Uniforms, u_Samplers);
    }

    size_t MTLShader::getUniformPos(const char* name) const {
        CORE_ASSERT( _uniformPosMap.find(std::string(name)) != _uniformPosMap.end(), "" );
        return _uniformPosMap.find(std::string(name))->second;
    }
}
