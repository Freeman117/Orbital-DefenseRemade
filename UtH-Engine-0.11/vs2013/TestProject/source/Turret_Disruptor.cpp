#include "Turret_Disruptor.hpp"

TurretDisruptor::TurretDisruptor(float orb, float orbPos, uth::Texture* projectileTexture) : Turret(projectileTexture)
{
	damage = 12;
	reloadSpeed = 1;
	bulletSpeed = 250;
	range = 150;
	aoe = 100;
	cooldown = 0;
	totalTime = 0;
	level = 0;
	slowAmount = 0.75f;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretDisruptor::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 70.0f)
	{
		reloadSpeed = 1;
		damage = 14;
		range = 170.0f;
		aoe = 120;
		slowAmount = 0.70f;
		level = 1;
		money -= 70;
	}
	else if (level == 1 && money > 110.0f)
	{
		reloadSpeed = 1;
		damage = 18;
		range = 220;
		aoe = 140;
		slowAmount = 0.65f;
		level = 2;
		money -= 95;
	}
	else if (level == 2 && money > 140.0f)
	{
		reloadSpeed = 1;
		damage = 18;
		range = 230.0f;
		aoe = 160;
		slowAmount = 0.6f;
		level = 3;
		money -= 120;
	}
	else if (level == 3 && money > 170.0f)
	{
		reloadSpeed = 1;
		damage = 20;
		range = 250.0f;
		aoe = 180;
		slowAmount = 0.55f;
		level = 4;
		money -= 145;
	}
	else if (level == 4 && choice == 1 && money > 200.0f)
	{
		reloadSpeed = 0.6f;
		damage = 20;
		range = 250.0f;
		aoe = 200;
		slowAmount = 0.55f;
		level = 5;
		money -= 180;
	}
	else if (level == 4 && choice == 2 && money > 200.0f)
	{
		reloadSpeed = 1;
		damage = 20;
		range = 250.0;
		aoe = 200;
		slowAmount = 0.45f;
		level = 5;
		money -= 180;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}