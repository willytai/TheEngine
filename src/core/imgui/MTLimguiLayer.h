#ifndef __MTL_IMGUI_LAYER_H__
#define __MTL_IMGUI_LAYER_H__

#import <Metal/Metal.h>
#import "backend/MTL/MTLcontext.h"

#include "core/imgui/imguiLayer.h"

@interface MTLImGuiData : NSObject
@property (nonatomic, strong) MTLRenderPassDescriptor* renderPassDescriptor;
@property (nonatomic, strong) id<MTLCommandBuffer> commandBuffer;
@property (nonatomic, strong) id<MTLRenderCommandEncoder> commandEncoder;
@property (nonatomic, strong) id<CAMetalDrawable> drawable;
- (instancetype)initWithContext:(GlobalContext*)context;
- (void)newFrame:(GlobalContext*)context;
- (void)presentDrawable;
- (void)commit;
@end

namespace Engine7414
{
    class MTLImGuiLayer : public ImGuiLayer
    {
    public:
        MTLImGuiLayer();
        ~MTLImGuiLayer();

        void begin() override;
        void end() override;
        void onAttach() override;
        void onDetach() override;

    private:
        MTLImGuiData* _data;
    };
}

#endif /* ifndef __MTL_IMGUI_LAYER_H__ */
