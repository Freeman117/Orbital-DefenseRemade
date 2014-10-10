#include "Bullet.hpp"

Bullet::Bullet(float bulletPositionX, float bulletPositionY, float angle, float velocity, float damage_, float range_, float splash) : uth::Component("Bullet")
{
	bPosx = bulletPositionX;
	bPosy = bulletPositionY;
	damage = damage_;
	rotation = angle;
	speed = velocity;
	range = range_;
	explosionradius = splash;
	travelledDistance = 0;
	hitBox = 5;
}

Bullet::~Bullet()
{

}

bool Bullet::MaxRangeTravelled(float dt)
{
	travelledDistance += speed*dt;
	if (travelledDistance >= range)
		return true;
	else
		return false;
}