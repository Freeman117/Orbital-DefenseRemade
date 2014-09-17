#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Math/Math.hpp>

class Enemy
{
public:
	Enemy(float health, float armor, float speed,uth::SpriteBatch*);
	~Enemy(){};

	void Update(float deltaTime);
	void Draw();
	void TakeHit(float damageAmount);


protected:

	float health;
	float armor;
	float speed;
    
private:
};

#endif ENEMY_HPP