#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/UtHEngine.hpp>
#include <pmath/PMath.hpp>
#include "Enemy.hpp"
#include "Wave.hpp"
#include "Enemy_Asteroid_Small.hpp"
#include "Enemy_Asteroid_Cluster.hpp"
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Renderer/Texture.hpp>
#include <UtH/Engine/GameObject.hpp>


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