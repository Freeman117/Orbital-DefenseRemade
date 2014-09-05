#pragma once
#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <stdlib.h>


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

	int orbit;
	int orbitPos;

	std::vector<uth::GameObject*> turrets;

	void Update(float dt);
	void AddTurret(int o,int oPos, int tType);


	uth::SpriteBatch* _spriteBatch;
	Turret* turret;
	
};

#endif