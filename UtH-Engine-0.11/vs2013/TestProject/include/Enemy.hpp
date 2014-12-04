#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <pmath/PMath.hpp>

class Enemy : public uth::Component
{
public:
	Enemy();
	Enemy(float health, float armor, float speed, float angle);
	~Enemy(){};

	void TakeHit(float damageAmount);
	virtual void OnDeath(){};
	float GetDistance();
	void SetDistance(float f);
	void UpdateMovementSpeed(float dt);
	void SetMovementMod(float amount, float duration);
	float GetAngle();
	float GetSpeed();
	bool GetAlive();
	float HitBox;
	float GetBounty();
protected:

	bool isAlive;
	float health;
	float armor;
	float speed;
	float speedMod;
	float speedDuration;
	float distance;
	float angle;
	float bounty;
	uth::Randomizer* randomizer;
private:
};

#endif //ENEMY_HPP