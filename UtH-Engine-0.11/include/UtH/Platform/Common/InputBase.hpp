#pragma once
#ifndef INPUTBASE_H_UTH
#define INPUTBASE_H_UTH

#include <UtH/Platform/InputEnums.hpp>

namespace uth
{
	class InputBase
	{
	public:
        virtual void Update(){}
        // For updates that need delta time
        virtual void Update(float){}
		virtual void Initiate(){}
		static void setWindowHandle(void* WindowHandle);
	protected:
		static void* windowHandle;
	};
}

#endif