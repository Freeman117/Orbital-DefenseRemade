#ifndef ENEMY_ASTEROID_CLUSTER_HPP
#define ENEMY_ASTEROID_CLUSTER_HPP

#include "Enemy.hpp"

class EnemyAsteroidCluster : public Enemy
{
public:
	EnemyAsteroidCluster(int wave, float angle);
	~EnemyAsteroidCluster(){};
    void OnDeath();
private:

};

#endif