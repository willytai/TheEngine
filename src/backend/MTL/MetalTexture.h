#ifndef __MTL_TEXTURE_OBJC_H__
#define __MTL_TEXTURE_OBJC_H__

#import <Metal/Metal.h>

@interface MTLTextureHandle : NSObject
@property (nonatomic, strong) id<MTLTexture> texture;
- (instancetype)initWithData:(void*)data Width:(NSUInteger)width Height:(NSUInteger)height Bpp:(NSInteger)bpp;
- (void)bindToSlot:(NSUInteger)slot;
@end

#endif /* __MTL_TEXTURE_OBJC_H__ */
