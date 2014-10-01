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

	testi = 0;		//TODO: Suunnittele logiikka tornien asettamiselle.
	testi2= 0;
}

void Turret::init(int t, int orb,int orbPos)
{
	t = type;
	if (t = 1)
	{
		damage = 1.0f;
		speed= 1.0f;
		range = 1.0f;
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

	if (turrets.size() < 0)
		return;

	int t = turrets.size()-1;

	Turret* turretComponent = turrets[t]->GetComponent<Turret>("");
	turretComponent->init(1, 0, 0);
	

}
//pmath::pi  MATIKKAKIRJASTO VAIHTUNUT
void Turret::Update(float dt, float rotation)		//Funktion toimintaa pit‰‰ muuttaa j‰rkev‰mm‰ksi
{
	
	if(turrets.size() < 1)
	{
		return;
	}
	totalTime += dt;

	//for(int i = turrets.size() -1; i>= 0; i--)//turrets.size()-1
	//{
	//	testi2++;
	//	turrets[i]->transform.SetPosition(100 * cosf(rotation + pmath::pi / 3 * testi2), 100 * sinf(rotation + pmath::pi / 3 * testi2));
	//}

	
}

void Turret::Draw()
{
	if(turrets.size() < 1)
	{
		return;
	}
	for(int i = turrets.size() -1; i>=0; i--)
	{
		turrets[i]->Draw(uthEngine.GetWindow());
	}
}

Turret::~Turret()
{
}
