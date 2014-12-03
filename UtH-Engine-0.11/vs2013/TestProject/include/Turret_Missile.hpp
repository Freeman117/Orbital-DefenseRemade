#ifndef TURRET_MISSILE_HPP
#define TURRET_MISSILE_HPP

#include "Turret.hpp"

class TurretMissile : public Turret
{
public:
	TurretMissile(float orb, float orbPos);
	~TurretMissile(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif