#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/UtHEngine.hpp>
#include <pmath/PMath.hpp>
#include "Enemy.hpp"
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Renderer/Texture.hpp>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(){};

	void UpdateEnemies(float deltaTime);
	void DrawEnemies();
	void SpawnEnemy(float healt, float armor, float speed, float angle);

	std::vector<uth::GameObject*> GetEnemies();
	uth::Texture* enemytexture;
protected:
	std::vector<uth::GameObject*> enemies;
};

#endif ENEMYMANAGER_HPP