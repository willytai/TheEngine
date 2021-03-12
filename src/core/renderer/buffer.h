#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>
#include <vector>
#include "core/core.h"

namespace Engine7414
{
    enum class BufferDataType : uint8_t
    {
        // vertices data type
        UNDEF, Float, Int,

        // index buffer type
        uInt8, uInt32
    };

    /***************************************************
    *                  Buffer Element                  *
    ***************************************************/
    // at most 4 components per element,
    // using uint16_t for 'count' for memory optimization
    struct BufferElement
    {
        BufferDataType  dtype;
        bool            normalized;
        uint16_t        count;
        uint32_t        offset;

        BufferElement(const BufferDataType& bdtype, const uint16_t& bcount, bool bnorm = false, uint32_t boffset = 0)
            : dtype(bdtype), normalized(bnorm), count(bcount), offset(boffset) {}

        uint32_t typeSize() const {
            switch (dtype) {
                case BufferDataType::Float: return 4;
                case BufferDataType::Int:   return 4;
                case BufferDataType::uInt8: return 1;
                default: CORE_ASSERT( false, "Unsupported data type for vertex buffer: {}", dtype ); return 0;
            }
        }
    };
    // -------------------------------------------------

    /***************************************************
    *                   Buffer Layout                  *
    ***************************************************/
    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : _elements(elements), _stride(0) {
            for (auto& element : _elements) {
                element.offset = _stride;
                _stride += (uint32_t)element.count * element.typeSize();
            }
        }
        ~BufferLayout() {}

        inline const std::vector<BufferElement>& elements() const { return _elements; }
        inline uint32_t stride() const { return _stride; }

    private:
        std::vector<BufferElement>  _elements;
        uint32_t                    _stride;
    };
    // -------------------------------------------------

    /***************************************************
    *                  Vertex Buffer                  *
    ***************************************************/
    class VertexBuffer
    {
    public:
        VertexBuffer() {}
        virtual ~VertexBuffer() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        inline void setLayout(const BufferLayout& layout) { _layout = layout; }
        inline const BufferLayout& layout() const { return _layout; }

        static VertexBuffer* create(const void* vertices, size_t size);

    private:
        BufferLayout    _layout;
    };
    // -------------------------------------------------

    /***************************************************
    *                Index Buffer Base                *
    ***************************************************/
    class IndexBuffer
    {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual BufferDataType type() const = 0;
        inline int count() const { return (int)_count; }
    protected:
        uint32_t _count;
    };
    // -------------------------------------------------

    /***************************************************
    *             Index Buffer with Type               *
    ***************************************************/
    #define IndexBufferBaseClass(ClassName, Type, TypeEnum) \
    class ClassName : public IndexBuffer \
    { \
    public: \
        virtual void bind() const override = 0; \
        virtual void unbind() const override = 0; \
        BufferDataType type() const override { return TypeEnum; } \
        static ClassName* create(const Type* indices, uint32_t count); \
    }

    IndexBufferBaseClass( IndexBufferUI8,  uint8_t, BufferDataType::uInt8 );
    IndexBufferBaseClass( IndexBufferUI32, uint32_t, BufferDataType::uInt32 );
}

#endif /* __BUFFER_H__ */