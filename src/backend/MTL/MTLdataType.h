#ifndef __MTL_DATA_TYPE_OBJC_H__
#define __MTL_DATA_TYPE_OBJC_H__

#include "backend/backend.h"
#include "core/renderer/buffer.h"

#import <Metal/Metal.h>

#include <iostream>

namespace Engine7414
{
#define GEN_FUNC(DATATYPE) \
    static MTLVertexFormat MTL ##DATATYPE ## TypeWithCount(uint32_t count) { \
        switch (count) { \
            case 1: return MTLVertexFormat ##DATATYPE; \
            case 2: return MTLVertexFormat ##DATATYPE ## 2; \
            case 3: return MTLVertexFormat ##DATATYPE ## 3; \
            case 4: return MTLVertexFormat ##DATATYPE ## 4; \
            default: BACKEND_ASSERT( count <= 4, "element with repeat count of {} with {} type not supported", count, #DATATYPE ); \
        } \
        return MTLVertexFormatInvalid; \
    }

    GEN_FUNC( Float );
    GEN_FUNC( Int );
    GEN_FUNC( UChar );
    GEN_FUNC( UInt );

    static MTLVertexFormat toMetalDataType(const BufferElement& element) {
        switch (element.dtype) {
            case BufferDataType::Float:  return MTLFloatTypeWithCount((uint32_t)element.count);
            case BufferDataType::Int:    return MTLIntTypeWithCount((uint32_t)element.count);
            case BufferDataType::uInt8:  return MTLUCharTypeWithCount((uint32_t)element.count);
            case BufferDataType::uInt32: return MTLUIntTypeWithCount((uint32_t)element.count);
            default: BACKEND_ASSERT( false, "Unsupported data type for Metal: {}", element.dtype );
        }
        return MTLVertexFormatInvalid;
    }

    static MTLIndexType toMetalIndexType(const BufferDataType& dtype) {
        switch (dtype) {
            case BufferDataType::uInt32: return MTLIndexTypeUInt32;
            default: BACKEND_ASSERT( false, "Unsupported index type for Metal: {}", dtype );
        }
    }
}

#endif /* ifndef __MTL_DATA_TYPE_OBJC_H__ */
