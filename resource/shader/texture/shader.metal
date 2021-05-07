#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct Uniforms
{
    float4x4 ProjViewMat;
};

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
} VertexOut;

vertex VertexOut vertexMain(VertexIn vIn                [[stage_in]],
                            constant Uniforms& uniforms [[buffer(1)]])
{
    VertexOut vOut;
    vOut.position = uniforms.ProjViewMat * float4(vIn.position, 1.0f);
    vOut.color = vIn.color;
    vOut.texCoor = vIn.texCoor;

    // maybe store samplers object into vOut here?
    return vOut;
}

// only supports texture id 0 for now
fragment float4 fragmentMain(VertexOut vIn [[stage_in]],
                             texture2d<float, access::sample> texture [[texture(0)]])
{
    constexpr sampler nearestSampler(coord::normalized, min_filter::nearest, mag_filter::nearest, mip_filter::none);
    return texture.sample(nearestSampler, vIn.texCoor) * vIn.color;
}
