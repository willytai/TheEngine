#import "backend/MTL/MetalTexture.h"
#import "backend/MTL/MTLcontext.h"

using namespace Engine7414;

@implementation MTLTextureHandle
- (instancetype)initWithData:(void*)data Width:(NSUInteger)width Height:(NSUInteger)height Bpp:(NSInteger)bpp{
    if ( (self = [super init]) ) {
        MTLTextureDescriptor* td = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                                                                      width:width
                                                                                     height:height
                                                                                  mipmapped:NO];
        self.texture = [MTLContext::getContext().nativeDevice newTextureWithDescriptor:td];
        MTLRegion region = {
            { 0, 0, 0 },
            { width, height, 1 }
        };
        [self.texture replaceRegion:region
                        mipmapLevel:0
                          withBytes:data
                        bytesPerRow:bpp*width];
    }
    return self;
}
@end
