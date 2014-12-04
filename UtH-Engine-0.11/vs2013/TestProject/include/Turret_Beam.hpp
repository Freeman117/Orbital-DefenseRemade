#ifndef TURRET_BEAM_HPP
#define TURRET_BEAM_HPP

#include "Turret.hpp"

class TurretBeam : public Turret
{
public:
	TurretBeam(float orb, float orbPos,uth::Texture* projectileTexture);
	~TurretBeam(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif