#include "Enemy_Pirate_Striker.hpp"

EnemyPirateStriker::EnemyPirateStriker(int wave, float angle_) : Enemy()
{
	armor = 7;
	HitBox = 30;
	angle = angle_;
	if (wave == 9)
	{
		health = 25;
		speed = 22;
		bounty = 10;
	}
	else if (wave == 5)
	{
		health = 25;
		speed = 19;
		bounty = 10;
	}
	else if (wave == 14 || wave == 24)
	{
		health = 28;
		speed = 22;
		bounty = 10;
	}
	else if (wave == 18)
	{
		health = 25;
		speed = 25;
		bounty = 10;
	}
	else if (wave == 20)
	{
		health = 30;
		speed = 22;
		bounty = 10;
	}
	else if (wave == 29)
	{
		health = 25;
		speed = 22;
		bounty = 10;
		armor = 15;
	}
	speed = 700 / (30 - speed);
}