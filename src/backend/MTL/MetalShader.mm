#import "backend/MTL/MetalShader.h"
#import "backend/MTL/MTLcontext.h"

#include "backend/MTL/MetalShaderTypes.h"
#include "core/renderer/shader.h"

using namespace Engine7414;

@implementation MTLShaderHandle
- (instancetype)initWithCSourcePath:(nonnull const char*)shaderCSrc {
    if ( (self = [super init]) ) {
        NSURL* shaderPath = [[NSBundle mainBundle] URLForResource:[NSString stringWithUTF8String:shaderCSrc]
                                                   withExtension:nil ];
        NSString* shaderSource = [[NSString alloc] initWithContentsOfURL:shaderPath
                                                   encoding:NSUTF8StringEncoding error:nil];
        auto* context = MTLContext::getContext();
        NSError* error;
        self.library = [context.nativeDevice newLibraryWithSource:shaderSource options:nil error:&error];
        if (self.library == nil) {
            NSLog(@"Error: failed to create Metal library: %@", error);
        }
        else {
            NSString* name;
            for (name in self.library.functionNames) {
                NSLog(@"function %@ created", name);
            }
        }

        // the buffer for the uniforms
        self.uniformBuffer = [context.nativeDevice newBufferWithLength:sizeof(Uniforms)
                                                               options:MTLCPUCacheModeWriteCombined];
    }
    return self;
}

- (id<MTLFunction>)getFunctionWithName:(NSString*)name {
    return [_library newFunctionWithName:name];
}

- (void)setUniformFrom:(void*)src Size:(NSUInteger)size Offset:(NSUInteger)offset {
    memcpy( (char*)self.uniformBuffer.contents+offset, src, size );
}

@end
