#ifndef __MTL_SHADER_OBJC_H__
#define __MTL_SHADER_OBJC_H__

#import <Metal/Metal.h>

@interface MTLShaderHandle : NSObject
@property (nonatomic, strong) id<MTLLibrary> library;
@property (nonatomic, strong) id<MTLBuffer> uniformBuffer;
- (instancetype)initWithCSourcePath:(const char*)shaderCSrc;
- (id<MTLFunction>)getFunctionWithName:(NSString*)name;
- (void)setUniformFrom:(void*)src Size:(NSUInteger)size Offset:(NSUInteger)offset;
@end

#endif /* __MTL_SHADER_OBJC_H__ */
