#include "Enemy_Pirate_Marauder.hpp"

EnemyPirateMarauder::EnemyPirateMarauder(int wave, float angle_) : Enemy()
{
	armor = 10;
	HitBox = 30;
	angle = angle_;
	if (wave == 8 || wave == 11)
	{
		health = 250;
		speed = 16;
		bounty = 20;
	}
	else if (wave == 7)
	{
		health = 250;
		speed = 16;
		bounty = 20;
		armor = 13;
	}
	else if (wave == 12)
	{
		health = 250;
		speed = 19;
		bounty = 20;
	}
	else if (wave == 13)
	{
		health = 368;
		speed = 16;
		bounty = 20;
	}
	else if (wave == 16)
	{
		health = 250;
		speed = 16;
		bounty = 20;
		armor = 15;
	}
	else if (wave == 19 || wave == 25 || wave == 26)
	{
		health = 275;
		speed = 16;
		bounty = 20;
	}
	else if (wave == 21)
	{
		health = 438;
		speed = 16;
		bounty = 20;
	}
	speed = 700 / (30 - speed);
}