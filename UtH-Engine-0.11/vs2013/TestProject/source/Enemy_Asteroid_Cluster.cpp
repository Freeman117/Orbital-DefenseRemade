#include "Enemy_Asteroid_Cluster.hpp"

EnemyAsteroidCluster::EnemyAsteroidCluster(int wave, float angle_) : Enemy()
{
	HitBox = 70;
	angle = angle_;
	if (wave < 3)
	{
		health = 200;
		speed = 30;
		bounty = 10;
		armor = 0;
	}
	else if (wave < 18)
	{
		health = 200 + wave * 25;
		speed = 30;
		bounty = 10 + wave * 3;
		armor = 0;
	}
	else
	{
		health = 200 + wave * 25;
		speed = 30;
		bounty = 25;
		armor = 0;
	}
}
void EnemyAsteroidCluster::OnDeath()
{

}