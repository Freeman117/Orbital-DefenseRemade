#include "Turret.hpp"


<<<<<<< HEAD

=======
>>>>>>> origin/master
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
<<<<<<< HEAD

=======
>>>>>>> origin/master
}

void Turret::init(int t, int orb,int orbPos)
{
<<<<<<< HEAD


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
=======
	

	if(t == 1)
	{
		damage = 1.0f;
		speed = 2.0f;
		range = 150.0f;
		aoe = 0;
		type = 1;
	}
	else
	{
		
	}
>>>>>>> origin/master

	orbit = orb;
	orbitPos = orbPos;

}

<<<<<<< HEAD
void Turret::AddTurret(float o, float oPos, int tType)
{
	init(tType,o,oPos);

	turret = new uth::GameObject();
	turrets.push_back(turret);
	turret->AddComponent(new uth::Sprite("test2.tga"));
	turret->transform.SetScale(0.1f);
	o = orbit;
	oPos = orbitPos;
	//turret->transform.SetPosition(100*cosf(oPos),100*sinf(oPos));
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
=======
void Turret::AddTurret(int o, int oPos, int tType)
{
	//turret = _spriteBatch->
	//turrets.push_back(turret);
}

void Turret::Update(float dt)
{
	
>>>>>>> origin/master
}

Turret::~Turret()
{
}
