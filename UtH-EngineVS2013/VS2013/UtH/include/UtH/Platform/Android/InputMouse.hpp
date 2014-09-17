#pragma once
#ifndef MOUSEINPUT_H_UTH
#define MOUSEINPUT_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>

#include <pmath/Vector2.hpp>

namespace uth
{
	enum class Mouse
	{
		MS1		= 0,
		LEFT	= MS1,
		MS2		= 1,
		RIGHT	= MS2,
		MS3		= 2,
		MIDDLE	= MS3,
		MS4		= 3,
		X1		= MS4,
		MS5		= 4,
		X2		= MS5,
		COUNT
	};

	//extern class Input;
	class MouseInput : public InputBase
	{
	public:
		bool IsButtonDown(Mouse Button);
		bool IsButtonPressed(Mouse Button);
		bool IsButtonReleased(Mouse Button);

		pmath::Vec2 Position();
		pmath::Vec2 Movement();
		pmath::Vec2 Wheel();
	};
}

#endif