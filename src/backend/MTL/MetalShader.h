#ifndef __MTL_SHADER_OBJC_H__
#define __MTL_SHADER_OBJC_H__

#import <Metal/Metal.h>

@interface MTLShaderHandle : NSObject
@property (nonatomic, strong) id<MTLLibrary> library;
- (instancetype)initWithCSourcePath:(nonnull const char*)shaderCSrc;
- (id<MTLFunction>)getFunctionWithName:(NSString*)name;
@end

#endif /* __MTL_SHADER_OBJC_H__ */
