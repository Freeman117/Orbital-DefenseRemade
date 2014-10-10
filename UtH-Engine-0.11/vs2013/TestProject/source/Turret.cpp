#include "Turret.hpp"

Turret::Turret(int type_, int orb, int orbPos) : uth::Component("Turret")
{

	type = type_;
	damage = 0;
	speed = 0;
	range = 0;
	aoe = 0;
	orbit = orb;
	orbitPos = orbPos;
	totalTime = 0;

	init(type);

	testi = 0;		//TODO: Suunnittele logiikka tornien asettamiselle.
	testi2= 0;
}

void Turret::init(int t)
{
	type = t;
	if (t == 1)
	{
		damage = 10.0f;
		speed= 1.0f;
		range = 100.0f;
		aoe = 0.0f;
	}
	else
	{
		return;
	}
}

void Turret::AddTurret(float o, float oPos, int tType)
{
	o = orbit;
	oPos = orbitPos;
	tType = type;


	turret = new uth::GameObject();
	turrets.push_back(turret);
	turret->AddComponent(new uth::Sprite("test2.tga"));
	turret->transform.SetScale(0.1f);
	//if(turrets.size() <= 5)
	//{
		for (int i = turrets.size()-1; i >=0; i--)
		{
		testi++;
		turrets[i]->transform.SetPosition(100 * cosf(oPos + pmath::pi / 3 * testi), 100 * sinf(oPos + pmath::pi / 3 * testi));
		}


}
void Turret::Update(float dt)//Funktion toimintaa pit‰‰ muuttaa j‰rkev‰mm‰ksi
{
	
	if(turrets.size() < 1)
	{
		return;
	}
	totalTime += dt;


	
}

void Turret::Draw(uth::RenderTarget& target)
{
	if(turrets.size() < 1)
	{
		return;
	}
	for(int i = turrets.size() -1; i>=0; i--)
	{
		turrets[i]->Draw(target);
	}
}

Turret::~Turret()
{
}
