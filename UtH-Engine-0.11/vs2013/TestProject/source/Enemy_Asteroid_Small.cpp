#include "Enemy_Asteroid_Small.hpp"

EnemyAsteroidSmall::EnemyAsteroidSmall(int wave,float angle_) : Enemy()
{
	HitBox = 30;
	angle = angle_;
	if (wave < 5)
	{
		health = 20;
		speed = 50;
		armor = 0;
		bounty = 1;
	}
	else if (wave < 15)
	{
		health = 20;
		speed = 50 + (wave - 5)*5;
		armor = 0 + wave - 5;
		bounty = 2;
	}
	else
	{
		health = 20;
		speed = 100;
		bounty = 2;
		armor = 10;
	}
}