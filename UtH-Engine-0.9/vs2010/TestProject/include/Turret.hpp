#pragma once
#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/UtHEngine.h>

class Turret
{
public:
	Turret(uth::SpriteBatch*);
	~Turret();

	void init(int t, int orb,int orbPos);

	int type;
	float damage;
	float speed;
	float range;
	float aoe;

	float totalTime;

	float orbit;
	float orbitPos;

	float testi;
	float testi2;

	std::vector<uth::GameObject*> turrets;

	void Update(float dt, float rotation);
	void AddTurret(float o,float oPos, int tType);
	void Draw();

	uth::SpriteBatch* _spriteBatch;
	uth::GameObject* turret;
	
};

#endif