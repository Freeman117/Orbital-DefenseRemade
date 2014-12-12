#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/UtHEngine.hpp>

class Turret : public uth::Component
{
public:
	Turret(){};
	Turret(uth::Texture* projectileTexture_);
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
	float GetSlowAmount(){ return slowAmount; }
	bool GetPenetrate(){ return penetrate; }
	uth::Texture* GetTexture(){ return projectileTexture;}
protected:

	int level;
	float damage;
	float reloadSpeed;
	float bulletSpeed;
	float range;
	float aoe;
	float orbit;
	float orbitPos;
	bool penetrate;
	float slowAmount;
	float armorPenetration;
	float critAmount;
	float cooldown;
	float totalTime;
	uth::Texture* projectileTexture;
};

#endif