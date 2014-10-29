#include "Turret.hpp"

Turret::Turret(int type_, int orb, int orbPos) : uth::Component("Turret")
{

	type = type_;
	damage = 0;
	speed = 0;
	cooldown = 0;
	range = 0;
	aoe = 0;
	orbit = orb;
	orbitPos = orbPos;
	totalTime = 0;

	init(type);

}

void Turret::init(int t)
{
	type = t;
	if (t == 1)
	{
		damage = 25.0f;
		speed= 1.0f;
		range = 100.0f;
		aoe = 0.0f;
	}
	else
	{
		return;
	}
}


Turret::~Turret()
{
}
