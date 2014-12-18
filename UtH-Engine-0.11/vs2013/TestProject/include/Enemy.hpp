#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <UtH/UtHEngine.hpp>

class Enemy : public uth::Component
{
public:
	Enemy();
	Enemy(float health, float armor, float speed, float angle);
	~Enemy(){};

	void TakeHit(float damageAmount, float armorPenetration);
	virtual void OnDeath(){};
	float GetDistance();
	void SetDistance(float f);
	void UpdateMovementSpeed(float dt);
	void SetMovementMod(float amount, float duration);
	float GetAngle();
	void SetAngle(float amount);
	float GetSpeed();
	bool GetCarrierSpawn(float dt);
	bool GetAlive();
	bool getCarrierStatus();
	float HitBox;
	float GetBounty();
protected:

	bool isAlive;
	bool isCarrier;
	float health;
	float armor;
	float speed;
	float speedMod;
	float speedDuration;
	float distance;
	float angle;
	float bounty;
	float carrierSpawn;
	uth::Randomizer* randomizer;
private:
};

#endif //ENEMY_HPP