#include "Enemy.hpp"

Enemy::Enemy(float healthi, float armori, float speedi, float anglei) : uth::Component("Enemy")
{
	health = healthi;
	armor = armori;
	speed = speedi;
	angle = anglei;
	isAlive = true;
	distance = 700;
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