#include "core/util/font.h"
#include "core/imgui/MTLimguiLayer.h"
#include "core/application/app.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"

#import "imgui/backends/imgui_impl_metal.h"

@implementation MTLImGuiData
- (instancetype)initWithContext:(GlobalContext*)context {
    if ( (self = [super init]) ) {
        self.renderPassDescriptor = [MTLRenderPassDescriptor new];
        self.renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.45f, 0.55f, 0.60f, 0.0f);
        self.renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        // self.renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    }
    return self;
}
- (void)newFrame:(GlobalContext*)context {
    // new drawable
    int width, height;
    glfwGetFramebufferSize( (GLFWwindow*)Engine7414::App::getWindow()->nativeWindow(), &width, &height );
    context.swapChain.drawableSize = CGSizeMake( width, height );
    _drawable = [context.swapChain nextDrawable];

    // set to renderPassDescriptor
    _renderPassDescriptor.colorAttachments[0].texture = _drawable.texture;

    // new buffer and encoder
    _commandBuffer = [context.commandQueue commandBuffer];
    _commandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor:_renderPassDescriptor];
}
- (void)endEncoding {
    [_commandEncoder endEncoding];
}
- (void)presentDrawable {
    [_commandBuffer presentDrawable:_drawable];
}
- (void)commit {
    [_commandBuffer commit];
}
@end

namespace Engine7414
{
    MTLImGuiLayer::MTLImGuiLayer() {
        _data = nil;
    }

    MTLImGuiLayer::~MTLImGuiLayer() {

    }

    void MTLImGuiLayer::begin() {
        [_data newFrame:MTLContext::getContext()];
        ImGui_ImplMetal_NewFrame( _data.renderPassDescriptor );
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void MTLImGuiLayer::end() {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( (float)App::getWindow()->getWidth(), (float)App::getWindow()->getHeight() );

        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData( ImGui::GetDrawData(), _data.commandBuffer, _data.commandEncoder );

        [_data endEncoding];
        [_data presentDrawable];
        [_data commit];
    }

    void MTLImGuiLayer::onAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // load font
        auto loadFunc = [&](const char* filepath, float size_pixels) {
            io.Fonts->AddFontFromFileTTF( filepath, size_pixels );
        };
        FontLoader::load( loadFunc );

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg
        // so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL( (GLFWwindow*)App::getWindow()->nativeWindow(), true );
        ImGui_ImplMetal_Init( MTLContext::getContext().nativeDevice );

        _data = [[MTLImGuiData alloc] initWithContext:MTLContext::getContext()];

        CORE_INFO( "ImGui Initialized" );
    }

    void MTLImGuiLayer::onDetach() {
        ImGui_ImplMetal_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
