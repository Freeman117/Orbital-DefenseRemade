#include "Turret_Beam.hpp"

TurretBeam::TurretBeam(float orb, float orbPos) : Turret()
{
	damage = 175;
	reloadSpeed = 3.5f;
	bulletSpeed = 1000;
	range = 150;
	aoe = 0;
	cooldown = 0;
	totalTime = 0;
	level = 0;
	frameAmounts = 1;
	startFrame = 42;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretBeam::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 70.0f)
	{
		reloadSpeed = 3.4f;
		damage = 190;
		range = 170.0f;
		aoe = 0;
		level = 1;
		money -= 70;
	}
	else if (level == 1 && money > 110.0f)
	{
		reloadSpeed = 3.3f;
		damage = 200;
		range = 220;
		level = 2;
		money -= 95;
	}
	else if (level == 2 && money > 140.0f)
	{
		reloadSpeed = 3.2f;
		damage = 210;
		range = 230.0f;
		level = 3;
		money -= 120;
	}
	else if (level == 3 && money > 170.0f)
	{
		reloadSpeed = 3.1f;
		damage = 220;
		range = 250.0f;
		level = 4;
		money -= 145;
	}
	else if (level == 4 && choice == 1 && money > 200.0f)
	{
		reloadSpeed = 3.0f;
		damage = 255;
		range = 220.0f;
		level = 5;
		money -= 180;
	}
	else if (level == 4 && choice == 2 && money > 200.0f)
	{
		reloadSpeed = 3.0f;
		damage = 220;
		range = 200.0;
		level = 5;
		money -= 180;
		armorPenetration = 0.25f;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}