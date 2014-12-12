#include "Turret_Mrk.hpp"

TurretMrk::TurretMrk(float orb, float orbPos, uth::Texture* projectileTexture) : Turret(projectileTexture)
{
	damage = 120;
	reloadSpeed = 4;
	bulletSpeed = 1000;
	range = 250;
	aoe = 0;
	cooldown = 0;
	totalTime = 0;
	level = 0;
	penetrate = true;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretMrk::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 200.0f)
	{
		reloadSpeed = 3.75f;
		damage = 140;
		range = 260.0f;
		aoe = 0;
		level = 1;
		money -= 70;
	}
	else if (level == 1 && money > 300.0f)
	{
		reloadSpeed = 3.5f;
		damage = 160;
		range = 270;
		aoe = 140;
		level = 2;
		money -= 95;
	}
	else if (level == 2 && money > 400.0f)
	{
		reloadSpeed = 3.25f;
		damage = 180;
		range = 280.0f;
		aoe = 160;
		level = 3;
		money -= 120;
	}
	else if (level == 3 && money > 500.0f)
	{
		reloadSpeed = 3.0f;
		damage = 200;
		range = 290.0f;
		aoe = 180;
		level = 4;
		money -= 145;
	}
	else if (level == 4 && choice == 1 && money > 600.0f)
	{
		reloadSpeed = 3.0f;
		damage = 250;
		range = 300.0f;
		aoe = 200;
		level = 5;
		money -= 180;
	}
	else if (level == 4 && choice == 2 && money > 600.0f)
	{
		reloadSpeed = 2.25f;
		damage = 200;
		range = 300.0;
		aoe = 200;
		level = 5;
		money -= 180;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}