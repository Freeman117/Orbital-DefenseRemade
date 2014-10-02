#ifndef TURRETMANAGER_HPP
#define TURRETMANAGER_HPP

#include <UtH\Engine\UtHEngine.h>
#include <pmath/PMath.hpp>
#include "Turret.hpp"
#include "Enemy.hpp"
#include "EnemyManager.hpp"

class TurretManager
{
public:
	TurretManager();
	~TurretManager(){};

	void UpdateTurrets(float deltaTime, EnemyManager* enemyManager);
	void RotateTurrets(int orb, float angle);
	void DrawTurrets();
	void CreateTurret(float type, float orb, float orbPos);

	std::vector<uth::GameObject*> turrets;

protected:

	float orbit01Angle;
	float orbit02Angle;


private:

};

#endif