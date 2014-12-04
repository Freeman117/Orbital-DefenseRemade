#pragma once
#ifndef BULLET_H_
#define BULLET_H_
#include <UtH/Engine/GameObject.hpp>

class Bullet : public uth::Component
{
public:
	Bullet(float bulletPositionX, float bulletPositionY, float angle, float velocity, float dmg,float range, float splash = 0, bool penetrate = false, float slowAmount = 1);
	~Bullet();

	bool MaxRangeTravelled(float dt);
	float bPosx, bPosy;
	float damage;
	float rotation;
	float speed;
	float explosionradius;
	float range;
	float travelledDistance;
	float hitBox;
	bool penetrate;
	float slowAmount;
private:

};

#endif
