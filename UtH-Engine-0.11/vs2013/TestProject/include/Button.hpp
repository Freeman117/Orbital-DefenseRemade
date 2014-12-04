#pragma once

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <UtH/Engine/GameObject.hpp>
#include <functional>
#include <UtH\Engine\AnimatedSprite.hpp>

namespace uth
{
	class RenderTarget;
	class Texture;
}

namespace ns
{
	class Button final: public uth::GameObject
	{
		typedef std::function<void()> Callback;
	public:
		//Esimerkkikoodia uth-enginen sivulta
		Button(const uth::RenderTarget& target, uth::Texture* texture);
		//Button(const uth::RenderTarget& target, uth::AnimatedSprite* animatedSprite);

		void setCallBack(Callback callback);
	private:
		void update(float dt) override;
		const uth::RenderTarget& m_target;
		Callback m_callback;

	};

}

#endif