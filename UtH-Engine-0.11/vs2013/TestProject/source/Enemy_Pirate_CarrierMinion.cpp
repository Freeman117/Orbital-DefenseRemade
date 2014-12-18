#include "Enemy_Pirate_CarrierMinion.hpp"

EnemyPirateCarrierMinion::EnemyPirateCarrierMinion(int wave, float angle_) : Enemy()
{
	armor = 5;
	HitBox = 30;
	angle = angle_;
	distance = 400;
	if (wave == 10)
	{
		health = 50;
		speed = 15;
		bounty = 0;
	}
	else if (wave == 20)
	{
		health = 75;
		speed = 15;
		bounty = 0;
	}
	else if (wave == 30)
	{
		health = 100;
		speed = 15;
		bounty = 0;
	}
	speed = 400 / (30 - speed);
}