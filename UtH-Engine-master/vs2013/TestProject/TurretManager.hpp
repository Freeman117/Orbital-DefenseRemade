#ifndef TURRETMANAGER_HPP
#define TURRETMANAGER_HPP

#include <UtH/Engine/Engine.hpp>
#include <pmath/PMath.hpp>
#include "Turret.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "EnemyManager.hpp"

class TurretManager
{
public:
	TurretManager();
	~TurretManager(){};

	void UpdateTurrets(float deltaTime, EnemyManager* enemyManager);
	void RotateTurrets(int orb, float angle);
	void RotationChange(float angle);
	void RotationChange(float angle, int orbit);
	void DrawTurrets();
	void CreateTurret(float type, float orb, float orbPos);
	void ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe);
	void UpdateBullets(float dt, EnemyManager* enemyManager);
	void DrawBullets();
	std::vector<uth::GameObject*> EnemyWithinRange(EnemyManager* enemyManager,float positionX, float positionY, float radius);

	std::vector<uth::GameObject*> turrets;
	std::vector<uth::GameObject*> bullets;
protected:

	uth::Sprite* turret01Sprite;
	uth::Texture* turret01Texture;
	uth::Texture* bullet01Texture;
	float orbit01Angle;
	float orbit02Angle;
	float AngleAmount;
	float currentAngle;

private:

};

#endif