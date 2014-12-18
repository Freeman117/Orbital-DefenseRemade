#ifndef WAVE_HPP
#define WAVE_HPP

class Wave
{
public:
	Wave(){};
	~Wave(){};
	void Init(int wave,int enemyType1,float spawnInterval1,int enemyAmount1,int enemyType2 = 0,float spawnInterval2 = 0,int enemyAmount2 = 0);
	int getEnemy(float dt);
	bool allEnemiesSpawned();
private:
	float enemySpawnTimer1, enemySpawnTimer2;
	float spawnInterval1, spawnInterval2;
	int enemyType1, enemyType2;
	int enemyAmount1, enemyAmount2;
	int amountSpawned1, amountSpawned2;
	int currentWave;
};

#endif