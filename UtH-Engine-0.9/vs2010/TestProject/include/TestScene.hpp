#pragma once
#ifndef TestScene_H_UTH
#define TestScene_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Math/Math.hpp>
#include <math.h>
#include <Turret.hpp>

namespace uth
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();

		float orbit1angle, orbit2angle;
<<<<<<< HEAD
		int orbitpos;
		bool constructed;

	protected:
		SpriteBatch* spriteBatch;
		Shader* shader;
		GameObject *image;

		GameObject *test2;

		Turret *turret;
		
=======

	protected:
		Shader* shader;
		GameObject *image;
		GameObject *test;
		GameObject *herp;

		GameObject *turret;

>>>>>>> origin/master
	};
}

#endif
