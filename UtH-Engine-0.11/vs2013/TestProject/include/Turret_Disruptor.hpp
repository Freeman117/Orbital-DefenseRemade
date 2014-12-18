#ifndef TURRET_DISRUPTOR_HPP
#define TURRET_DISRUPTOR_HPP

#include "Turret.hpp"

class TurretDisruptor : public Turret
{
public:
	TurretDisruptor(float orb, float orbPos);
	~TurretDisruptor(){};
	void Upgrade(float &money, int choice = 1);
private:

};

#endif