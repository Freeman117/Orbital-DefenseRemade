#ifndef ENEMY_PIRATE_STRIKER_HPP
#define ENEMY_PIRATE_STRIKER_HPP

#include "Enemy.hpp"

class EnemyPirateStriker : public Enemy
{
public:
	EnemyPirateStriker(int wave, float angle);
	~EnemyPirateStriker(){};
protected:

};

#endif