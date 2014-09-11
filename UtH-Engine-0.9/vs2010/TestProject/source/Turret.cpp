#include "Turret.hpp"



Turret::Turret(uth::SpriteBatch* spriteBatch)
{
	_spriteBatch = spriteBatch;

	damage = 0;
	speed = 0;
	range = 0;
	aoe = 0;
	orbit = 0;
	orbitPos = 0;
	totalTime = 0;

	testi = 0;		//TODO: Suunnittele logiikka tornien asettamiselle.

}

void Turret::init(int t, int orb,int orbPos)
{

	//if(t == 1)
	//{
	//damage = 1.0f;
	//speed = 2.0f;
	//range = 150.0f;
	//aoe = 0;
	//type = 1;
	//}
	//else
	//{
		
	//}

}

void Turret::AddTurret(float o, float oPos, int tType)
{
	o = orbit;
	oPos = orbitPos;

	//init(tType,o,oPos);  //Tällä hetkellä turha funktio

	turret = new uth::GameObject();
	turrets.push_back(turret);
	turret->AddComponent(new uth::Sprite("test2.tga"));
	turret->transform.SetScale(0.1f);

	for (int i = turrets.size()-1; i >=0; i--)
	{
		testi++;
		turrets[i]->transform.SetPosition(100*cosf(oPos+PI/3*testi),100*sinf(oPos+PI/3*testi));
	}
}

void Turret::Update(float dt, float rotation)
{
	if(turrets.size() < 1)
	{
		return;
	}
	totalTime += dt;
	for(int i = turrets.size() -1; i>= 0; i--)
	{
		turrets[i]->transform.SetPosition(100*cosf(rotation),100*sinf(rotation));
	}
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
