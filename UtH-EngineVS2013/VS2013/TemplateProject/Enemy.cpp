#include "Enemy.hpp"

Enemy::Enemy(float healthi, float armori, float speedi,uth::SpriteBatch* spriteBatch)
{
	health = healthi;
	armor = armori;
	speed = speedi;

}

void Enemy::TakeHit(float damageAmount)
{
	health -= (damageAmount - armor);
}
void Enemy::Update(float dt)
{

}