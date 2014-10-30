#include "Turret.hpp"

Turret::Turret(int type_, int orb, int orbPos) : uth::Component("Turret")
{

	type = type_;
	damage = 0;
	speed = 0;
	cooldown = 0;
	range = 0;
	aoe = 0;
	level = 0;
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
		damage = 50.0f;
		speed= 1.5f;
		range = 100.0f;
	}
	else
	{
		return;
	}
}
void Turret::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 50.0f)
	{
		speed = 1.5f;
		damage = 60;
		range = 105;
		level = 1;
		money -= 50;
	}
	else if (level == 1 && money > 70.0f)
	{
		speed = 1.35;
		damage = 60;
		range = 110;
		level = 2;
		money -= 70;
	}
	else if (level == 2 && money > 90.0f)
	{
		speed = 1.35;
		damage = 65;
		range = 115;
		level = 3;
		money -= 90;
	}
	else if (level == 3 && money > 110.0f)
	{
		speed = 1.2;
		damage = 65;
		range = 120;
		level = 4;
		money -= 110;
	}
	else if (level == 4 && choice == 1 && money > 130.0f)
	{
		speed = 1.2;
		damage = 80;
		range = 120;
		level = 5;
		money -= 130;
	}
	else if (level == 4 && choice == 2 && money > 150.0f)
	{
		speed = 1.2;
		damage = 65;
		range = 150;
		level = 5;
		money -= 150;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}

Turret::~Turret()
{
}
