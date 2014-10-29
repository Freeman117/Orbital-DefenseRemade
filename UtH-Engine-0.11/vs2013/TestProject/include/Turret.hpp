#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/UtHEngine.hpp>

class Turret : public uth::Component
{
public:
	Turret(int t, int orb, int orbPos);
	~Turret();

	void init(int t);

	int type;
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