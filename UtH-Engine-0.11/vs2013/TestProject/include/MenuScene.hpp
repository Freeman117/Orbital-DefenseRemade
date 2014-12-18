#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <UtH/UtHEngine.hpp>
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
	uth::GameObject* title;

	uth::GameObject* Background;
};

#endif