#ifndef TURRET_LAZER_HPP
#define TURRET_LAZER_HPP

#include "Turret.hpp"

class TurretLazer : public Turret
{
public:
	TurretLazer(float orb, float orbPos);
	~TurretLazer(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif