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
	testi2= 0;
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

	//init(tType,o,oPos);  //T‰ll‰ hetkell‰ turha funktio

	//if(turrets.size() >= 6)
	//{
	//	return;
	//}

	turret = new uth::GameObject();
	turrets.push_back(turret);
	turret->AddComponent(new uth::Sprite("test2.tga"));		//Ei toimi (Error:ATTEMPT TO DIVIDE BY ZERO)
	turret->transform.SetScale(0.1f);
	//if(turrets.size() <= 5)
	//{
		for (int i = turrets.size()-1; i >=0; i--)
		{
		testi++;
		turrets[i]->transform.SetPosition(100 * cosf(oPos + pmath::pi / 3 * testi), 100 * sinf(oPos + pmath::pi / 3 * testi));
		}
	//}
	/*if(turrets.size() <= 6)
	{
		for (int i = turrets.size()-1; i >=0; i--)
		{
		testi++;
		turrets[i]->transform.SetPosition(180 * cosf(oPos + pmath::pi / 3 * testi), 180 * sinf(oPos + pmath::pi / 3 * testi));
		}
	}*/
}
//pmath::pi  MATIKKAKIRJASTO VAIHTUNUT
void Turret::Update(float dt, float rotation)		//Funktion toimintaa pit‰‰ muuttaa j‰rkev‰mm‰ksi
{
	
	if(turrets.size() < 1)
	{
		return;
	}
	totalTime += dt;

	for(int i = 5; i>= 0; i--)//turrets.size()-1
	{
		testi2++;
		turrets[i]->transform.SetPosition(100 * cosf(rotation + pmath::pi / 3 * testi2), 100 * sinf(rotation + pmath::pi / 3 * testi2));
	}

	/*if(turrets.size() >=6)
	{
		for(int i = turrets.size()-1; i>=6; i--)
		{
			turrets[i]->transform.SetPosition(180 * cosf(rotation + pmath::pi / 3 * testi2), 180 * sinf(rotation + pmath::pi / 3 * testi2));
		}
	}*/
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
