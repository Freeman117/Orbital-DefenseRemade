#ifndef TURRET_RMK_HPP
#define TURRET_MRK_HPP

#include "Turret.hpp"

class TurretMrk : public Turret
{
public:
	TurretMrk(float orb, float orbPos, uth::Texture* projectileTexture);
	~TurretMrk(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif