#include "Enemy.hpp"

Enemy::Enemy(float healthi, float armori, float speedi)
{
	health = healthi;
	armor = armori;
	speed = speedi;
	isAlive = true;
}

void Enemy::TakeHit(float damageAmount)
{
	health -= (damageAmount - armor);
	if (health <= 0)
	{
		isAlive = false;
	}
}
