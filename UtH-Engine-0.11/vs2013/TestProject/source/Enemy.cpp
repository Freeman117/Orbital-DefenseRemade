#include "Enemy.hpp"
Enemy::Enemy()
{
	isAlive = true;
	distance = 700;
	angle = randomizer->GetFloat(0.0f, 1.0f) * 360;
}
Enemy::Enemy(float health_, float armor_, float speed_, float angle_) : uth::Component("Enemy")
{
}

void Enemy::TakeHit(float damageAmount)
{
	health -= (damageAmount - armor);
	if (health <= 0)
	{
		isAlive = false;
	}
}
float Enemy::GetAngle()
{
	return angle;
}
float Enemy::GetDistance()
{
	return distance;
}
void Enemy::SetDistance(float f)
{
	distance = f;
}
float Enemy::GetSpeed()
{
	return speed;
}
bool Enemy::GetAlive()
{
	return isAlive;
}
float Enemy::GetBounty()
{
	return bounty;
}
