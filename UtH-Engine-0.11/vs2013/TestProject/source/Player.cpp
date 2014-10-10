#include "Player.hpp"

Player::Player()
	: uth::GameObject("Player")
{
	this->AddComponent(new uth::Sprite("moonBaseMockup2.png"));
}

Player::~Player()
{

}

void Player::update(float dt)
{

}

void Player::draw(uth::RenderTarget& target)
{

}