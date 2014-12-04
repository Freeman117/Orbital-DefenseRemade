#ifndef TURRET_MRK_HPP
#define TURRET_MRK_HPP

#include "Turret.hpp"

class TurretMrk : public Turret
{
public:
	TurretMrk(float orb, float orbPos);
	~TurretMrk(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif