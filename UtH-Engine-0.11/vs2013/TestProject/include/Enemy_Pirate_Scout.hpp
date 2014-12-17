#ifndef ENEMY_PIRATE_SCOUT_HPP
#define ENEMY_PIRATE_SCOUT_HPP

#include "Enemy.hpp"

class EnemyPirateScout : public Enemy
{
public:
	EnemyPirateScout(int wave, float angle);
	~EnemyPirateScout(){};
protected:

};

#endif