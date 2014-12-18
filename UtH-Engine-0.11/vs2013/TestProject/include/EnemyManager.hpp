#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/UtHEngine.hpp>

#include "Enemy.hpp"
#include "Wave.hpp"
#include "Enemy_Asteroid_Small.hpp"
#include "Enemy_Asteroid_Cluster.hpp"
#include "Enemy_Pirate_Carrier.hpp"
#include "Enemy_Pirate_Marauder.hpp"
#include "Enemy_Pirate_Scout.hpp"
#include "Enemy_Pirate_Striker.hpp"
#include "Enemy_Pirate_CarrierMinion.hpp"

class EnemyManager : public uth::GameObject
{
public:
	EnemyManager();
	~EnemyManager(){};

	void UpdateEnemies(float deltaTime, int &health, float &money);
	void DrawEnemies();
	void SpawnEnemy(int wave, int type, float angle);
	void InitWaves(int wave);
	void UpdateWaves(float dt);

	std::vector<std::shared_ptr<uth::GameObject>> GetEnemies();
	uth::Texture* asteroidTextures;
	uth::Texture* pirateTextures;
	uth::Texture* carrierTextures;
	Wave waves[30];
protected:
	uth::Randomizer* randomizer;
	std::vector<std::shared_ptr<uth::GameObject>> enemies;
	int currentWave;
};

#endif