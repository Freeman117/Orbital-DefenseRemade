#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Engine.hpp>

class Player : public uth::GameObject
{
public:
	Player();
	~Player();
	float health;
private:
	void update(float dt) override;
	void draw(uth::RenderTarget& target) override;

};

#endif