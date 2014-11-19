#ifndef ENEMY_ASTEROID_SMALL_HPP
#define ENEMY_ASTEROID_SMALL_HPP

#include "Enemy.hpp"

class EnemyAsteroidSmall : public Enemy
{
public:
	EnemyAsteroidSmall(int wave,float angle);
	~EnemyAsteroidSmall(){};
protected:

};

#endif