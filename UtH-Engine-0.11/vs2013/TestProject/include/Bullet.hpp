#pragma once
#ifndef BULLET_H_
#define BULLET_H_
#include <UtH/UtHEngine.hpp>

class Bullet : public uth::Component
{
public:
	Bullet(float bulletPositionX, float bulletPositionY, float angle, float velocity, float dmg,float range, float splash = 0, bool penetrate = false, float slowAmount = 1,float crit = 1, float armorPenetration = 1);
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
	float crit;
	float armorPenetration;
private:

};

#endif
