#pragma once

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <UtH/Engine/GameObject.hpp>
#include <functional>

namespace uth
{
	class RenderTarget;
	class Texture;
}

namespace ns
{
	class Button : public uth::GameObject
	{
	public:
		//Esimerkkikoodia uth-enginen sivulta
		Button(const uth::RenderTarget& target, uth::Texture* texture);
		void update(float dt) override;
		void setCallBack(std::function<void()> callback);
	private:
		const uth::RenderTarget& m_target;
		std::function<void()> m_callback;

	};

}

#endif