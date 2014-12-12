#ifndef TURRETMANAGER_HPP
#define TURRETMANAGER_HPP

#include <UtH/Engine/Engine.hpp>
#include <pmath/PMath.hpp>
#include "Turret.hpp"
#include "Turret_Cannon.hpp"
#include "Turret_Missile.hpp"
#include "Turret_Lazer.hpp"
#include "Turret_Beam.hpp"
#include "Turret_Disruptor.hpp"
#include "Turret_Mrk.hpp"
#include "Bullet.hpp"
#include "Node.hpp"
#include "EnemyManager.hpp"
#include <array>

class TurretManager : public uth::GameObject
{
public:
	TurretManager();
	~TurretManager(){};

	void UpdateTurrets(float deltaTime, EnemyManager* enemyManager);
	void UpgradeTurret(float &money);
	void RotateTurrets(int orb, float angle);
	void RotationChange(float angle);
	void RotationChange(float angle, int orbit);
	void CreateTurret(int type, int orb, int orbPos);
	void ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe, bool penetrate,float slowAmount,float crit, float armorPene, uth::Texture* texture);
	void UpdateBullets(float dt, EnemyManager* enemyManager);
	void CreateNodes();
	void UpdateNodes();
	std::vector<std::shared_ptr<uth::GameObject>> EnemyWithinRange(EnemyManager* enemyManager, float positionX, float positionY, float radius);
	std::vector<std::shared_ptr<uth::GameObject>> turrets;
	std::vector<std::shared_ptr<uth::GameObject>> bullets;
	std::vector<std::shared_ptr<Node>> nodes;
	//std::vector<Node*> nodes;

	void poisto();
protected:

	float orbit01Angle;
	float orbit02Angle;
	float AngleAmount;
	float currentAngle;

private:
	uth::Sprite* turret01Sprite;
	uth::Texture* turret01Texture;
	uth::Texture* bullet01Texture;
	uth::Texture* node01Texture;
	uth::Texture* towerButtonTexture;

	uth::Randomizer* rand;

	std::array<ns::Button*, 6> towers;
	std::vector<std::shared_ptr<ns::Button>> towerButtons;
	ns::Button* cancel;
	std::vector<std::shared_ptr<ns::Button>> cancelButton;

	void AddTurretButtons();
	void RemoveTurretButtons();

	uth::Texture* disruptorProjectile;
};

#endif