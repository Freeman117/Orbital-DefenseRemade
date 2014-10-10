#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <pmath/PMath.hpp>

class Enemy : public uth::Component
{
public:
	Enemy(float health, float armor, float speed, float angle);
	~Enemy(){};

	void TakeHit(float damageAmount);
	float GetDistance();
	void SetDistance(float f);
	float GetAngle();
	float GetSpeed();
	bool GetAlive();
	float HitBox;

protected:

	bool isAlive;
	float health;
	float armor;
	float speed;
	float distance;
	float angle;

private:
};

#endif //ENEMY_HPP