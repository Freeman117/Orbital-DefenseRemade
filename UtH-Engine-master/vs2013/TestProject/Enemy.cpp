#include "Enemy.hpp"

Enemy::Enemy(float health_, float armor_, float speed_, float angle_) : uth::Component("Enemy")
{
	health = health_;
	armor = armor_;
	speed = speed_;
	angle = angle_;
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