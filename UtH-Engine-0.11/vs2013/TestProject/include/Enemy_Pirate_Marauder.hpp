#ifndef ENEMY_PIRATE_MARAUDER_HPP
#define ENEMY_PIRATE_MARAUDER_HPP

#include "Enemy.hpp"

class EnemyPirateMarauder : public Enemy
{
public:
	EnemyPirateMarauder(int wave, float angle);
	~EnemyPirateMarauder(){};
protected:

};

#endif