#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Math/Math.hpp>

class Enemy : uth::Component
{
public:
	Enemy(float health, float armor, float speed);
	~Enemy(){};

	void TakeHit(float damageAmount);


protected:

	bool isAlive;
	float health;
	float armor;
	float speed;
    
private:
};

#endif ENEMY_HPP