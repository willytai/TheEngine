#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

#include "core/core.h"

namespace Engine7414
{
    enum class FrameBufferTextureFormat
    {
        UNDEF = 0,

        // color
        RGBA8,
        RED_INT,

        // depth/stencil
        DEPTH24STENCIL8,

        // default
        Depth = DEPTH24STENCIL8
    };

    enum class FrameBufferTextureClearAction
    {
        CLEAR_AS_COLOR,
        CLEAR_AS_FLOAT,
        CLEAR_AS_INT,
        DONT_CARE
    };

    union FrameBufferTextureClearData
    {
        FrameBufferTextureClearData(int i) : int1(i) {}
        FrameBufferTextureClearData(float f) : float1(f) {}
        FrameBufferTextureClearData(float f, int i) : fi({ f, i }) {}
        FrameBufferTextureClearData(float f1, float f2, float f3, float f4) : color4({ f1, f2, f3, f4 }) {}
        
        struct { float r; float g; float b; float a; } color4;
        struct { float f; int i; }                     fi;
        int                                            int1;
        float                                          float1;
    };

    struct FrameBufferTextureDiscriptor
    {
        FrameBufferTextureDiscriptor() = default;
        FrameBufferTextureDiscriptor(FrameBufferTextureFormat texFormat) : format(texFormat) {}
        FrameBufferTextureDiscriptor(FrameBufferTextureFormat texFormat,
                                     FrameBufferTextureClearAction texClearAction,
                                     FrameBufferTextureClearData texClearData) : 
            format(texFormat),
            clearAction(texClearAction),
            clearData(texClearData) {}

        FrameBufferTextureFormat format = FrameBufferTextureFormat::UNDEF;
        FrameBufferTextureClearAction clearAction = FrameBufferTextureClearAction::CLEAR_AS_COLOR;
        FrameBufferTextureClearData clearData = { 0.0f, 0.0f, 0.0f, 1.0f };

        // TODO: filter/warp
    };

    struct FrameBufferAttachmentDiscriptor
    {
        FrameBufferAttachmentDiscriptor() = default;
        FrameBufferAttachmentDiscriptor(const std::initializer_list<FrameBufferTextureDiscriptor>& txtDiscriptor) : attachments(txtDiscriptor) {}
    
        std::vector<FrameBufferTextureDiscriptor> attachments;
    };

    struct FrameBufferSpec
    {
        // initial values don't actually matter since framebuffer should be resized whenever resize events are triggered
        uint32_t width = 1280;
        uint32_t height = 960;

        uint32_t sample = 1;
        FrameBufferAttachmentDiscriptor attachments;
    };

    class FrameBuffer
    {
    public:
        FrameBuffer(const FrameBufferSpec& spec);
        virtual ~FrameBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void resize(const uint32_t& width, const uint32_t& height) = 0;
        virtual uint32_t colorAttachmentID(int index = 0) const = 0;
        virtual const FrameBufferSpec& spec() const = 0;
        virtual void readPixel(int x, int y, void* data, int index = 0) const = 0;

        // TODO this should be called only by renderer*
        virtual void clear() const = 0;

        static Ref<FrameBuffer> create(const FrameBufferSpec& spec);
        static bool isDepthFormat(const FrameBufferTextureFormat& format);

    protected:
        FrameBufferSpec _spec;
        
        std::vector<FrameBufferTextureDiscriptor>   _colorAttachmentDescs;
        FrameBufferTextureDiscriptor                _depthAttachmentDesc = FrameBufferTextureFormat::UNDEF;
    };
}

#endif /* __FRAME_BUFFER_H__ */
