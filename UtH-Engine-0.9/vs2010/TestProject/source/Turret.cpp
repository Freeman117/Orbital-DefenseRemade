#include "Turret.hpp"


Turret::Turret()
{
	
}

void Turret::init(int t, int orb,int orbPos)
{
	damage = 0;
	speed = 0;
	range = 0;
	aoe = 0;
	orbit = 0;
	orbitPos = 0;

	if(t == 1)
	{
		damage = 1.0f;
		speed = 2.0f;
		range = 150.0f;
		aoe = 0;
		type = 1;
	}
	else
	{
		
	}

	orbit = orb;
	orbitPos = orbPos;

}

void Turret::AddTurret(int o, int oPos)
{
	
}

void Turret::Update(float dt)
{
	
}

Turret::~Turret()
{
}
