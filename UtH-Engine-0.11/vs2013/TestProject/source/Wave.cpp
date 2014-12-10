#include "Wave.hpp"
void Wave::Init(int wave_, int enemyType1_, float spawnInterval1_, int enemyAmount1_, int enemyType2_ = 0, float spawnInterval2_ = 0, int enemyAmount2_ = 0)
{
	currentWave = wave_;
	enemyType1 = enemyType1_;
	spawnInterval1 = spawnInterval1_;
	enemyAmount1 = enemyAmount1_;
	enemyType2 = enemyType2_;
	spawnInterval2 = spawnInterval2_;
	enemyAmount2 = enemyAmount2_;
}
int Wave::getEnemy(float dt)
{
	if (enemyAmount1 < amountSpawned1 && enemySpawnTimer1 >= spawnInterval1)
	{
		amountSpawned1++;
		enemySpawnTimer1 -= spawnInterval1;
		return enemyType1;
	}
	else if (enemyAmount2 < amountSpawned2 && enemySpawnTimer2 >= spawnInterval2)
	{
		amountSpawned1++;
		enemySpawnTimer2 -= spawnInterval2;
		return enemyType2;
	}
	else
	{
		return 0;
	}
	return -1;
}