#include "Enemy_Pirate_Scout.hpp"

EnemyPirateScout::EnemyPirateScout(int wave, float angle_) : Enemy()
{
	armor = 0;
	HitBox = 30;
	angle = angle_;
	if (wave == 2 || wave == 8)
	{
		health = 25;
		speed = 19;
		bounty = 6;
	}
	else if (wave == 3)
	{
		health = 31;
		speed = 19;
		bounty = 6;
	}
	else if (wave == 5)
	{
		health = 25;
		speed = 21;
		bounty = 6;
	}
	else if (wave == 10 || wave == 14 || wave == 26)
	{
		health = 28;
		speed = 19;
		bounty = 6;
	}
	else if (wave == 12 || wave == 18)
	{
		health = 25;
		speed = 22;
		bounty = 6;
	}
	else if (wave == 21)
	{
		health = 43;
		speed = 19;
		bounty = 6;
	}
	else if (wave == 28)
	{
		health = 50;
		speed = 19;
		bounty = 6;
	}
	speed = 700 / (30 - speed);
}