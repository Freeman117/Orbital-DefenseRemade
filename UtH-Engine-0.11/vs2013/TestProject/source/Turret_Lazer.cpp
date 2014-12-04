#include "Turret_Lazer.hpp"

TurretLazer::TurretLazer(float orb, float orbPos, uth::Texture* projectileTexture) : Turret(projectileTexture)
{
	damage = 16;
	reloadSpeed = 0.6f;
	bulletSpeed = 500;
	range = 120;
	aoe = 0;
	cooldown = 0;
	totalTime = 0;
	slowAmount = 1;
	penetrate = false;
	level = 0;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretLazer::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 70.0f)
	{
		reloadSpeed = 0.6f;
		damage = 18;
		range = 130.0f;
		aoe = 0;
		level = 1;
		money -= 70;
	}
	else if (level == 1 && money > 110.0f)
	{
		reloadSpeed = 0.6f;
		damage = 20;
		range = 165;
		level = 2;
		money -= 95;
	}
	else if (level == 2 && money > 140.0f)
	{
		reloadSpeed = 0.6f;
		damage = 23;
		range = 140.0f;
		level = 3;
		money -= 120;
	}
	else if (level == 3 && money > 170.0f)
	{
		reloadSpeed = 0.6f;
		damage = 25;
		range = 150.0f;
		level = 4;
		money -= 145;
	}
	else if (level == 4 && choice == 1 && money > 200.0f)
	{
		reloadSpeed = 0.45f;
		damage = 25;
		range = 160.0f;
		level = 5;
		money -= 180;
	}
	else if (level == 4 && choice == 2 && money > 200.0f)
	{
		reloadSpeed = 0.6f;
		damage = 25;
		range = 160.0;
		level = 5;
		money -= 180;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}