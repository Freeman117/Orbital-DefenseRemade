#include "Bullet.hpp"

Bullet::Bullet(float bulletPositionX, float bulletPositionY, float dmg, float angle, float velocity, float splash)
{
	bPosx = bulletPositionX;
	bPosy = bulletPositionY;
	damage = dmg;
	rotation = angle;
	speed = velocity;
	explosionradius = splash;
}

Bullet::~Bullet()
{

}

void Bullet::Update(float dt)
{
	for (int i = bullets.size() - 1; i >= 0; i--)
	{
		float bulletposx = bullets[i]->transform.GetPosition().x;
		float bulletposy = bullets[i]->transform.GetPosition().y;

		//bullets[i]->transform.SetPosition();
	}
}