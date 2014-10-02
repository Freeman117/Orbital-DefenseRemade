#pragma once
#ifndef BULLET_H_
#define BULLET_H_
#include <UtH/Engine/GameObject.hpp>

class Bullet : public uth::GameObject
{
public:
	Bullet(float bulletPositionX,float bulletPositionY,float dmg, float angle, float velocity,float splash);
	~Bullet();
	void Update(float dt);
	std::vector<Bullet*> bullets;
private:
	float bPosx, bPosy;
	float damage;
	float rotation;
	float speed;
	float explosionradius;

};

#endif
