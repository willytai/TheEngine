#include "core/app.h"
#include "core/layer/layer.h"
#include "core/event/event.h"
#include "core/imgui/imguiLayer.h"
#include "core/util/font.h"

#include "core/input/input.h"

#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertexArray.h"
#include "core/renderer/texture.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/cameraController.h"
#include "core/renderer/frameBuffer.h"

#include "core/scene/scene.h"
#include "core/scene/components.h"

#include "editor/editorLayer.h"

// --------------- entry point ---------------
#ifdef ENGINE_INCLUDE_MAIN
#include "core/entry.h"
#endif
// -------------------------------------------
