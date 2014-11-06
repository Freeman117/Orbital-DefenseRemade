#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <UtH/Engine/Engine.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderAttributes.hpp>
#include <memory>
#include <array>
#include "Button.hpp"

class MenuScene : public uth::Scene
{
public:
	MenuScene();
	~MenuScene();
	bool Init() override;
	bool DeInit() override;
	void Update(float dt);
private:
	uth::Camera menuCamera;
	std::array<ns::Button*, 2> buttons;
};

#endif