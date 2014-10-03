#ifndef TURRET_H_
#define TURRET_H_

#include <UtH/UtHEngine.hpp>

class Turret : public uth::Component
{
public:
	Turret(int t, int orb, int orbPos);
	~Turret();

	void init(int t);

	int type;
	float damage;
	float speed;
	float range;
	float aoe;

	float totalTime;

	float orbit;
	float orbitPos;

	float testi;
	float testi2;

	std::vector<uth::GameObject*> turrets;

	void Update(float dt) override;
	void AddTurret(float o,float oPos, int tType);
	void Draw(uth::RenderTarget& target) override;

	uth::SpriteBatch* _spriteBatch;
	uth::GameObject* turret;
	
	
};

#endif