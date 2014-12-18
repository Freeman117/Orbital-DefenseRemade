#include "Enemy_Pirate_Carrier.hpp"

EnemyPirateCarrier::EnemyPirateCarrier(int wave, float angle_) : Enemy()
{
	armor = 0;
	carrierSpawn = 0;
	HitBox = 80;
	angle = angle_;
	isCarrier = true;
	if (wave == 10)
	{
		health = 1500;
		speed = 0;
		bounty = 150;
	}
	else if (wave == 20)
	{
		health = 2000;
		speed = 0;
		bounty = 150;
	}
	else if (wave == 30)
	{
		health = 2500;
		speed = 0;
		bounty = 150;
	}
	speed = 700 / (30 - speed);
}