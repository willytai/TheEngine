#include "core/application/appMetal.h"
#include "core/renderer/renderer.h"

namespace Engine7414
{
    void AppMetal::run(App& app) {
        CORE_INFO( "Engine Running!" );
        app._stopWatch.reset();

        while ( app._shouldRun ) {
            @autoreleasepool
            {
                TimeStep deltaTime = app._stopWatch.deltaTime();

                if ( !app._minimized ) {
                    for (auto* layer : app._layerStack) {
                        layer->onUpdate( deltaTime );
                    }
                }

                app._imguiLayer->begin();
                for (auto* layer : app._layerStack) {
                    layer->onImGui();
                }
                app._imguiLayer->end();

                app._window->onUpdate();
            }
        }

        Renderer::shutdown();
    }
}
