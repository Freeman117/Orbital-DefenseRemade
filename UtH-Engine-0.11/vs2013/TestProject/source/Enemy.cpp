#include "Enemy.hpp"
Enemy::Enemy()
{
	isAlive = true;
	speedMod = 1;
	distance = 700+randomizer->GetFloat(0,1)*50;
}
Enemy::Enemy(float health_, float armor_, float speed_, float angle_) : uth::Component("Enemy")
{
}

void Enemy::TakeHit(float damageAmount, float armorPenetration)
{
	health -= (damageAmount - armor*armorPenetration);
	if (health <= 0)
	{
		isAlive = false;
	}
}
void Enemy::SetMovementMod(float amount, float duration)
{
	speedDuration = duration;
	speedMod = amount;
}
void Enemy::UpdateMovementSpeed(float dt)
{
	speedDuration -= dt;
	if (speedDuration < 0)
		speedMod = 1;
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
	return speed*speedMod;
}
bool Enemy::GetAlive()
{
	return isAlive;
}
float Enemy::GetBounty()
{
	return bounty;
}
