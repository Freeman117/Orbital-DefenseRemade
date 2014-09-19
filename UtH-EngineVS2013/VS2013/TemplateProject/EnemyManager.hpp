#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/Engine/UtHEngine.h>
#include <pmath/PMath.hpp>
#include "Enemy.hpp"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(){};

	std::vector<uth::GameObject*> enemies;

	void UpdateEnemies();
	void DrawEnemies();
	void SpawnEnemy();
};

#endif ENEMYMANAGER_HPP