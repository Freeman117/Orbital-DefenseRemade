#include "Enemy_Asteroid_Cluster.hpp"

EnemyAsteroidCluster::EnemyAsteroidCluster(int wave, float angle_) : Enemy()
{
	HitBox = 70;
	angle = angle_;
	if (wave == 4 || wave == 6)
	{
		health = 250;
		speed = 9;
		bounty = 75;
		armor = 10;
	}
	else if (wave == 15 || wave == 22)
	{
		health = 825;
		speed = 9;
		bounty = 75;
		armor = 10;
	}
	else if (wave == 16)
	{
		health = 750;
		speed = 9;
		bounty = 75;
		armor = 15;
	}
	else if (wave == 23)
	{
		health == 750;
		speed = 13;
		bounty = 75;
		armor = 10;
	}
	else if (wave == 28)
	{
		health == 1500;
		speed = 9;
		bounty = 75;
		armor = 10;
	}
	speed = 700 / (30 - speed);
}
void EnemyAsteroidCluster::OnDeath()
{

}