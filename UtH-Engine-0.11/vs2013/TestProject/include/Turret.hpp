#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/UtHEngine.hpp>

class Turret : public uth::Component
{
public:
	Turret(int t, float orb, float orbPos);
	~Turret();

	void init(int t);
	void Upgrade(float &money,int choice = 1);

	int type;
	int level;
	float damage;
	float speed;
	float range;
	float aoe;

	float totalTime;

	float orbit;
	float orbitPos;

	float cooldown;
	
	
};

#endif