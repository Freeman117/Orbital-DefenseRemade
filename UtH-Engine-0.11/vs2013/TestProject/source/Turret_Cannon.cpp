#include "Turret_Cannon.hpp"

TurretCannon::TurretCannon(float orb, float orbPos) : Turret()
{
	damage = 50;
	reloadSpeed = 1.5f;
	bulletSpeed = 400;
	range = 100;
	aoe = 0;
	cooldown = 0;
	totalTime = 0;
	level = 0;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretCannon::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 50.0f)
	{
		reloadSpeed = 1.5f;
		damage = 60;
		range = 105;
		level = 1;
		money -= 50;
	}
	else if (level == 1 && money > 70.0f)
	{
		reloadSpeed = 1.35f;
		damage = 60;
		range = 110;
		level = 2;
		money -= 70;
	}
	else if (level == 2 && money > 90.0f)
	{
		reloadSpeed = 1.35f;
		damage = 65;
		range = 115;
		level = 3;
		money -= 90;
	}
	else if (level == 3 && money > 110.0f)
	{
		reloadSpeed = 1.2f;
		damage = 65;
		range = 120;
		level = 4;
		money -= 110;
	}
	else if (level == 4 && choice == 1 && money > 130.0f)
	{
		reloadSpeed = 1.2f;
		damage = 80;
		range = 120;
		level = 5;
		money -= 130;
	}
	else if (level == 4 && choice == 2 && money > 150.0f)
	{
		reloadSpeed = 1.2f;
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