#ifndef __METAL_SHADER_TYPES_H__
#define __METAL_SHADER_TYPES_H__

#include <simd/simd.h>

// make sure these uniforms are registered inside MTLShader as strings!
typedef struct {
    simd::float4x4 u_ProjViewMat;
    int            u_Samplers[32];
} Uniforms;

#endif /* __METAL_SHADER_TYPES_H__ */
