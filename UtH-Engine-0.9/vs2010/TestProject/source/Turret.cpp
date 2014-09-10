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

}

void Turret::init(int t, int orb,int orbPos)
{


	//if(t == 1)
	//{
	damage = 1.0f;
	speed = 2.0f;
	range = 150.0f;
	aoe = 0;
	type = 1;
	//}
	//else
	//{
		
	//}

	orbit = orb;
	orbitPos = orbPos;

}

void Turret::AddTurret(float o, float oPos, int tType)
{
	init(tType,o,oPos);

	turret = new uth::GameObject();
	turrets.push_back(turret);
	//_spriteBatch->AddSprite(turret,"Turret",umath::vector4(1,1,1,1),umath::rectangle(0,0,16,16));
	turret->AddComponent(new uth::Sprite("test2.tga"));
	turret->transform.SetScale(0.1f);
	o = orbit;
	oPos = orbitPos;
	turret->transform.SetPosition(100*cosf(oPos),100*sinf(oPos));
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
		turret->transform.SetPosition(100*cosf(rotation),100*sinf(rotation));
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
		turret->Draw(uthEngine.GetWindow());
	}
}

Turret::~Turret()
{
}
