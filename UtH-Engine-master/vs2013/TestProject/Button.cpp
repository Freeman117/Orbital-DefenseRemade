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
	if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
	{
		auto clickPos = m_target.PixelToCoords(uthInput.Mouse.Position());
		//Esimerkkikoodia uth-enginen sivulta
		if (transform.GetBounds().contains(clickPos) && m_callback)
		m_callback();
	}

}
