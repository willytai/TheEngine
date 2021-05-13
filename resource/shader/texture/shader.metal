#include <metal_stdlib>
#include <simd/simd.h>

#include "src/backend/MTL/MetalShaderTypes.h"

using namespace metal;

// typedef struct
// {
//     float4x4 u_ProjViewMat;
// } Uniforms;

typedef enum {
    PositionIndex = 0,
    ColorIndex    = 1,
    texCoorIndex  = 2,
    texIDIndex    = 3,
} VertexAttribute;

typedef struct {
    float3 position [[attribute(VertexAttribute::PositionIndex)]];
    float4 color    [[attribute(VertexAttribute::ColorIndex)]];
    float2 texCoor  [[attribute(VertexAttribute::texCoorIndex)]];
    int    texID    [[attribute(VertexAttribute::texIDIndex)]];
} VertexIn;

typedef struct {
    float4 position [[position]];
    float4 color;
    float2 texCoor;
    int    texID;
} VertexOut;

vertex VertexOut vertexMain(VertexIn vIn                [[stage_in]],
                            constant Uniforms& uniforms [[buffer(1)]])
{
    VertexOut vOut;
    vOut.position = uniforms.u_ProjViewMat * float4(vIn.position, 1.0f);
    vOut.color = vIn.color;
    vOut.texCoor = vIn.texCoor;
    vOut.texID = vIn.texID;

    // maybe store samplers object into vOut here?
    return vOut;
}

// only supports texture id 0 for now
fragment float4 fragmentMain(VertexOut vIn [[stage_in]],
                             constant Uniforms& uniforms [[buffer(1)]],
                             texture2d<float, access::sample> texture_0 [[texture(0)]],
                             texture2d<float, access::sample> texture_1 [[texture(1)]])
{
    constexpr sampler nearestSampler(coord::normalized, min_filter::nearest, mag_filter::nearest, mip_filter::none);
    switch (uniforms.u_Samplers[vIn.texID]) {
        case 0: return texture_0.sample(nearestSampler, vIn.texCoor) * vIn.color;
        case 1: return texture_1.sample(nearestSampler, vIn.texCoor) * vIn.color;
        default: return float4(0.0f);
    }
}
