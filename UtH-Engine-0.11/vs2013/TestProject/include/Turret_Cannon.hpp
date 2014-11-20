#ifndef TURRET_CANNON_HPP
#define TURRET_CANNON_HPP

#include "Turret.hpp"

class TurretCannon : public Turret
{
public:
	TurretCannon(float orb, float orbPos);
	~TurretCannon(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif