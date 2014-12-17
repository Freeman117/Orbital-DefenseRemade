#include "Enemy_Asteroid_Small.hpp"

EnemyAsteroidSmall::EnemyAsteroidSmall(int wave,float angle_) : Enemy()
{
	armor = 0;
	HitBox = 30;
	angle = angle_;
	if (wave == 1 || wave == 2 || wave == 6 || wave == 11)
	{
		health = 20;
		speed = 17;
		bounty = 2;
	}
	else if (wave == 3)
	{
		health = 25;
		speed = 17;
		bounty = 2;
	}
	else if (wave == 15||wave == 17 || wave == 22)
	{
		health = 22;
		speed = 17;
		bounty = 2;
	}
	else if (wave == 23 || wave == 27)
	{
		health = 20;
		speed = 21;
		bounty = 2;
	}
	speed = 700/(30 - speed);
}