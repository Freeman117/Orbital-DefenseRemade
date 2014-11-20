#include "Button.hpp"
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Engine/Sprite.hpp>

using namespace ns;

Button::Button(const uth::RenderTarget& target, uth::Texture* texture)
	: GameObject(),
	  m_target(target)
{
	this->AddComponent(new uth::Sprite(texture));
}

void Button::setCallBack(Callback callback)
{
	m_callback = callback;
}

void Button::update(float)
{
#if defined UTH_SYSTEM_WINDOWS
	if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
	{
		auto clickPos = m_target.PixelToCoords(uthInput.Mouse.Position());
		//Esimerkkikoodia uth-enginen sivulta
		if (transform.GetBounds().contains(clickPos) && m_callback)
		m_callback();
	}
#endif
#if defined UTH_SYSTEM_ANDROID
	if (uthInput.Touch[0].Motion() == uth::TouchMotion::TAP)
	{
		//Esimerkkikoodia uth-enginen sivulta
		auto touchPos = m_target.PixelToCoords(uthInput.Touch[0].GetPosition());
		if (transform.GetBounds().contains(touchPos) && m_callback)
		m_callback();
	}
#endif

}
