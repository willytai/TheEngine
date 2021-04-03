#ifndef __LAYER2D_H__
#define __LAYER2D_H__

#include "engine.h"

class Layer2D : public Engine7414::Layer
{
public:
	Layer2D(const char* name);

	void onAttach() override;
	void onEvent(Engine7414::Event& event) override;
	void onImGui() override;
	void onUpdate(const Engine7414::TimeStep& deltaTime) override;

private:
	glm::vec4						_color;
	Engine7414::CameraController	_cameraController;
	Engine7414::Ref<Engine7414::Texture2D>    _texture;
};

#endif