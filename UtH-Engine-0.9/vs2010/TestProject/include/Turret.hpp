#pragma once
#ifndef TURRET_H_
#define TURRET_H_

<<<<<<< HEAD
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/UtHEngine.h>
=======
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <stdlib.h>

>>>>>>> origin/master

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

<<<<<<< HEAD
	float orbit;
	float orbitPos;

	std::vector<uth::GameObject*> turrets;

	void Update(float dt, float rotation);
	void AddTurret(float o,float oPos, int tType);
	void Draw();

	uth::SpriteBatch* _spriteBatch;
	uth::GameObject* turret;
=======
	int orbit;
	int orbitPos;

	std::vector<uth::GameObject*> turrets;

	void Update(float dt);
	void AddTurret(int o,int oPos, int tType);


	uth::SpriteBatch* _spriteBatch;
	Turret* turret;
>>>>>>> origin/master
	
};

#endif