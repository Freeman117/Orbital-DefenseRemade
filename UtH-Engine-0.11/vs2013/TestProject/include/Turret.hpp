#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/UtHEngine.hpp>

class Turret : public uth::Component
{
public:
	Turret(){};
	~Turret(){};
	bool CanShoot();
	virtual void Upgrade(float &money, int choice = 1){};
	float GetOrbit(){ return orbit; }
	float GetOrbitPos(){ return orbitPos; }
	float GetCooldown(){ return cooldown; }
	void SetCooldown(float value){cooldown = value;}
	float GetReloadSpeed(){ return reloadSpeed; }
	float GetDamage(){ return damage; }
	float GetRange(){ return range; }
	float GetAoe(){ return aoe; }
	float GetBulletSpeed(){ return bulletSpeed; }
protected:

	int level;
	float damage;
	float reloadSpeed;
	float bulletSpeed;
	float range;
	float aoe;
	float orbit;
	float orbitPos;

	float cooldown;
	float totalTime;
};

#endif