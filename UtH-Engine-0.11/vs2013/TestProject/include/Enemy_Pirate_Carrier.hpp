#ifndef ENEMY_PIRATE_CARRIER_HPP
#define ENEMY_PIRATE_CARRIER_HPP

#include "Enemy.hpp"

class EnemyPirateCarrier : public Enemy
{
public:
	EnemyPirateCarrier(int wave, float angle);
	~EnemyPirateCarrier(){};
protected:

};

#endif