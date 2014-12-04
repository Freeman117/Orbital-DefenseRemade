#include "Turret_Missile.hpp"

TurretMissile::TurretMissile(float orb, float orbPos, uth::Texture* projectileTexture) : Turret(projectileTexture)
{
	damage = 35;
	reloadSpeed = 2.2f;
	bulletSpeed = 450;
	range = 150;
	aoe = 50;
	cooldown = 0;
	totalTime = 0;
	level = 0;
	slowAmount = 1;
	penetrate = false;
	orbit = orb;
	orbitPos = orbPos;
}

void TurretMissile::Upgrade(float &money, int choice)
{
	if (level == 0 && money > 80.0f)
	{
		reloadSpeed = 2.2f;
		damage = 40;
		range = 157.5f;
		aoe = 55;
		level = 1;
		money -= 80;
	}
	else if (level == 1 && money > 110.0f)
	{
		reloadSpeed = 2.1f;
		damage = 45;
		range = 165;
		aoe = 60;
		level = 2;
		money -= 110;
	}
	else if (level == 2 && money > 140.0f)
	{
		reloadSpeed = 2.1f;
		damage = 50;
		range = 172.5f;
		aoe = 65;
		level = 3;
		money -= 140;
	}
	else if (level == 3 && money > 170.0f)
	{
		reloadSpeed = 2.0f;
		damage = 55;
		range = 180;
		aoe = 70;
		level = 4;
		money -= 170;
	}
	else if (level == 4 && choice == 1 && money > 200.0f)
	{
		reloadSpeed = 2.0;
		damage = 60;
		range = 187.5f;
		aoe = 85;
		level = 5;
		money -= 200;
	}
	else if (level == 4 && choice == 2 && money > 200.0f)
	{
		reloadSpeed = 1.2f;
		damage = 65;
		range = 187.5f;
		aoe = 75;
		level = 5;
		money -= 200;
	}
	else
	{
		std::cout << "Cannot upgrade!" << std::endl;
	}
}