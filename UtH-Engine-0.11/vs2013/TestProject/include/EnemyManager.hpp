#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/UtHEngine.hpp>

#include "Enemy.hpp"
#include "Wave.hpp"
#include "Enemy_Asteroid_Small.hpp"
#include "Enemy_Asteroid_Cluster.hpp"


class EnemyManager : public uth::GameObject
{
public:
	EnemyManager();
	~EnemyManager(){};

	void UpdateEnemies(float deltaTime, int &health);
	void DrawEnemies();
	void SpawnEnemy(int wave, int type, float angle);
	void InitWaves(int wave);
	void UpdateWaves(float dt);

	std::vector<std::shared_ptr<uth::GameObject>> GetEnemies();
	uth::Texture* enemytexture;
	Wave waves[10];
protected:
	std::vector<std::shared_ptr<uth::GameObject>> enemies;
	int currentWave;
};

#endif